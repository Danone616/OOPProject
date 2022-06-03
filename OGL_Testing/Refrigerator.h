#ifndef REFRIGERATOR_H
#define REFRIGERATOR_H

#include "Compressor.h"
#include "Electric_Engine.h"
#include "Processing_Unit.h"
#include "Thermoregulator.h"

class Refrigerator
{
    //Components
public:
    class Refrigerator_Body
    {
    private:
        double height;
        double depth;
        double width;
        double weight;
    public:
        Refrigerator_Body();
        Refrigerator_Body(double Height, double Depth, double Width, double Weight);
        double Get_Weight();
    };
    class Refrigerator_Isolation
    {
    private:
        double isolation_quality;
    public:
        Refrigerator_Isolation();
        Refrigerator_Isolation(double quality);
        double Get_Quality();
    };
private:
    Electric_Engine engine;
    Compressor compressor;
    Processing_Unit processor;
    Refrigerator_Body body;
    Refrigerator_Isolation isolation;
public:
    Thermoregulator thermoregulator;
    Refrigerator();
    Refrigerator(Electric_Engine newengine, Compressor newcompressor, Thermoregulator newthermoregulator, Processing_Unit newprocessor, int height, int depth, int width, int body_weight, double quality);
    double Update_Refrigerator(bool Is_Open, double Item_Weight, double Enviroment_temperature, double Enviroment_Speed);
    void Output_State();
    void Output_State(bool IsOpen, double ItemWeight);
};

#endif