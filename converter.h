#ifndef CONVERTER_H
#define CONVERTER_H
#define PI 3.14159265359

class Converter
{
public:
    static double degToRad(double _deg);
    static double radToDeg(double _rad);
private:
 // Disallow creating an instance of this object
    Converter() {}

};

#endif // CONVERTER_H
