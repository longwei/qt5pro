#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <QList>
#include <QTimer>

#include <QCoreApplication>
#include <QtTest>

class TestRunner: public QObject
{
    Q_OBJECT

public:
    TestRunner();

    void addTest(QObject * test);
    bool runTests();

private slots:
    void run();

private:
    void doRunTests();

    QList<QObject *> m_tests;
    int m_overallResult;
};

#endif // TESTRUNNER_H
