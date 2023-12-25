#include "udp.h"
#include <QDataStream>

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
    qDebug() << "Message: " << buffer;

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


}



