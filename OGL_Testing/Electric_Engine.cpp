#include "Electric_Engine.h"

Electric_Engine::Electric_Engine()
{
    cycles = 0;
    power = 0;
    weight = 0;
}
Electric_Engine::Electric_Engine(double Cycles, double Power, double Weight)
{
    cycles = Cycles;
    power = Power;
    weight = Weight;
}
double Electric_Engine::Get_Power()
{
    return this->power;
}
double Electric_Engine::Get_Cycles()
{
    return this->cycles;
}
double Electric_Engine::Get_Weight()
{
    return this->weight;
}