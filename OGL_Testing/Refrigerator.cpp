#include "Refrigerator.h"
#include <iostream>

Refrigerator::Refrigerator()
{
    engine = Electric_Engine();
    compressor = Compressor();
    thermoregulator = Thermoregulator();
    processor = Processing_Unit();
    body = Refrigerator_Body();
    isolation = Refrigerator_Isolation();
}
Refrigerator::Refrigerator(Electric_Engine newengine, Compressor newcompressor, Thermoregulator newthermoregulator, Processing_Unit newprocessor, int height, int depth, int width, int body_weight, double quality)
{
    engine = newengine;
    compressor = newcompressor;
    thermoregulator = newthermoregulator;
    processor = newprocessor;
    body = Refrigerator_Body(height, depth, width, body_weight);
    isolation = Refrigerator_Isolation(quality);
}

double Refrigerator::Update_Refrigerator(bool Is_Open, double Item_Weight, double Enviroment_temperature, double Enviroment_Speed)
{
    double transfer_coeficient;
    double timestep = 0.01;
    if (Is_Open) transfer_coeficient = 1;
    else transfer_coeficient = (1 - this->isolation.Get_Quality());

    double TotalWeight = Item_Weight + engine.Get_Weight() + compressor.Get_Weight() + body.Get_Weight();
    double Speed = engine.Get_Cycles() * compressor.Get_Pressure() * processor.Get_Power_Meter();
    double Power = (engine.Get_Power() + compressor.Get_Power() + processor.Get_Power()) * processor.Get_Power_Meter();

    double Target = processor.Get_Target_Temperature();
    double Current = thermoregulator.Get_Temperature();

    if (Target > Current)
    {
        double Cold = 0;
        double Warm = TotalWeight * Current;
        double Hot = (TotalWeight * Enviroment_Speed * transfer_coeficient * Enviroment_temperature) * timestep;

        double Change = (Cold + Warm + Hot) / (TotalWeight + (TotalWeight * Enviroment_Speed * transfer_coeficient));

        thermoregulator.Set_Temperature(Change);
        return 0;
    }
    else
    {
        double Cold = (Speed * compressor.Get_Minimal_Temperature())*timestep;
        double Warm = TotalWeight * Current;
        double Hot = (TotalWeight * Enviroment_Speed * transfer_coeficient * Enviroment_temperature)*timestep;

        double Change = (Cold + Warm + Hot) / (Speed + TotalWeight + (TotalWeight * Enviroment_Speed * transfer_coeficient));

        thermoregulator.Set_Temperature(Change);

        return Power;
    }
}
void Refrigerator::Output_State()
{
    std::cout<<this->thermoregulator.Get_Temperature()<<std::endl;
}
void Refrigerator::Output_State(bool IsOpen, double ItemWeight)
{
    if (this->thermoregulator.Get_Temperature() >= 0) std::cout<<this->thermoregulator.Get_Temperature();
    else std::cout<<this->thermoregulator.Get_Temperature();
    if (IsOpen) std::cout<<"     Open       ";
    else std::cout<<"     Closed     ";
    std::cout<<ItemWeight<< std::endl;
}
Refrigerator::Refrigerator_Body::Refrigerator_Body()
{
    height = 0;
    depth = 0;
    width = 0;
    weight = 0;
}
Refrigerator::Refrigerator_Body::Refrigerator_Body(double Height, double Depth, double Width, double Weight)
{
    height = Height;
    depth = Depth;
    width = Width;
    weight = Weight;
}
double Refrigerator::Refrigerator_Body::Get_Weight()
{
    return this->weight;
}
Refrigerator::Refrigerator_Isolation::Refrigerator_Isolation()
{
    isolation_quality = 0;
}
Refrigerator::Refrigerator_Isolation::Refrigerator_Isolation(double quality)
{
    isolation_quality = quality;
}
double Refrigerator::Refrigerator_Isolation::Get_Quality()
{
    return this->isolation_quality;
}