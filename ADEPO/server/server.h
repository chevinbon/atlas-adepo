#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <fstream>
#include <iomanip>

#include <QObject>
#include <QString>
#include <QFile>
#include <QTimer>

#include "bcam.h"
#include "calibration.h"
#include "configuration.h"
#include "data.h"
#include "reference.h"
#include "run.h"

#include "lwdaq_client.h"
#include "point3f.h"
#include "setup.h"
#include "call.h"
#include "callback.h"

class Server : public QObject, public Call
{
    Q_OBJECT

public:
    Server(Callback& callback, QObject *parent = 0);
    ~Server() {};

    void startDAQ(QString runMode, int runTime, bool airpad, std::vector<int> detectors);
    void stopDAQ();
    QString calculateCoordinates();
    int readLWDAQOutput();

    // implementation of Call
    void start();
    void stop();
    void update();

private slots:
    void lwdaqStateChanged();
    void timeChanged();
    void startDAQ();

private:
    Callback& callback;

    int writeSettingsFile(QString settings_file);
    int writeParamsFile(QString params_file);
    int writeScriptFile(QString fileName);

    QString getDateTime();
    int writeBCAMScript(Configuration &config, std::ofstream &file, BCAM bcam, int spots, QString sourceDeviceElement);

    void imgCoordToBcamCoord(Calibration &calibration, Setup &setup, Data &data);
    void calculCoordBcamSystem(Configuration &config, Calibration &calibration, Setup &setup, Data& data);
    void mountPrismToGlobalPrism();
    int writeFileObsMountSystem(QString fileName, QString datetime);
    Point3f changeReference(Point3f coord_sys1, Point3f translation, Point3f rotation);

    void helmert(Configuration &config, Data& data);

    void updateState();

    QTimer *waitingTimer;
    QTimer *updateTimer;

    QString adepoState;
    QString runMode;
    int runTime;
    bool useAirpads;
    std::vector<int> detectors;

    QString resultFile;
    QString scriptFile;

    LWDAQ_Client *lwdaq_client;
    QString previousState;
    bool needToCalculateResults;

    Configuration config;
    Calibration calibration;
    Setup setup;
    Data data;
    Reference reference;
    Run run;
};

#endif // SERVER_H

