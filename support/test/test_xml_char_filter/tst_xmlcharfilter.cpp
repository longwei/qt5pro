#include "tst_xmlcharfilter.h"

#include <xmlcharfilter.h>

#include <QVector>
#include <QtTest>

//as VS2013 does not support u8, u, and U prefixes for encodings,
//  and Unicode character specification with \u and \U
//  (http://msdn.microsoft.com/en-us/library/69ze775t.aspx),
//  the two helper functions below are used when necessary in the tests
//
//  (Note: g++, on the contrary, works fine, allowing constructs like:
//    QTest::newRow("\\uFFFD") << u8"\uFFFD";)

//returns a QString consisting of a QChar sequence for the given code point
static QString fromCodePoint( uint codePoint )
{
    uint string[] = { codePoint };
    return QString::fromUcs4( string, 1 );
}

//returns a QString consisting of a QChar sequence for the given code point sequence
static QString fromCodePoints( const QVector<uint>& codePoints )
{
    return QString::fromUcs4( codePoints.data(), codePoints.length() );
}

void Tst_toXMLCharacterRange::tst_allowedStrings()
{
    QFETCH( QString, allowedString );
    QCOMPARE( toXMLCharacterRange( allowedString ), allowedString );
}

void Tst_toXMLCharacterRange::tst_allowedStrings_data()
{
    QTest::addColumn<QString>( "allowedString" );

    //various combinations from the low (ASCII) code point range
    QTest::newRow("empty") << "";
    QTest::newRow("latin characters") << "abc";
    QTest::newRow("latin characters with spaces and \\t") << "abc DEF\tghi \t\tJK";
    QTest::newRow("\\n") << "\\n";
    QTest::newRow("\\r") << "\\r";
    QTest::newRow("a mix of \\n and \\r") << "\n\r\n\n\r\r";
    QTest::newRow("a mix of latin characters with spaces, \\t, \\n, and \\r") << "ab c\td e\nf\rg\n\\rh\t\n\r";

    //boundaries of allowable code point ranges
    QTest::newRow("\\u0020") << fromCodePoint( 0x0020 );
    QTest::newRow("\\uD7FF") << fromCodePoint( 0xD7FF );

    QTest::newRow("\\uE000") << fromCodePoint( 0xE000 );
    QTest::newRow("\\uFFFC") << fromCodePoint( 0xFFFC );

    QTest::newRow("\\u10000") << fromCodePoint( 0x10000 );
    QTest::newRow("\\u10FFFF") << fromCodePoint( 0x10FFFF );
}

void Tst_toXMLCharacterRange::tst_disallowedStrings()
{
    QFETCH( QString, disallowedString );
    QCOMPARE( toXMLCharacterRange( disallowedString ), QString("") );
}

void Tst_toXMLCharacterRange::tst_disallowedStrings_data()
{
    QTest::addColumn<QString>("disallowedString");

    //code point \x0
    QTest::newRow("\\0") << fromCodePoint( 0 );

    //disallowed code points from \x1 up to \xE, inclusive
    QTest::newRow("\\1") << "\x1";
    QTest::newRow("\\2") << "\x2";
    QTest::newRow("\\3") << "\x3";
    QTest::newRow("\\4") << "\x4";
    QTest::newRow("\\5") << "\x5";
    QTest::newRow("\\6") << "\x6";
    QTest::newRow("\\7") << "\x7";
    QTest::newRow("\\8") << "\x8";
    // \t (\x9) and \n (\xA) are allowed
    QTest::newRow("\\xB") << "\xB";
    QTest::newRow("\\xC") << "\xC";
    // \r (\xD) is allowed
    QTest::newRow("\\xE") << "\xE";

    //code points \xF to \x1F, inclusive (in a single UTF-8 string)
    char codePoints[ 0x10 + 1 ] = { 0 }; //zero filled + a zero terminator
    for ( unsigned i = 0; i < sizeof( codePoints ) - 1; i++ )
        codePoints[ i ] = 0xF + i;
    QTest::newRow("[\\xF-\\x1F]") << QString::fromUtf8( codePoints );

    //broken surrogate pairs not tested for

    //code point 0xFFFD (Unicode replacement character)
    QTest::newRow("\\uFFFD") << fromCodePoint( 0xFFFD );

    //code point 0xFFFE
    QTest::newRow("\\uFFFE") << fromCodePoint( 0xFFFE );

    //code point 0xFFFF
    QTest::newRow("\\uFFFF") << fromCodePoint( 0xFFFF );
}

void Tst_toXMLCharacterRange::tst_mixedStrings()
{
    QFETCH( QString, string );
    QFETCH( QString, result );

    QCOMPARE( toXMLCharacterRange( string ), result );
}

void Tst_toXMLCharacterRange::tst_mixedStrings_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    QTest::newRow("allowed ASCII and disallowed low code points") << "abc\x1 def\x2 ghi" << "abc def ghi";
    QTest::newRow("allowed ASCII and \\uFFFD, \\uFFFE and \\uFFFF")
            << ( "abc" + fromCodePoint( 0xFFFD ) + " def" + fromCodePoint( 0xFFFF ) + " ghi" + fromCodePoint( 0xFFFE ) )
            << "abc def ghi";

    QTest::newRow("allowed high code points and disallowed low code points")
            << fromCodePoints( { 0x0100, 0x1, 0xD7FF, 0x2, 0x10000, 0x3, 0x10FFFE } )
            << fromCodePoints( { 0x0100, 0xD7FF, 0x10000, 0x10FFFE } );

    QTest::newRow("allowed high code points and \\uFFFD, \\uFFFE and \\uFFFF")
            << fromCodePoints( { 0x0100, 0xFFFD, 0xD7FF, 0xFFFE, 0x10000, 0xFFFF, 0x10001 } )
            << fromCodePoints( { 0x0100, 0xD7FF, 0x10000, 0x10001 } );

    QTest::newRow("a combination of ASCII, including line terminators, and high code points")
            << "abc\n\r" + fromCodePoint( 0xFFFD ) + "\t" + fromCodePoint( 0xFFFE ) + " def" + fromCodePoints( { 0x10000, 0x1F, 0xFFFF } )
            << "abc\n\r\t def" + fromCodePoint( 0x10000 );
}

void Tst_toXMLCharacterRange::tst_brokenStrings()
{
    QFETCH( QString, brokenString );
    QCOMPARE( toXMLCharacterRange( brokenString ), brokenString );
}

void Tst_toXMLCharacterRange::tst_brokenStrings_data()
{
    QTest::addColumn<QString>("brokenString");

    QTest::newRow("single high surrogate") << QString( QChar( 0xD800 ) );
    QTest::newRow("single low surrogate") << QString( QChar( 0xDC00 ) );
    QTest::newRow("a low surrogate followed by a high surrogate") << ( QString( QChar( 0xDC00 ) ) + QString( QChar( 0xD800) ) );

    QTest::newRow("single high surrogate, and a character disallowed in XML") << ( QString( QChar( 0xD800 ) ) + "\x1" );
    QTest::newRow("single low surrogate, and a character disallowed in XML") << ( QString( QChar( 0xDC00 ) )  + "\x1" );
    QTest::newRow("a low surrogate followed by a high surrogate, and a character disallowed in XML") << ( QString( QChar( 0xDC00 ) ) + QString( QChar( 0xD800 ) )  + "\x1" );
}

void Tst_toXMLCharacterRange::bench_loremIpsum()
{
    QString s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed vel sodales nisi. "
                "Sed a ante non nibh cursus aliquet eu a libero. Nunc turpis diam, molestie quis risus id, "
                "molestie malesuada sem. Donec accumsan auctor erat, ac iaculis nisi efficitur quis. "
                "Maecenas sed imperdiet quam. Nunc tristique vehicula quam, sit amet lobortis ligula accumsan in. "
                "Morbi ut semper tortor, id aliquet quam. Curabitur felis felis, pellentesque ac imperdiet ac, "
                "vestibulum eget ligula. Aenean venenatis quam a viverra ultricies. Aenean convallis, purus "
                "vestibulum iaculis scelerisque, odio urna porta felis, id dapibus ex tortor sed neque. "
                "Aliquam vel facilisis turpis. Nunc ac bibendum dolor. Donec venenatis venenatis tortor "
                "rhoncus hendrerit. Aliquam id arcu eu urna fringilla varius at vel nisl.";

    QBENCHMARK {
        toXMLCharacterRange( s );
    }
}
