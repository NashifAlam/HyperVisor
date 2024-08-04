#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#define FrontTyrePressureThreshold 20
#define RearTyrePressureThreshold 24

#define TyreTemperatureThreshold 110

#define BrakeTemperatureThreshold 700
#define BrakeWearThreshold 78

#include <QMainWindow>
#include <QDebug>

//Class defination and initialisation
class preProcessor{
    private:
        int a =10;
        char
            TyreString = 0,
            BrakeString = 0,
            DoorString = 0,
            ToggleString = 0,
            DiagnosticString = 0;
     public:
        //Variables
        int generatedValue;

        //Functions
        //int initialise(int a_1, int a_2, int a_3, int a_4, int a_5, int a_6, int a_7, int a_8);
        //void valueRenderer(int index, int value);
        void checkTyre(int multiplier, bool value);
        void checkBrakes(int multiplier, bool value);
        void checkDoors(int multiplier, bool value);
        void ToggleValues(int mulitplier, bool value);
        void DiagnosticData(int multiplier, bool value);
        void Relay();

};
/*
//Feeding binary values into the array to generate binary string octet
int preProcessor::initialise(int a_1, int a_2, int a_3, int a_4, int a_5, int a_6, int a_7, int a_8);

//Value Renderer: Adding consistency bit to keep value stable
void preProcessor::valueRenderer(int index,int value);


//All sensor check code blocks
//Multiplier determines the value to be toggled, value is binary for checks


void preProcessor::checkTyre(int multiplier, int value);

void preProcessor::checkBrakes(int multiplier, int value);


void preProcessor::checkDoors(int multiplier, int value);


void preProcessor::ToggleValues(int multiplier, int value);

void preProcessor::DiagnosticData(int multiplier, int value);

//Transfer string parser
void preProcessor::Relay();
*/

#endif // MAINFUNCTIONS_H
