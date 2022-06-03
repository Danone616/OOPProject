#include "Thermoregulator.h"

Thermoregulator::Thermoregulator()
{
    temperature = 0;
}
Thermoregulator::Thermoregulator(double Temperature)
{
    temperature = Temperature;
}
double Thermoregulator::Get_Temperature()
{
    return this->temperature;
}
void Thermoregulator::Set_Temperature(double newTemperature)
{
    this->temperature = newTemperature;
}