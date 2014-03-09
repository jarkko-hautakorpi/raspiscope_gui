#ifndef SCOPESETTINGS_H
#define SCOPESETTINGS_H
#include <map>
#include <string>
#include <iostream>
#include <QObject>

class scopeSettings : public QObject
{
public:
    static scopeSettings& get();

    struct portSettings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };


private:
    scopeSettings();
    static scopeSettings *settings;
    scopeSettings(scopeSettings const&);
    void operator=(scopeSettings const&);



};

// Settings is a global, singleton that is available for everyone
// in this application

//static scopeSettings settings;

#endif // SCOPESETTINGS_H
