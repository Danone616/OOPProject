#include "Processing_Unit.h"

Processing_Unit::Processing_Unit()
{
    power = 0;
    power_meter = 1;
    target_temperature = 0;
}
Processing_Unit::Processing_Unit(double Power, double Target_Temperature)
{
    power = Power;
    power_meter = 1;
    target_temperature = Target_Temperature;
}
void Processing_Unit::Set_Power_Meter(double Power_Meter)
{
    this->power_meter = Power_Meter;
}
void Processing_Unit::Set_Target_Temperature(double Target_Temperature)
{
    this->target_temperature = Target_Temperature;
}
double Processing_Unit::Get_Power_Meter()
{
    return this->power_meter;
}
double Processing_Unit::Get_Target_Temperature()
{
    return this->target_temperature;
}
double Processing_Unit::Get_Power()
{
    return this->power;
}