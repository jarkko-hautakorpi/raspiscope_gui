#ifndef SERIALDATALINK_H
#define SERIALDATALINK_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#define USART_RX_BUFFER_SIZE 1024
#define USART_TX_BUFFER_SIZE 32
#define USART_RX_BUFFER_MASK ( USART_RX_BUFFER_SIZE - 1 )
#define USART_TX_BUFFER_MASK ( USART_TX_BUFFER_SIZE - 1 )

/* types from Atmel code */
#define uint8_t (unsigned char)
#define uint16_t (unsigned short int)

class serialDataLink : public QObject
{
    Q_OBJECT

public:
    explicit serialDataLink(QObject *parent = 0);
    typedef volatile struct Settings {
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
    } portSettings_t;

    typedef volatile struct USART_Buffer
    {
        unsigned short int RX[USART_RX_BUFFER_SIZE];
        unsigned short int TX[USART_TX_BUFFER_SIZE];
        unsigned short int RX_Head;
        unsigned short int RX_Tail;
        unsigned short int TX_Head;
        unsigned short int TX_Tail;
    } USART_Buffer_t;

    typedef volatile struct USART_data
    {
        USART_Buffer_t buffer;
    } USART_data_t;

    static bool USART_TXBuffer_FreeSpace(USART_data_t * usart_data);
    static bool USART_TXBuffer_PutByte(USART_data_t * usart_data, unsigned char data);

    int scope_command(unsigned char command, unsigned char param);



private:
    void setControlsEnabled(bool enable);
    void processError(const QString &error);
    
signals:
    void errorMessage(const QString &);
    
public slots:

private slots:
    void sendRequest();
    
};

#endif // SERIALDATALINK_H
