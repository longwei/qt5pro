#include "widget.h"
#include <QVBoxLayout>

Widget::Widget()
{
    QVBoxLayout* lt  = new QVBoxLayout(this);

    m_edit = new TextEdit;
    connect( m_edit, SIGNAL(pasteEventHappened(QString)), SLOT(onPasteEventHappened(QString)) );
    lt->addWidget(m_edit);

    m_view = new QTextEdit;
    m_view->setReadOnly(true);

    m_view->resize(400, 300);
    m_view->show();
//    lt->addWidget(m_view);
}

void Widget::onPasteEventHappened(const QString &info)
{
    m_view->append(info);
}
/*

//produces a string which respresents a valid Unicode codepoint sequence,
//  and does not contain characters outside of the range allowed for XML
QString Conversation::toXMLCharacterRange( const QString& s )
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

QXmppMessage Conversation::createMessageToSend( const QString& body )
{
    QXmppMessage message;
    message.setTo( m_jid );
    message.setType( m_type );

    //this will remove all characters prohibited in XML
    QString bodySanitized = toXMLCharacterRange( body );
    //if at this point the message is whitespace-only, it will be replaced with a single space
    //  (empty bodies currently result in warning signs appearing next to messages several seconds after they are sent)


    qDebug() << "body:" << body;
    qDebug() << "bodySanitized:" << bodySanitized;
    qDebug() << "bodySanitized.trimmed():" << bodySanitized.trimmed();
    qDebug() << "bodySanitized.trimmed().isEmpty():" << bodySanitized.trimmed().isEmpty();

    message.setBody( (bodySanitized.trimmed().isEmpty()) ? qll(" "): bodySanitized );


    qDebug() << "message.body()" << message.body();

    s_messageId++;
    QString messageId = qll("message_") % QString::number( s_messageId );
    message.setId( messageId );
    return message;
}

*/
