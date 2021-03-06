#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <vector>

#include <QString>

#include "calib1.h"
#include "calib2.h"

#define CALIBRATION_FILE "BCAM_Parameters.txt"

class Calibration
{
public:
    Calibration() {};
    ~Calibration() {};

    int read(QString filename);
    QString getFilename() const { return filename; }
    std::string check() const;

    std::vector<Calib1> getCalibs1() const {return mCalibs1;}
    std::vector<Calib2> getCalibs2() const {return mCalibs2;}

    void clear() {
        mCalibs1.clear();
        mCalibs2.clear();
    }

private:
    QString filename;

    void add(Calib1 val) { mCalibs1.push_back(val); }
    void add(Calib2 val) { mCalibs2.push_back(val);}

    std::vector<Calib1> mCalibs1;
    std::vector<Calib2> mCalibs2;

};

#endif // CALIBRATION_H
