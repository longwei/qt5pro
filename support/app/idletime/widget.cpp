#include "widget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QGroupBox>
#include <QIntValidator>
#include <QTime>

#include <QDebug>

const int maxTimeout = 3*60*60; //3 hours

static QWidget* groupBoxForTimeoutEdit(QLineEdit* edit, const QString& title, const QString& text)
{
    QGroupBox* gb = new QGroupBox();
    gb->setTitle(title);

    QHBoxLayout* buttonLt = new QHBoxLayout(gb);
    buttonLt->addWidget(edit);

    QIntValidator* validator = new QIntValidator();
    validator->setRange(0, maxTimeout);

    edit->setValidator(validator);
    edit->setText(text);

    return gb;
}

static QWidget* groupBoxForLog(QTextEdit* edit, const QString& title)
{
    QGroupBox* gb = new QGroupBox();
    gb->setTitle(title);

    QHBoxLayout* buttonLt = new QHBoxLayout(gb);
    buttonLt->addWidget(edit);

    edit->setReadOnly(true);

    return gb;
}

Widget::Widget(int idleTimeout, int startDelay)
{
    QVBoxLayout* lt = new QVBoxLayout(this);

    QHBoxLayout* topRowLt = new QHBoxLayout();

    m_idleTimeoutEdit = new QLineEdit();
    topRowLt->addWidget( groupBoxForTimeoutEdit(m_idleTimeoutEdit, "Idle timeout, sec.", QString::number(idleTimeout)) );

    m_startTimeoutEdit = new QLineEdit();
    topRowLt->addWidget( groupBoxForTimeoutEdit(m_startTimeoutEdit, "Start delay, sec.", QString::number(startDelay)) );

    m_startButton = new QPushButton("Schedule start");
    topRowLt->addWidget(m_startButton);
    connect( m_startButton, SIGNAL(clicked()), SLOT(onStartButtonClicked()) );

    lt->addLayout(topRowLt);

    QHBoxLayout* bottomRowLt = new QHBoxLayout();

    m_idleWatchLog = new QTextEdit();
    bottomRowLt->addWidget( groupBoxForLog(m_idleWatchLog, "IdleWatch") );
    connect( &m_idleWatch, SIGNAL(watchingChanged()), SLOT(onIdleWatchingChanged()) );
    connect( &m_idleWatch, SIGNAL(idleChanged()), SLOT(onIdleWatchIdleChanged()) );

    lt->addLayout(bottomRowLt);
}

Widget::~Widget()
{

}

void Widget::onStartButtonClicked()
{
    qDebug() << "Widget::onStartButtonClicked()";
    QTimer::singleShot(m_startTimeoutEdit->text().toInt()*1000, this, SLOT(start()) );

    m_startButton->setEnabled(false);

    m_idleTimeoutEdit->setEnabled(false);
    m_startTimeoutEdit->setEnabled(false);
}

void Widget::start()
{
    qDebug() << "Widget::start()";
    m_idleWatch.setIdleTimeout(m_idleTimeoutEdit->text().toInt());
    m_idleWatch.setWatching(true);
}

static QString currentTimeStr()
{
    return QTime::currentTime().toString();
}

static QString idleWatchIdleStr(const IdleWatch& watch)
{
    return watch.idle()? "true": "false";
}

static void logWatchingChanged(const IdleWatch& watch, QTextEdit* watchLog)
{
    if (watch.watching())
        watchLog->append( QString("[%1] started, idle: %2").arg(currentTimeStr())
                                     .arg(idleWatchIdleStr(watch)) );
}

static void logWatchIdleChanged(const IdleWatch& watch, QTextEdit* watchLog)
{
    QString msg = QString("[%1] idle: %2").arg(currentTimeStr()).arg(idleWatchIdleStr(watch));
    watchLog->append(msg);
}

void Widget::onIdleWatchingChanged()
{
    logWatchingChanged(m_idleWatch, m_idleWatchLog);
}

void Widget::onIdleWatchIdleChanged()
{
    logWatchIdleChanged(m_idleWatch, m_idleWatchLog);
}
