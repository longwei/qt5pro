#include "testrunner.h"

#include <QTimer>

#include <QCoreApplication>

#include <QtTest>

TestRunner::TestRunner()
    : m_overallResult(0)
{
}

void TestRunner::addTest(QObject * test)
{
    test->setParent(this);
    m_tests.append(test);
}

bool TestRunner::runTests()
{
    int argc =0;
    char * argv[] = {0};
    QCoreApplication app(argc, argv);

    QTimer::singleShot(0, this, SLOT(run()) );
    app.exec();

    return m_overallResult == 0;
}

void TestRunner::run()
{
    doRunTests();
    QCoreApplication::instance()->quit();
}


void TestRunner::doRunTests()
{
    foreach (QObject * test, m_tests) {
        m_overallResult|= QTest::qExec(test);
    }
}
