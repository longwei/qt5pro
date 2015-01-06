#ifndef TST_XMLCHARFILTER_H
#define TST_XMLCHARFILTER_H

#include <QObject>

class Tst_toXMLCharacterRange: public QObject
{
    Q_OBJECT
public:

private slots:
    //strings completely consisting of characters allowed in XML
    void tst_allowedStrings();
    void tst_allowedStrings_data();

    //strings completely consisting of characters disallowed in XML
    void tst_disallowedStrings();
    void tst_disallowedStrings_data();

    //strings consisting of a mix of allowed and disallowed characters
    void tst_mixedStrings();
    void tst_mixedStrings_data();

    //strings consisting of a broken UTF-16 code unit sequences
    void tst_brokenStrings();
    void tst_brokenStrings_data();

    //a basic benchmark
    void bench_loremIpsum();
};

#endif // TST_XMLCHARFILTER_H
