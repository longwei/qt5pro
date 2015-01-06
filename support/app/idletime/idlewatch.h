#ifndef IDLEWATCH_H
#define IDLEWATCH_H

#include <QTimer>

//A simple class doing what KIdleTime promises, basically,
//  but without the trouble brought by KIdleTime's one-shot-style API.
//  Slightly more reliable on Windows, where respective WinAPI functions
//  are used directly; wraps KIdleTime::idleTime() on Linux
class IdleWatch: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool watching READ watching WRITE setWatching NOTIFY watchingChanged)
    Q_PROPERTY(int idleTimeout READ idleTimeout WRITE setIdleTimeout NOTIFY idleTimeoutChanged)
    Q_PROPERTY(bool idle READ idle NOTIFY idleChanged)

signals:
    void watchingChanged();
    void idleTimeoutChanged();
    void idleChanged();

public:
    //upon creation, the property values are:
    //  watching=false, idleTimeout=0, idle=false
    IdleWatch();
    ~IdleWatch();

    //starting watching also results in an immediate idle check,
    //  i.e. idleChanged() may be emitted right from within setWatching(true);
    //  stopping watching makes no checks and leaves "idle" property in its current state
    void setWatching(bool watching);
    bool watching() const;

    //the idle timeout/period watched for (in milliseconds);
    //  value of zero is allowed but results in no checks being performed
    //  (and "idle" property keeping its value);
    //  setting this peoprty does not result in an immediate idle check,
    //  and is allowed when watching for idle state has already started
    //  (i.e. when "watching" property is set)
    int idleTimeout() const;
    void setIdleTimeout(int timeout);

    //whether the computer is considered to be in idle state currently
    //  (calling this method does not result in an immediate re-check)
    bool idle() const;

private:
    void checkIfIdle();
    int getIdleMilliseconds(bool *success) const;

    QTimer m_timer;
    bool m_watching;
    int m_idleTimeout;
    bool m_idle;
};

#endif // IDLEWATCH_H
