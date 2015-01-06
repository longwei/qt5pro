#include <testrunner.h>

#include <QDebug>

#include "tst_xmlcharfilter.h"

int main() {
    TestRunner testRunner;

    testRunner.addTest(new Tst_toXMLCharacterRange);

    bool res = testRunner.runTests();

    qDebug() << "Overall result: " << (res? "PASS": "FAIL");

    return !res;
}
