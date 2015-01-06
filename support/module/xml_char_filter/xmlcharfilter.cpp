#include "xmlcharfilter.h"

#include <QRegularExpression>
#include <algorithm>

//returns true, if the passed character is acceptable in XML
//  ( #x9 | #xA | #xD | [#x20-#xD7FF] | [#xE000-#xFFFD] | [#x10000-#x10FFFF] )
//  and is not the Unicode replacement character ( #xFFFD )
static bool inXMLCharacterRange( uint ch )
{
    return ( ch == 0x9 ) || ( ch == 0xA ) || ( ch == 0xD )
            || ( ch >= 0x20 && ch <=0xD7FF )
            || ( ch >= 0xE000 && ch < 0xFFFD )
            || ( ch >= 0x10000 && ch <= 0x10FFFF );
}

QString toXMLCharacterRange1( const QString& s )
{
    //this gives a sanitized string
    //  with invalid codepoint sequences replaced with Unicode replacement character
    //  (http://qt-project.org/doc/qt-5/qstring.html#toUcs4),
    //  and the surrogate pairs combined
    //  (http://www.unicode.org/faq/utf_bom.html#utf32-6)
    QVector<uint> asUcs4 = s.toUcs4();

    //now, the Unicode replacement character
    //  (http://qt-project.org/doc/qt-5/qchar.html#SpecialCharacter-enum),
    //  and the characters illegal in XML
    //  (http://www.w3.org/TR/2000/REC-xml-20001006#NT-Char)
    //  should be removed
    QVector<uint> asUcs4Stripped;
    asUcs4Stripped.reserve( asUcs4.count() );
    std::copy_if( asUcs4.begin(), asUcs4.end(), std::back_inserter(asUcs4Stripped), inXMLCharacterRange );

    return QString::fromUcs4( asUcs4Stripped.data(), asUcs4Stripped.count() );
}

//removes the characters illegal in XML and the Unicode replacement character;
//  the input string is assumed to have a valid UTF-16 layout (no broken surrogate sequences or standalone surrogates),
//  otherwise it will be returned unmodified, with nothing replaced
//
//  the characters *allowed* in XML are (http://www.w3.org/TR/2000/REC-xml-20001006#NT-Char):
//  ( \x9, \xA, \xD, [\x20-\xD7FF], [\xE000-\xFFFD], [\x10000-\x10FFFF] )
//
//  the Unicode replacement character is:
//  \xFFFD
QString toXMLCharacterRange2( const QString& s )
{
    //note: QRegularExpression internally uses PCRE, asking it to check if the string is a valid UTF-16 one first,
    //  if this check fails, no matching (or replacement) takes place (and the string is returned as is)

    //assumes anything in the [\xD800-\xDFF] is a part of a valid surrogate pair,
    //  and anything above \x10000 (inclusive) is valid
    static const QRegularExpression re( "[\\x{0}-\\x{8}]|\\x{B}|\\x{C}|[\\x{E}-\\x{1F}]|\\x{FFFD}|\\x{FFFE}|\\x{FFFF}" );

    return QString( s ).remove( re );
}

//produces a string which respresents a valid Unicode codepoint sequence,
//  and does not contain characters outside of the range allowed for XML
//  (or the Unicode replacement character)
QString toXMLCharacterRange( const QString& s )
{
    return toXMLCharacterRange2(s);
}
