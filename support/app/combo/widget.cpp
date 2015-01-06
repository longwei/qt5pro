#include "widget.h"

#include <QWindow>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QApplication>
#include <QDebug>

Widget::Widget()
{
    QWindow* window = new QWindow;
    QWidget* dummy = QWidget::createWindowContainer(window);
    dummy->setMinimumSize(200, 100);

    m_comboBox = new QComboBox;
    m_comboBox->setInsertPolicy(QComboBox::NoInsert);
    m_comboBox->addItem("first");
    m_comboBox->addItem("second");

    typedef void (QComboBox::* currentIndexChangedType)(int);
    QObject::connect(m_comboBox, static_cast<currentIndexChangedType>(&QComboBox::currentIndexChanged),
        [this] (int index)
    {
        qDebug() << "QComboBox::currentIndexChanged(): " << index;

        //This wouldn't help:
        //m_comboBox->setFocus();

        m_comboBox->setEditable(true);

        QObject::connect(m_comboBox->lineEdit(), &QLineEdit::editingFinished, [this]() {
            qDebug() << "QLineEdit::editingFinished()";
            m_comboBox->setEditable(false);
        });
        QObject::connect(m_comboBox->lineEdit(), &QLineEdit::returnPressed, [this]() {
            qDebug() << "QLineEdit::returnPressed()";
            m_comboBox->setItemText(m_comboBox->currentIndex(), m_comboBox->currentText());
        });
    });

    QVBoxLayout* lt = new QVBoxLayout(this);
    lt->addWidget(dummy);
    lt->addWidget(m_comboBox);

    connect( qApp, &QApplication::focusChanged, [] (QWidget* old, QWidget* now) {
        auto logWidget = [](QString s, QWidget* w) {
            if (w)
                qDebug() << s << ": " << w;
            else
                qDebug() << s << ": " << "null";
        };

        logWidget("old focus widget: ", old);
        logWidget("new focus widget: ", now);
    } );
}
