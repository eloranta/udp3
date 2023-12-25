#ifndef udp_h
#define udp_h

#include <QObject>
#include <QUdpSocket>

#include <QObject>

class udp : public QObject
{
    Q_OBJECT
private:
    QUdpSocket *socket;
    void ParseMessage(QByteArray& buffer);
public:
    explicit udp(QObject *parent = nullptr);

signals:

public slots:
    void readyRead();
};

#endif
