#ifndef ELECTRIC_ENGINE_H
#define ELECTRIC_ENGINE_H

class Electric_Engine
{
private:
    double cycles;
    double power;
    double weight;
public:
    Electric_Engine();
    Electric_Engine(double Cycles, double Power, double Weight);
    double Get_Power();
    double Get_Cycles();
    double Get_Weight();
};

#endif