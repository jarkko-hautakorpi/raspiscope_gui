#include <stdio.h>
#include <stdlib.h>
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "serialdatalink.h"
#include "hdlc.h"


serialDataLink::serialDataLink(QObject *parent) :
    QObject(parent)
{
    volatile portSettings_t portSettings;
    portSettings.baudRate = QSerialPort::Baud115200;
    portSettings.dataBits = QSerialPort::Data8;
    portSettings.flowControl = QSerialPort::NoFlowControl;
    portSettings.localEchoEnabled = 0;
    //portSettings.name = "ttyUSB1";
    portSettings.parity = QSerialPort::NoParity;
    portSettings.stopBits = QSerialPort::OneStop;
}


void serialDataLink::sendRequest()
{
    QSerialPort serial;
    if (serial.portName() !=  "ttyUSB0") {
        serial.close();


        if (!serial.open(QIODevice::ReadWrite)) {
            processError(tr("Can't open %1, error code %2")
                         .arg(serial.portName()).arg(serial.error()));
            return;
        }

        if (!serial.setBaudRate(QSerialPort::Baud9600)) {
            processError(tr("Can't set rate 9600 baud to port %1, error code %2")
                         .arg(serial.portName()).arg(serial.error()));
            return;
        }

        if (!serial.setDataBits(QSerialPort::Data8)) {
            processError(tr("Can't set 8 data bits to port %1, error code %2")
                         .arg(serial.portName()).arg(serial.error()));
            return;
        }

        if (!serial.setParity(QSerialPort::NoParity)) {
            processError(tr("Can't set no patity to port %1, error code %2")
                         .arg(serial.portName()).arg(serial.error()));
            return;
        }

        if (!serial.setStopBits(QSerialPort::OneStop)) {
            processError(tr("Can't set 1 stop bit to port %1, error code %2")
                         .arg(serial.portName()).arg(serial.error()));
            return;
        }

        if (!serial.setFlowControl(QSerialPort::NoFlowControl)) {
            processError(tr("Can't set no flow control to port %1, error code %2")
                         .arg(serial.portName()).arg(serial.error()));
            return;
        }
    }

    //statusLabel->setText(tr("Status: Running, connected to port %1.").arg(serialPortComboBox->currentText()));
    QString qString1 = "?~";
    //serial.write("?~"); // status
}

void serialDataLink::processError(const QString &error)
{
    emit errorMessage(error);

}

bool serialDataLink::USART_TXBuffer_FreeSpace(serialDataLink::USART_data_t * usart_data)
{
    /* Make copies to make sure that volatile access is specified. */
    unsigned char tempHead = (usart_data->buffer.TX_Head + 1) & USART_TX_BUFFER_MASK;
    unsigned char tempTail = usart_data->buffer.TX_Tail;

    /* There are data left in the buffer unless Head and Tail are equal. */
    return (tempHead != tempTail);
}

bool serialDataLink::USART_TXBuffer_PutByte(serialDataLink::USART_data_t * usart_data, unsigned char data)
{
    //unsigned char tempCTRLA;
	unsigned char tempTX_Head;
	bool TXBuffer_FreeSpace;
    serialDataLink::USART_Buffer_t * TXbufPtr;

	TXbufPtr = &usart_data->buffer;
    //TXBuffer_FreeSpace = serialDataLink::USART_TXBuffer_FreeSpace(serialDataLink::USART_data_t * usart_data);
    unsigned char tempHead = (usart_data->buffer.TX_Head + 1) & USART_TX_BUFFER_MASK;
    unsigned char tempTail = usart_data->buffer.TX_Tail;
    TXBuffer_FreeSpace = tempHead != tempTail;
    if(TXBuffer_FreeSpace)
	{
	  	tempTX_Head = TXbufPtr->TX_Head;
	  	TXbufPtr->TX[tempTX_Head]= data;
		/* Advance buffer head. */
		TXbufPtr->TX_Head = (tempTX_Head + 1) & USART_TX_BUFFER_MASK;
	}
	return TXBuffer_FreeSpace;
}


int serialDataLink::scope_command(unsigned char command, unsigned char param = 0)
{
    return 1;
}


