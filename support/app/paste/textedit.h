#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class TextEdit: public QTextEdit
{
    Q_OBJECT

signals:
    void pasteEventHappened(QString info) const;

public:
    TextEdit();

protected:
    bool canInsertFromMimeData(const QMimeData *source) const;
    void insertFromMimeData(const QMimeData * source);
};

#endif // TEXTEDIT_H
