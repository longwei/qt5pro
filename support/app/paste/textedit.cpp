#include "textedit.h"

#include <QMimeData>
#include <QChar>
#include <QDebug>

#include <algorithm>

//returns true, if the passed character is acceptable in XML
//  ( #x9 | #xA | #xD | [#x20-#xD7FF] | [#xE000-#xFFFD] | [#x10000-#x10FFFF] )
//  and is not the Unicode replacement character ( #xFFFD )
static bool inXMLCharacterRange(uint ch)
{
    return (ch == 0x9) || (ch == 0xA) || (ch == 0xD)
            || (ch >= 0x20 && ch <=0xD7FF)
            || (ch >= 0xE000 && ch < 0xFFFD)
            || (ch >= 0x10000 && ch <= 0x10FFFF);
}

//produces a string which respresents a valid Unicode codepoint sequence,
//  and does not contain characters outside of the range allowed for XML
static QString toXMLCharacterRange(const QString& s)
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
    asUcs4Stripped.reserve(asUcs4.count());
    std::copy_if(asUcs4.begin(), asUcs4.end(), std::back_inserter(asUcs4Stripped), inXMLCharacterRange);

    return QString::fromUcs4(asUcs4Stripped.data(), asUcs4Stripped.count());
}

TextEdit::TextEdit()
{

}

bool TextEdit::canInsertFromMimeData(const QMimeData *source) const
{
    if (source->hasText()) {
        return true;
    } else {
        emit pasteEventHappened("Paste refused: no text in mime data.");
        return false;
    }
}

QString toEscapedString(const QString& s)
{
    QString res;

    for (int i = 0; i < s.count(); i++) {
        res += QString("\\%1").arg(s.at(i).unicode());
    }

    return res;
}

void TextEdit::insertFromMimeData(const QMimeData *source)
{
    QString text = source->text();
    QString stripped = toXMLCharacterRange(text);

    QMimeData strippedData;
    strippedData.setText(stripped);

    QString info = QString() + "pasted: " + toEscapedString(text) + "\n"
                    + "stripped: " + toEscapedString(stripped) + "\n"
                    + "equal: " + ((text == stripped)? "true": "false");

    QTextEdit::insertFromMimeData(&strippedData);
    emit pasteEventHappened(info);
}
