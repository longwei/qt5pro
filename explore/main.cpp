/*
* Copyright 2013 Atlassian
*/

#include <QAbstractNativeEventFilter>
#include <QWindow>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMessageBox>
#include <QSslCertificate>
#include <QSslCertificateExtension>
#include <QSslConfiguration>
#include <QSslSocket>
#include <QStyleFactory>
#include <QtSingleApplication>
#include <QStandardPaths>

#include <QTimer>

#include <iostream>
#include <stdio.h>

#include "AddLiveController.h"
#include "HipLogin.h"
#include "HipMainWindow.h"
#include "ServerConnection.h"
#include "Utils.h"
#include <Settings.h>
#include "LoggingCategories.h"

//#ifdef Q_OS_MAC
//#include <private/qcore_mac_p.h>
//#endif


Q_LOGGING_CATEGORY(HC_GRAPHICS, "hc.graphics");
Q_LOGGING_CATEGORY(HC_NETWORK,  "hc.network");

#ifdef Q_OS_WIN32
#include <Windows.h>

class WindowsEventFilter : public QAbstractNativeEventFilter
{
    void quitApp()
    {
        QObject* sc = qApp->findChild<ServerConnection*>();
        if( sc )
        {
            sc->deleteLater();
        }
        for ( auto widget : qApp->topLevelWidgets() )
        {
            if ( qobject_cast<HipMainWindow*>( widget ) )
            {
                widget->deleteLater();
            }
        }
        qApp->quit();
    }
    virtual bool nativeEventFilter( const QByteArray& eventType, void* message, long* result ) override
    {
        MSG* msg = reinterpret_cast<MSG*>( message );
        if ( msg->message == WM_QUERYENDSESSION )
        {
            qDebug() << "bbbbb querying for end session";
            quitApp();
            return true;
        }
        else if ( msg->message == WM_ENDSESSION
                   && ( msg->lParam & ENDSESSION_CLOSEAPP )
                   && msg->wParam == TRUE )
        {
            qDebug() << "bbbbb quitting";
            quitApp();
            return true;
        }
        return false;
    }
};

#endif

#ifdef Q_OS_LINUX
#include "client/linux/handler/exception_handler.h"
#include <unistd.h>
static QString applicationPath;
static bool dumpCallback( const google_breakpad::MinidumpDescriptor& descriptor,
                          void* context,
                          bool succeeded )
{
#ifdef TEMP_DISABLED
    const char* kurasshuPath = ( applicationPath + "/kurasshu" ).toLocal8Bit();
    qWarning() << "HipChat has crashed. Crash dump is at:" << descriptor.path()
               << ( applicationPath + "/kurasshu" ).toLocal8Bit()
               << execl( kurasshuPath, kurasshuPath, descriptor.path(), NULL );
#endif
    return false; //allow sigabrt's to be raised
}
#elif defined(Q_OS_WIN)
extern QString qAppFileName(); //a private Qt function defined for Mac & Windows
#endif

#ifdef Q_OS_WIN
#include "../breakpad-qt/BreakpadHandler.h"
#endif

static qint64 startupMsec = QDateTime::currentMSecsSinceEpoch();
void messageHandler( QtMsgType type, const QMessageLogContext& context, const QString& msg )

{
    if ( Utils::logging->type != Utils::None )
    {
        qint64 msecSinceStart = QDateTime::currentMSecsSinceEpoch() - startupMsec;
        QString output;

        if ( qstrcmp( context.category, "x" ) == 0 )
        {
            output = qlc( '[' ) % QString::number( msecSinceStart, 16 ) % qll( "] " ) % msg;
        }
        else
        {
            output = qlc( '[' ) % QString::number( msecSinceStart, 16 ) % qll( "][" )
                     % context.function % qlc( ']' ) % msg;
        }

        switch ( type )
        {
            case QtDebugMsg:
                break;

            case QtWarningMsg:
                output = QString( "Warning: " ).append( msg );
                break;

            case QtCriticalMsg:
                output = QString( "Critical: " ).append( msg );
                break;

            case QtFatalMsg:
                output = QString( "Fatal error: " ).append( msg );
                break;

            default: //Qt 5.2 introduces QtTraceMsg
                output = QString( "Trace: " ).append( msg );
                break;
        }

#ifdef Q_OS_WIN
        output = output.left(450) + "\n";

        //following the advice of this poor guy:
        //  http://stackoverflow.com/questions/14643293/how-does-qt5-redirect-qdebug-statements-to-the-qt-creator-2-6-console
        OutputDebugStringA(output.toLocal8Bit().constData());
#endif

//        output.append( "\n" );

//        switch ( Utils::logging->type )
//        {
//            case Utils::StdoutLogging:
//                {
//                    QTextStream( stdout ) << output;
//                    break;
//                }

//            case Utils::FileLogging:
//                {
//                    if ( !Utils::logging->debugLog )
//                    {
//                        QString saveLoc  = QStandardPaths::standardLocations( QStandardPaths::DesktopLocation )[0];
//                        if (saveLoc.isEmpty())
//                            QDir::homePath();
//                        saveLoc.append( QDir::toNativeSeparators( "/hipchatlog.txt" ) );
//                        QFile* log = new QFile( saveLoc );
//                        log->open( QIODevice::WriteOnly | QIODevice::Text );
//                        Utils::logging->debugLog = new QTextStream( log );
//                    }

//                    ( *Utils::logging->debugLog ) << output;
//                    Utils::logging->debugLog->flush();
//                    break;
//                }

//            case Utils::AboutLogging:
//                {
//                    Utils::aboutLog.append( output );
//                    break;
//                }

//            case Utils::None:
//                break;
//        }

        if ( type == QtFatalMsg )
            abort();
    }
}

int main( int argc, char** argv )
{
    qDebug() << "Hey ***";

    initResources();
    Utils::init();

#ifdef Q_OS_LINUX
    qInstallMessageHandler( messageHandler );
    google_breakpad::MinidumpDescriptor descriptor( "/tmp" );
    google_breakpad::ExceptionHandler eh( descriptor,
                                          0,
                                          dumpCallback,
                                          0,
                                          true,
                                          -1 );
    QFileInfo binaryInfo( qll( "/proc/self/exe" ) );
    QString libPath = binaryInfo.canonicalPath();
    QStringList paths;
    paths << libPath << libPath % qll( "/plugins" );
    QCoreApplication::setLibraryPaths( paths );

#elif defined(Q_OS_WIN)
    qInstallMessageHandler( messageHandler );
//    QString libPath = QFileInfo( qAppFileName() ).path();
//    QStringList paths;
//    paths << libPath << libPath % qls( "/plugins" );
//    QCoreApplication::setLibraryPaths( paths );
#elif defined(Q_OS_MAC)
    QString appFileName;
    {
        QCFType<CFURLRef> bundleURL(CFBundleCopyExecutableURL(CFBundleGetMainBundle()));
        if(bundleURL)
    {
            QCFString cfPath(CFURLCopyFileSystemPath(bundleURL, kCFURLPOSIXPathStyle));
            if(cfPath)
                appFileName = cfPath;
    }
    }
    QStringList paths;
    QString libPath = QFileInfo( appFileName ).path();
    paths << libPath << libPath % qls( "/plugins" );
    QCoreApplication::setLibraryPaths( paths );
    qDebug() << paths << appFileName;
#endif
    qDebug() << "hello";
    QtSingleApplication app( argc, argv );

    qDebug() << "hello again" << QCoreApplication::applicationDirPath();
    if ( app.isRunning() && !app.arguments().contains( "--detach" ) ) //really: isRunningTwice
    {
#ifndef Q_OS_WIN
        QTextStream( stdout ) << "HipChat is already running; activating other instance.\n"
                              "Run a new process with --detach.\n";
#endif
        return app.sendMessage( qll( "what's up" ) ) ? 0 : 1;
    }

    QCoreApplication::setOrganizationName( "Atlassian" );
    QCoreApplication::setOrganizationDomain( "atlassian.com" );
    QCoreApplication::setApplicationName( "HipChat" );
    QCoreApplication::setApplicationVersion( Utils::QUIPCHAT_VERSION_STR );
    app.setWindowIcon( Utils::appIcon );
    Utils::initPixmaps();

    if ( app.arguments().contains( "--debug" ) )
        Utils::logging->type = Utils::StdoutLogging;
//    else if ( app.arguments().contains( "--logtofile" ) )
//        Utils::logging->type = Utils::FileLogging;
//    else
//        Utils::logging->type = Utils::None;

//    if ( app.arguments().contains( "--verbose" ) )
//        Utils::logging->printPresence = true;

//    if ( app.arguments().contains( qll( "--dont-strip-messages" ) ) )
//        Utils::logging->stripMessages = false;

//    if ( app.arguments().contains( qll( "--logtoabout" ) ) )
//    {
//        Utils::logging->type = Utils::AboutLogging;
//        Utils::aboutLog.reserve( 100000 );
//    }
    Utils::countFps = app.arguments().contains( qll("--fps") );

//    qDebug() << "available styles" << QStyleFactory::keys();

//    if ( app.arguments().contains( "--help" ) )
//    {
//        QTextStream( stdout ) << "Usage: hipchat [options]\n\n"
//                              "Persistent group chat using XMPP.\n\n"
//                              "Options:\n"
//                              "\t--help: Show this help\n"
//                              "\t--version: Show version information\n"
//                              "\t--humans: The humans behind HipChat\n"
//                              "\t--debug: Print debugging information to console\n"
//                              "\t--logtofile: Save debugging information to hipchatlog.txt\n"
//                              "\t--logtoabout: Save debugging information in a buffer in the About dialog.\n"
//                              "\t--verbose: Include presence information in log\n"
//                              "\t--dont-strip-messages: Don't strip sensitive information from log.\n"
//                              "\t--fps: Show FPS counters on video.\n"
//                              ;
//        return 0;
//    }

//    if ( app.arguments().contains( "--version" ) )
//    {
//#ifdef Q_OS_UNIX
//        QTextStream out( stdout );
//#elif defined( Q_OS_WIN32)
//        QFile* log = new QFile( "hipchatlog.txt" );
//        log->open( QIODevice::WriteOnly | QIODevice::Text );
//        QTextStream out( log );
//#endif
//        QPointer<AddLiveController> addLive = new AddLiveController( nullptr );
//        QObject::connect( addLive.data(), &AddLiveController::version, [&]( const QString & version )
//        {
//            out << "Video version:\t\t" % version % "\n";
//            delete addLive.data();
//            qApp->quit();
//        } );
//        addLive->requestVersion();

//        out << "HipChat:\t\t" % Utils::QUIPCHAT_VERSION_STR % "\n"
//            "Compiled Qt:\t\t" QT_VERSION_STR "\n"
//            "Using Qt:\t\t" << qVersion() << "\n";

//        return app.exec();

//    }

//    if ( app.arguments().contains( "--humans" ) )
//    {
//        QFile humans( ":/web/humans.txt" );
//        humans.open( QIODevice::ReadOnly );
//        QTextStream( stdout ) << humans.readAll();
//        return 0;
//    }

//    {
//#ifdef Q_OS_LINUX
//        applicationPath = app.applicationDirPath();
//        QString fontPath = applicationPath % qll( "/../share/fonts/truetype/Symbola.ttf" );
//        QFontDatabase::addApplicationFont( fontPath );
//#else
//        QString fontPath = app.applicationDirPath() % qll( "/Symbola.ttf" );
//        //not adding font for Windows, due to unpatched bug in the Windows dlls
//        //and QTextEdit doesn't seem to appreciate > 4 byte characters on Windows.
//#endif
//        qDebug() << fontPath;
//    }

//#if defined(Q_OS_WIN)
//    BreakpadQt::GlobalHandler::instance()->setDumpPath( QDir::tempPath() );
//#ifdef TEMP_DISABLED
//    BreakpadQt::GlobalHandler::instance()->setReporter( "kurasshu" );
//#endif
//    QFont font = app.font();
//    font.setFamily( "Arial" );
//    font.setPointSizeF( qMax( font.pointSizeF(), 9.5 ) );
//    app.setFont( font );
//#endif
//    app.setFont( Settings::instance()->font() );
    {
        QSslConfiguration config = QSslConfiguration::defaultConfiguration();
        QList<QSslCertificate> certs;
        QDir certDir( ":/certs/" );
        certDir.setFilter( QDir::Files );
        QFileInfoList certList = certDir.entryInfoList();

        foreach ( const QFileInfo & certFileInfo, certList )
        {
            QFile certFile( certFileInfo.filePath() );
            if( certFile.open( QIODevice::ReadOnly ) )
            {
                QSslCertificate loadedCert( certFile.readAll(), QSsl::Pem );
                if ( Utils::logging->printPresence )
                {
                    qDebug() << certFileInfo.filePath() << loadedCert.issuerInfo( QSslCertificate::Organization ) << loadedCert.expiryDate() << loadedCert.subjectInfo( QSslCertificate::Organization ) << loadedCert.isNull();
                }
                certs << loadedCert;
                Utils::SslHashes << loadedCert.digest( QCryptographicHash::Sha1 ).toHex();
            }
            else
            {
                qDebug() << "error opening cert" << certFileInfo.filePath() << certFile.error();
            }
        }

        config.setCaCertificates( certs );
        config.setPeerVerifyDepth( 0 );
        QSslConfiguration::setDefaultConfiguration( config );
    }
    HipMainWindow::loadStyleSheet();
#ifdef Q_OS_WIN32
    qApp->installNativeEventFilter( new WindowsEventFilter );
#endif

    QTimer timer;
    QObject::connect( &timer, &QTimer::timeout, [&timer]() {
        timer.stop();

        qDebug() << "creating widgets[0]";

        HipMainWindow* mainWindow = new HipMainWindow();
        HipLogin* foo = new HipLogin( mainWindow );

        if ( Settings::instance()->password().isEmpty() || Settings::instance()->userName().isEmpty() )
        {
            foo->show();
        }
        else
        {
            foo->onSignInReleased();
            foo->show();
        }

        qDebug() << "creating widgets[1]";
    }  );

    timer.start(0);

    qDebug() << "starting qApp";
    int val = app.exec();
    qDebug() << "exiting with" << val;
}
