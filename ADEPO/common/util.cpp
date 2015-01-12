#include "util.h"

std::string Util::getSourceDeviceElement(bool isPrism, bool flashSeparate, int deviceElement, bool first) {
    if (flashSeparate) {
        if (isPrism) {
            return deviceElement == 2 ? first ? "3" : "4" : first ? "1" : "2";
        } else {
            return deviceElement == 2 ? first ? "1" : "2" : first ? "3" : "4";
        }
    } else {
        if (isPrism) {
            return deviceElement == 2 ? "3 4" : "1 2";
        } else {
            return deviceElement == 2 ? "1 2" : "3 4";
        }
    }
}


