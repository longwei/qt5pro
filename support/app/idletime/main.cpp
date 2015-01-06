#include "widget.h"

#include <QApplication>
#include <QTime>
#include <QFile>
#include <QDebug>

#include <cstdio>

void logOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(type)
    Q_UNUSED(context)
    Q_UNUSED(msg)

    QTime currentTime = QTime::currentTime();
    QString currentTimeStr = QString("%1-%2-%3").arg(currentTime.hour(), 2, 10, QChar('0'))
            .arg(currentTime.minute(), 2, 10, QChar('0')).arg(currentTime.second(), 2, 10, QChar('0'));

    static QFile logFile(QString("idletime-[%1].txt").arg(currentTimeStr));

    static bool opened = false;
    if (!opened) {
        if (!logFile.open(QIODevice::Text | QIODevice::WriteOnly))
            qFatal("failed to open() the log file %s", logFile.fileName().toStdString().c_str());

        opened = true;
    }

    QString message = QString("[%1] %2\n").arg(currentTimeStr).arg(msg);
    logFile.write(message.toLocal8Bit());
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qInstallMessageHandler(logOutput);

    Widget widget;
    widget.show();

    return app.exec();
}
