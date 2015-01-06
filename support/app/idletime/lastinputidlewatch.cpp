#include "lastinputidlewatch.h"

#include <QDebug>

#include <windows.h>

static const int timerInterval = 1000;

LastInputIdleWatch::LastInputIdleWatch()
    : m_watching(false),
      m_idle(false)
{
    connect( &m_timer, SIGNAL(timeout()), SLOT(checkIfIdle()) );
}

LastInputIdleWatch::~LastInputIdleWatch()
{

}

void LastInputIdleWatch::setWatching(bool watching)
{
    if (m_watching != watching) {
        m_watching = watching;
        emit watchingChanged();

        if (watching) {
            qDebug() << "LastInputIdleWatch::setWatching() -- starting, timeout:" << m_idleTimeout;
            m_timer.start(timerInterval);
            checkIfIdle();
        } else {
            qDebug() << "LastInputIdleWatch::setWatching() -- stopping";
            m_timer.stop();
        }
    }
}

bool LastInputIdleWatch::watching() const
{
    return m_watching;
}

bool LastInputIdleWatch::idle() const
{
    return m_idle;
}

void LastInputIdleWatch::checkIfIdle()
{
//    qDebug() << "LastInputIdleWatch::onTimer()";

    LASTINPUTINFO info;
    info.dwTime = 0;
    info.cbSize = sizeof(LASTINPUTINFO);

    if (GetLastInputInfo(&info)) {
        quint64 idleTicks = GetTickCount() - info.dwTime;
        bool idle = idleTicks > idleTimeout()*1000;

        if (m_idle != idle) {
            qDebug() << "LastInputIdleWatch::onTimer() -- idle changed to:" << idle;
            m_idle = idle;
            emit idleChanged();
        }
    } else {
        qDebug() << "LastInputIdleWatch::onTimer() -- GetLastInputInfo() failed";
    }
}
