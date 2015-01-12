#ifndef UTIL_H
#define UTIL_H

#include <string>

class Util
{
public:
    Util() {};
    virtual ~Util() {};

    static std::string getSourceDeviceElement(bool isPrism, bool flashSeparate, int deviceElement, bool first);

    static void checkCalibrationDatabase();
};

#endif // UTIL_H
