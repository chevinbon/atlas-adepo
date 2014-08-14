#ifndef PRISM_CORRECTION_H
#define PRISM_CORRECTION_H

#include "iostream"
#include "Point3f.h"

class prism_correction
{
public:
    prism_correction(std::string prism, Point3f delta) : mPrism(prism), mDelta(delta) {};
    virtual ~prism_correction() {};

    //setter et getter
    std::string getPrism() const {return mPrism;}

    Point3f getDelta() const {return mDelta;}

    //methodes
    void print() {
        std::cout<<"*******************************************Correction excentrement*******************************************"<<std::endl;
        std::cout<<"Identifiant du prisme : "<<getPrism()<<std::endl;
        std::cout<<"Valeur d'excentrement : "<<std::endl;
        getDelta().print();
    }

protected:
private:
    std::string mPrism;
    Point3f mDelta;
};

#endif // PRISM_CORRECTION_H
