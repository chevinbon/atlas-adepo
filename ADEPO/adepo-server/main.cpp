#include <QtCore/QCoreApplication>

#include "server.h"
#include "socket_server.h"
#include "util.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Util::setApplicationInfo("ADEPO server");
    Util::handleDebug(app);

    std::cout << app.applicationName().toStdString() << " " << app.applicationVersion().toStdString() << std::endl;

    SocketServer webSocketServer(5687);
    Server server(webSocketServer);
    webSocketServer.setServer(server);

//    QObject::connect(&webSocketServer, &SocketServer::closed, &app, &QCoreApplication::quit);

    return app.exec();
}
