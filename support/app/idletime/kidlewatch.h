#ifndef KIDLEWATCH_H
#define KIDLEWATCH_H

#include "idlewatch.h"

class KIdleWatch: public IdleWatch
{
    Q_OBJECT
public:
    KIdleWatch();
    ~KIdleWatch();

    void setWatching(bool watching);
    bool watching() const;

    bool idle() const;

private slots:
    void onKITTimoutReached(int id);
    void onKITResumingFromIdle();

private:
    int m_kIdleTimeoutId;
    bool m_watching;
    bool m_idle;
};

#endif // KIDLEWATCH_H
