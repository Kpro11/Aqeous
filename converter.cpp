#include "converter.h"

double Converter::degToRad(double _deg) {
    return _deg * PI / 180;
}

double Converter::radToDeg(double _rad) {
    return _rad * 180 / PI;
}


