#include <QApplication>
#include <QtGui>
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QUrl>
#include <QString>

#include "client.h"
#include "socket_client.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Util::setApplicationInfo("ADEPO client");
    Util::handleDebug(app);

    Client client;
    client.changedState(ADEPO_UNKNOWN, 0, LWDAQ_UNKNOWN, 0);

    SocketClient webSocketClient(client, QStringLiteral("ws://localhost:5687"));
    client.setServer(webSocketClient);
    client.show();


    return app.exec();
}
