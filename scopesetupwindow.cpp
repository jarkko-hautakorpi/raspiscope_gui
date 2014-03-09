


#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "scopesetupwindow.h"
#include "mainwindow.h"
#include "scopesettings.h"
#include "ui_scopesetupwindow.h"



scopeSetupWindow::scopeSetupWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scopeSetupWindow)
{
    this->foobar = "foobar";
    this->baudRates <<
        "9600" <<
        "56000" <<
        "57600" <<
        "115200" <<
        "128000" <<
        "1000000" <<
        "1228800" <<
        "2000000" <<
        "2457600" <<
        "3000000" <<
        "4000000" <<
        "4915200"
    ;
    ui->setupUi(this);
    ui->textOutputArea->setReadOnly(true);
    // Start and stop signals from buttons
    connect(ui->live_start, SIGNAL(clicked()),
            this, SLOT(SetupWindow_liveStart()));
    connect(ui->live_stop, SIGNAL(clicked()),
            this, SLOT(SetupWindow_liveStop()));

    getSerialPorts();

}

scopeSetupWindow::~scopeSetupWindow()
{
    //scopeSettings *settings;
    //settings = scopeSettings::get();
    delete ui;
}

void scopeSetupWindow::on_actionSetupWindow_reject_triggered()
{
    this->~scopeSetupWindow();
}

void scopeSetupWindow::on_actionSetupWindow_accept_triggered()
{

}

void scopeSetupWindow::SetupWindow_liveStart() {

}

void scopeSetupWindow::SetupWindow_liveStop() {

}

void scopeSetupWindow::getSerialPorts() {

    ui->comboBox_baudSelect->addItems(this->baudRates);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QString portinfo;
        portinfo = "Found port       : ";
        portinfo += info.portName();
        if( info.isBusy())
            portinfo += "   is busy";
        else {
            portinfo += "   is available";
            ui->comboBox_ttyselect->addItem(info.portName());
        }
        this->appendToTextarea(portinfo);

        // Example use QSerialPort
        /*
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
            serial.close();
            */
    }

}

void scopeSetupWindow::appendToTextarea (QString text){
    ui->textOutputArea->appendPlainText(text);
}

