#include "udp.h"
#include <QDataStream>
#include <QTime>

udp::udp(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 2237);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void udp::readyRead()
{
    QByteArray buffer;
    buffer.resize(static_cast<int>(socket->pendingDatagramSize()));

    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    //qDebug() << "Message from: " << sender.toString();
    //qDebug() << "Message port: " << senderPort;
    //qDebug() << "Message: " << buffer;

    ParseMessage(buffer);
}

void udp::ParseMessage(QByteArray& buffer)
{
    //qDebug() << "Message: " << buffer;

    QDataStream stream(&buffer, QIODevice::ReadOnly);
    quint32 magic;
    stream >> magic;
    if (magic != 0xadbccbda)
    {
        qDebug() << "Magic number not correct: " << magic;
        return;
    }

    quint32 schema;
    stream >> schema;
    if (schema != 2)
    {
        qDebug() << "Schema number not 2: " << schema;
        return;
    }
    quint32 messageNumber;
    stream >> messageNumber;

    //qDebug() << messageNumber;

    switch(messageNumber)
    {
    case Heartbeat:
        qDebug() << "Heartbeat";
        break;
    case Status:
        qDebug() << "Status";
        break;
    case Decode:
        //qDebug() << "Decode";
        decode(stream);
        break;
    case Clear:
        qDebug() << "Clear";
        break;
    case QSOLogged:
        qDebug() << "QSOLogged";
        break;
    case Close:
        qDebug() << "Close";
        break;
    case WSPRDecode:
        qDebug() << "WSPRDecode";
        break;
    case LoggedADIF:
        qDebug() << "LoggedADIF";
        break;
    default:
        qDebug() << "Unknown message number received: " << messageNumber;
        break;
    }
}

void udp::decode(QDataStream &stream)
{
    uint len;
    char *raw;
    stream.readBytes(raw, len);
    QString id = QString::fromUtf8(raw, static_cast<int>(len));
    bool New = false;
    QTime Time;
    qint32 snr;
    double deltaTime;
    quint32 deltaFrequency;
    stream >> New >> Time >> snr >> deltaTime >> deltaFrequency;
    qDebug() << "Id =" << id << "New =" << New << "Time =" << Time << "SNR =" << snr
             << "DT =" << deltaTime << "DF =" << deltaFrequency;


}




