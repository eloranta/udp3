#include <QCoreApplication>
#include "udp.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    udp udp;
    return app.exec();
}
