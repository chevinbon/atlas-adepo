#ifndef GLOBAL_COORD_PRISM_H
#define GLOBAL_COORD_PRISM_H

#include "bcam.h"

class GlobalCoordPrism
{
public:
    GlobalCoordPrism(BCAM bcam, Point3d coordPrismMountSys, float airpad) :
        mBCAM(bcam), mCoordPrismMountSys(coordPrismMountSys), mAirpad(airpad) {};
    virtual ~GlobalCoordPrism() {};

    //getter setter
    BCAM getBCAM() const {return mBCAM; }
    Prism getPrism() const {return mBCAM.getPrism(); }
    QString getName() const { return getBCAM().getName()+"_"+getPrism().getName(); }
    Point3d getCoordPrismMountSys() const {return mCoordPrismMountSys; }

    float getAirpad() { return mAirpad; }

    //methodes
    void print() {
        std::cout<<"*******************************************global coordinates of prism*******************************************"<<std::endl;
        std::cout<<"Objet BCAM : "<<getBCAM().getName().toStdString()<<std::endl;
        std::cout<<"Objet Prism : "<<getPrism().getName().toStdString()<<std::endl;
        std::cout<<"Coordonnées du prisme dans le systeme global : "<<std::endl;
        getCoordPrismMountSys().print();
    }

protected:
private:
    BCAM mBCAM;
    Point3d mCoordPrismMountSys;
    float mAirpad;
};

#endif // GLOBAL_COORD_PRISM_H
