#ifndef THERMOREGULATOR_H
#define THERMOREGULATOR_H

class Thermoregulator
{
    
private:
    double temperature;
public:
    Thermoregulator();
    Thermoregulator(double Temperature);
    double Get_Temperature();
    void Set_Temperature(double newTemperature);
};

#endif