//#ifndef MAINFUNCTIONS_H
//#define MAINFUNCTIONS_H
#include "mainFunctions.h"
#define FrontTyrePressureThreshold 20
#define RearTyrePressureThreshold 24

#define TyreTemperatureThreshold 110

#define BrakeTemperatureThreshold 700
#define BrakeWearThreshold 78

#include <QMainWindow>
#include <QDebug>



//Class defination and initialisation
/*class preProcessor{
private:
    int a =10;
    int TyreString = 0,
        BrakeString = 0,
        DoorString = 0,
        ToggleString = 0,
        DiagnosticString = 0;
public:
    //Variables
    int generatedValue;

    //Functions
    int initialise();
    void valueRenderer(int index, bool value);
    void checkTyre(int shifter, bool value);
    void checkBrakes(int shifter, bool value);
    void checkDoors(int shifter, bool value);
    void ToggleValues(int mulitplier, bool value);
    void DiagnosticData(int shifter, bool value);
    void Relay();

};/*

//Feeding binary values into the array to generate binary string octet
int preProcessor::initialise()
{
    int A[8]={a_1,a_2,a_3,a_4,a_5,a_6,a_7,a_8};
    int output =0;
    for(int temp =0, shifter=10000000; temp <8; temp++)
    {
        output += shifter * A[temp];
        shifter /= 10;
    }
    return output;
}
*/
/*
//Value Renderer: Adding consistency bit to keep value stable
void preProcessor::valueRenderer(int index,bool value)
{

    switch (index) {
    case 1:
        TyreString = value + 100000000;
        qDebug() << TyreString;
        break;
    case 2:
        BrakeString = value + 100000000;
        qDebug() << BrakeString;
        break;
    case 3:
        DoorString = value + 100000000 ;
        qDebug() << DoorString;
        break;
    case 4:
        ToggleString = value + 100000000;
        qDebug() << ToggleString;
        break;
    case 5:
        DiagnosticString = value +  100000000;
        break;
    }
}*/


//All sensor check code blocks
//shifter determines the value to be toggled, value is binary for checks


void preProcessor::checkTyre(int shifter, bool value)
{

    TyreString = (value << shifter);

    qDebug() << TyreString;
    //return 0;
    Relay();
}

void preProcessor::checkBrakes(int shifter, bool value)
{

    BrakeString = (value << shifter);


    qDebug() << BrakeString;
    Relay();
}

void preProcessor::checkDoors(int shifter, bool value)
{

    DoorString = (value << shifter);

    qDebug() <<DoorString;
    Relay();
}

void preProcessor::ToggleValues(int shifter, bool value)
{

    ToggleString = (value << shifter);

    qDebug() << ToggleString;
    Relay();
}

void preProcessor::DiagnosticData(int shifter, bool value)
{

    DiagnosticString = (value << shifter);

    qDebug() << DiagnosticString;
    Relay();
}


//Transfer string parser
void preProcessor::Relay()
{
    //QString Tyr = QString::number(TyreString), Br = QString::number(BrakeString), Ds = QString::number(DoorString),
    //    Ts = QString::number(ToggleString);// Dia = QString::number(DiagnosticString);

    int compiledValue = 0;
    compiledValue = (DiagnosticString << 24)|(ToggleString << 16)|(BrakeString << 8)|(TyreString);

    QString Output = "[" + QString::number(compiledValue) + "]" ;

    qDebug() << "Final String" <<Output;

    //+ "," + Dia +
}


//#endif // MAINFUNCTIONS_H
