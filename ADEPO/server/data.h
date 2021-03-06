#ifndef DATA_H
#define DATA_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdexcept>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>

#include <QString>
#include <QStringList>

#include "configuration.h"
#include "bcam.h"
#include "dual_spot.h"
#include "mount_coord_spots.h"
#include "mount_coord_prism.h"
#include "global_coord_prism.h"
#include "bcam_params.h"



class Data
{
public:
    //constructeurs et destructeur
    Data() {};
    Data(const Data& /* copie */) {};
    virtual ~Data() {};

    //getter
    std::vector<DualSpot> getDualSpots() const {return mDualSpots;}
    std::vector<MountCoordSpots> getMountCoordSpots() const {return mMountCoordSpots;}
    std::vector<MountCoordPrism> getMountCoordPrisms() const {return mMountCoordPrisms;}
    //gestion des parametres de translation et de rotation par BCAM
    std::vector<BCAMParams> getBCAMParams() const {return mBcamParams;}
    //gestion de la liste des coordonnees du prisme dans le repre global
    std::vector<GlobalCoordPrism> getGlobalCoordPrisms() const {return mGlobalCoordPrisms;}

   //methodes d'ajout
    void add(DualSpot val) {mDualSpots.push_back(val);}
    void add(MountCoordSpots val) {mMountCoordSpots.push_back(val);}
    void add(MountCoordPrism val) {mMountCoordPrisms.push_back(val);}
    //gestion des parametres de translation et de rotation par BCAM
    void add(BCAMParams val) {mBcamParams.push_back(val);}
    //gestion de la liste des coordonnees du prisme dans le repre global
    void add(GlobalCoordPrism val) {mGlobalCoordPrisms.push_back(val);}

    void clear() {
        mDualSpots.clear();
        mMountCoordSpots.clear();
        mMountCoordPrisms.clear();
        mGlobalCoordPrisms.clear();
    }

private:
    std::vector<DualSpot> mDualSpots;
    std::vector<MountCoordSpots> mMountCoordSpots;
    std::vector<MountCoordPrism> mMountCoordPrisms;
    std::vector<BCAMParams> mBcamParams;
    std::vector<GlobalCoordPrism> mGlobalCoordPrisms;

};

#endif // DATA_H
