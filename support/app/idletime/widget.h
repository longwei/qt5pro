#ifndef WIDGET_H
#define WIDGET_H

#include "idlewatch.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

class Widget: public QWidget
{
    Q_OBJECT
public:
    Widget(int idleTimeout=3, int startDelay=10);
    ~Widget();

private slots:
    void onStartButtonClicked();
    void start();

    void onIdleWatchingChanged();
    void onIdleWatchIdleChanged();

private:
    IdleWatch m_idleWatch;

    QLineEdit* m_idleTimeoutEdit;
    QLineEdit* m_startTimeoutEdit;

    QPushButton* m_startButton;

    QTextEdit* m_idleWatchLog;
};

#endif // WIDGET_H
