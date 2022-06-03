#ifndef PROCESSING_UNIT_H
#define PROCESSING_UNIT_H


class Processing_Unit
{
private:
    double target_temperature;
    double power_meter;
    double power;
    bool is_on;
public:
    
    Processing_Unit();
    Processing_Unit(double Power, double Target_Temperature);
    void Set_Power_Meter(double Power_Meter);
    void Set_Target_Temperature(double Target_Temperature);
    void Set_State(bool newstate);
    double Get_Power_Meter();
    double Get_Target_Temperature();
    double Get_Power();
    bool Get_State();
};

#endif