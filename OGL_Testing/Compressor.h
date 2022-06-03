#ifndef COMPRESSOR_H
#define COMPRESSOR_H

class Compressor
{

private:
    double pressure;
    double power;
    double weight;
    double minimal_temperature;
 
public:
    Compressor();
    Compressor(double Pressure, double Power, double Weight, double Minimal_Temperature);
    double Get_Power();
    double Get_Pressure();
    double Get_Weight();    
    double Get_Minimal_Temperature();

};
#endif