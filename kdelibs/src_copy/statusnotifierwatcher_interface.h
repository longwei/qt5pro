/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -m -p statusnotifierwatcher_interface /home/w1/portable/code/HipChat/quipchat/kdelibs/knotifications/src/org.kde.StatusNotifierWatcher.xml
 *
 * qdbusxml2cpp is Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef STATUSNOTIFIERWATCHER_INTERFACE_H_1413873782
#define STATUSNOTIFIERWATCHER_INTERFACE_H_1413873782

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.kde.StatusNotifierWatcher
 */
class OrgKdeStatusNotifierWatcherInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.kde.StatusNotifierWatcher"; }

public:
    OrgKdeStatusNotifierWatcherInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgKdeStatusNotifierWatcherInterface();

    Q_PROPERTY(bool IsStatusNotifierHostRegistered READ isStatusNotifierHostRegistered)
    inline bool isStatusNotifierHostRegistered() const
    { return qvariant_cast< bool >(property("IsStatusNotifierHostRegistered")); }

    Q_PROPERTY(int ProtocolVersion READ protocolVersion)
    inline int protocolVersion() const
    { return qvariant_cast< int >(property("ProtocolVersion")); }

    Q_PROPERTY(QStringList RegisteredStatusNotifierItems READ registeredStatusNotifierItems)
    inline QStringList registeredStatusNotifierItems() const
    { return qvariant_cast< QStringList >(property("RegisteredStatusNotifierItems")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> RegisterStatusNotifierHost(const QString &service)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(service);
        return asyncCallWithArgumentList(QLatin1String("RegisterStatusNotifierHost"), argumentList);
    }

    inline QDBusPendingReply<> RegisterStatusNotifierItem(const QString &service)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(service);
        return asyncCallWithArgumentList(QLatin1String("RegisterStatusNotifierItem"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void StatusNotifierHostRegistered();
    void StatusNotifierHostUnregistered();
    void StatusNotifierItemRegistered(const QString &in0);
    void StatusNotifierItemUnregistered(const QString &in0);
};

namespace org {
  namespace kde {
    typedef ::OrgKdeStatusNotifierWatcherInterface StatusNotifierWatcher;
  }
}
#endif