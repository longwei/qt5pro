#ifndef WIDGET_H
#define WIDGET_H

#include <QComboBox>

class Widget: public QWidget
{
    Q_OBJECT
public:
    Widget();

private:
    QComboBox* m_comboBox;
};

#endif // WIDGET_H
