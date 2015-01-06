#include "kidlewatch.h"

#include "kidletime/kidletime.h"

#include <QDebug>

KIdleWatch::KIdleWatch()
    : m_kIdleTimeoutId(-1),
      m_watching(false),
      m_idle(false)
{
    connect( KIdleTime::instance(), SIGNAL(timeoutReached(int)), SLOT(onKITTimoutReached(int)) );
    connect( KIdleTime::instance(), SIGNAL(resumingFromIdle()), SLOT(onKITResumingFromIdle()) );
}

KIdleWatch::~KIdleWatch()
{
    if (m_kIdleTimeoutId != -1) {
        KIdleTime::instance()->removeIdleTimeout(m_kIdleTimeoutId);
        qDebug() << "~KIdleWatch()::KIdleWatch() -- removed m_kIdleTimeoutId:" << m_kIdleTimeoutId;
    }
}

void KIdleWatch::setWatching(bool watching)
{
    if (m_watching != watching) {
        m_watching = watching;
        emit watchingChanged();

        if (watching) {
            qDebug() << "KIdleWatch::setWatching() -- starting, idleTimeout():" << idleTimeout();

            if (m_kIdleTimeoutId != -1) {
                KIdleTime::instance()->removeIdleTimeout(m_kIdleTimeoutId);
                qDebug() << "KIdleWatch::KIdleWatch() -- removed m_kIdleTimeoutId:" << m_kIdleTimeoutId;
            }

            m_kIdleTimeoutId = KIdleTime::instance()->addIdleTimeout(idleTimeout()*1000);
            qDebug() << "KIdleWatch::KIdleWatch() -- added m_kIdleTimeoutId:" << m_kIdleTimeoutId;
        } else {
            qDebug() << "KIdleWatch::KIdleWatch() -- stopping";

            KIdleTime::instance()->removeIdleTimeout(m_kIdleTimeoutId);
            qDebug() << "KIdleWatch::KIdleWatch() -- removed m_kIdleTimeoutId:" << m_kIdleTimeoutId;
            m_kIdleTimeoutId = -1;
        }
    }
}

bool KIdleWatch::watching() const
{
    return m_watching;
}

bool KIdleWatch::idle() const
{
    return m_idle;
}

void KIdleWatch::onKITTimoutReached(int id)
{
    qDebug() << "KIdleWatch::onKITTimoutReached()";

    if (m_kIdleTimeoutId != id) {
        QString msg = QString("KIdleWatch::onKITTimoutReached() -- id, mismatch, m_kIdleTimeoutId: %1, id: %2")
                .arg(m_kIdleTimeoutId).arg(id);
        qFatal("%s", msg.toLatin1());
    }

    if (!m_idle) {
        qDebug() << "KIdleWatch::onKITTimoutReached() -- idle changed to:" << true;
        m_idle = true;
        emit idleChanged();
    }

    KIdleTime::instance()->catchNextResumeEvent();
}

void KIdleWatch::onKITResumingFromIdle()
{
    qDebug() << "KIdleWatch::onKITResumingFromIdle()";

    if (m_idle) {
        qDebug() << "KIdleWatch::onKITTimoutReached() -- idle changed to:" << false;
        m_idle = false;
        emit idleChanged();
    }

    KIdleTime::instance()->removeIdleTimeout(m_kIdleTimeoutId);
    qDebug() << "KIdleWatch::onKITResumingFromIdle() -- removed m_kIdleTimeoutId:" << m_kIdleTimeoutId;
    m_kIdleTimeoutId = KIdleTime::instance()->addIdleTimeout(idleTimeout()*1000);
    qDebug() << "KIdleWatch::onKITResumingFromIdle() -- added m_kIdleTimeoutId:" << m_kIdleTimeoutId;
}
