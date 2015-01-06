#ifndef WIDGET_H
#define WIDGET_H

#include "textedit.h"

class Widget: public QWidget
{
    Q_OBJECT
public:
    Widget();

private slots:
    void onPasteEventHappened(const QString& info);

private:
    TextEdit* m_edit;
    QTextEdit* m_view;
};

#endif // WIDGET_H
