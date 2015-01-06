#include "idlewatch.h"

#include <QDebug>

#ifdef Q_OS_LINUX
    #include "kidletime.h"
#elif defined( Q_OS_WIN32 )
    #include "Windows.h"
#else
    //no support for Mac OS X at the moment
    Q_STATIC_ASSERT_X(false, "IdleWatch: only Linux and Widows are supported currently")
#endif

static const int timerInterval = 1000;

IdleWatch::IdleWatch()
    : m_watching(false),
      m_idleTimeout(0),
      m_idle(false)
{
    connect(&m_timer, &QTimer::timeout, this, &IdleWatch::checkIfIdle);
}

IdleWatch::~IdleWatch()
{

}

void IdleWatch::setWatching(bool watching)
{
    if (m_watching != watching) {
        m_watching = watching;
        emit watchingChanged();

        if (watching) {
            qDebug() << "Starting watching for idle, idleTimeout():" << idleTimeout();
            m_timer.start(timerInterval);
            checkIfIdle();
        } else {
            qDebug() << "Stopping watching for idle";
            m_timer.stop();
        }
    }
}

bool IdleWatch::watching() const
{
    return m_watching;
}

int IdleWatch::idleTimeout() const
{
    return m_idleTimeout;
}

void IdleWatch::setIdleTimeout(int timeout)
{
    if (timeout < 0) {
        qDebug() << "Ignoring an attempt to set a negative idle timeout:" << timeout;
        return;
    }

    if (m_idleTimeout != timeout) {
        m_idleTimeout = timeout;
        emit idleTimeoutChanged();
    }
}

bool IdleWatch::idle() const
{
    return m_idle;
}

void IdleWatch::checkIfIdle()
{
    if (m_idleTimeout == 0) {
        qDebug() << "idle timeout not set, but idle checks are asked for";
        return;
    }

    bool success = false;
    bool idle = getIdleMilliseconds(&success) > m_idleTimeout*1000;

    if (!success)
        return;

    if (m_idle != idle) {
        qDebug() << "LastInputIdleWatch::onTimer() -- idle changed to:" << idle;
        m_idle = idle;
        emit idleChanged();
    }
}

#ifdef Q_OS_LINUX

//always succeds
int IdleWatch::getIdleMilliseconds(bool *success) const
{
    *success = true;
    return KIdleTime::instance()->idleTime();
}

#elif defined( Q_OS_WIN32 )

//getting idle time (via GetLastInputInfo()) may fail on Windows, hence the "ok" flag
int IdleWatch::getIdleMilliseconds(bool *success) const
{
    LASTINPUTINFO info;
    info.dwTime = 0;
    info.cbSize = sizeof(LASTINPUTINFO);

    *success = GetLastInputInfo(&info);

    if (!(*success)) {
        qDebug() << "GetLastInputInfo() failed";
    }

    //Unsigned 32-bit ints -- this will nicely produce correct results
    //  when the values wrap same number of times +/- one;
    //  after about 49 days of inactivity, this will make checkIfIdle()
    //  falsely assume going out from idle state, for a while --
    //  but this is common for GetLastInputInfo() based solutions
    //  (another option could be using CallNtPowerInformation() call,
    //   which is precise to 30 seconds or so only, not fully supported on XP,
    //   and seemingly rarely used overall -- although the two
    //   may probably be combined, if needed)
    return GetTickCount() - info.dwTime;
}

#endif
