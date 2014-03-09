#ifndef SCOPESETUPWINDOW_H
#define SCOPESETUPWINDOW_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class scopeSetupWindow;
}

class scopeSetupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit scopeSetupWindow(QWidget *parent = 0);
    ~scopeSetupWindow();
    
private slots:
    void on_actionSetupWindow_reject_triggered(); // Cancel
    void on_actionSetupWindow_accept_triggered(); // Ok
    void SetupWindow_liveStart(); // Start
    void SetupWindow_liveStop();  // Stop

private:
    QString foobar;
    QStringList baudRates;
    Ui::scopeSetupWindow *ui;
    void getSerialPorts(void);
    void appendToTextarea (QString text);



signals:
    void setStatusbarTextSignal(const QString& text);
    void on_actionSetupWindow_liveStartSignal(); // Start
    void on_actionSetupWindow_liveStopSignal();  // Stop

};

#endif // SCOPESETUPWINDOW_H
