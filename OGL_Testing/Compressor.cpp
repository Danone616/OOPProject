#include "Compressor.h"

Compressor::Compressor()
{
    pressure = 0;
    power = 0;
    weight = 0;
    minimal_temperature = 0;
}
Compressor::Compressor(double Pressure, double Power, double Weight, double Minimal_Temperature)
{
    pressure = Pressure;
    power = Power;
    weight = Weight;
    minimal_temperature = Minimal_Temperature;
}
double Compressor::Get_Power()
{
    return this->power;
}
double Compressor::Get_Pressure()
{
    return this->pressure;
}
double Compressor::Get_Weight()
{
    return this->weight;
}
double Compressor::Get_Minimal_Temperature()
{
   return this->minimal_temperature;
}
