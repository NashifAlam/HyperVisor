#ifndef MAINHEADER_H
#define MAINHEADER_H

#define FrontTyrePressureThreshold 20
#define RearTyrePressureThreshold 24

#define TyreTemperatureThreshold 110

#define BrakeTemperatureThreshold 700
#define BrakeWearThreshold 78

#include <QMainWindow>

class preProcessor{
    private:
        int a =10;
        int TyreString = 0, BrakeString = 0, DoorString = 0, ToggleString = 0, DiagnosticString = 0;
     public:
        //Variables
        int generatedValue;

        //Functions
        int initialise(int a_1, int a_2, int a_3, int a_4, int a_5, int a_6, int a_7, int a_8);
        void valueRenderer(int index, int value);
        void checkTyre(int multiplier, int value);
        void checkBrakes(int multiplier, int value);
        void checkDoors(int multiplier, int value);
        void ToggleValues(int mulitplier, int value);
        void DiagnosticData(int multiplier, int value);
        void Relay();

};

int preProcessor::initialise(int a_1, int a_2, int a_3, int a_4, int a_5, int a_6, int a_7, int a_8)
{
    int A[8]={a_1,a_2,a_3,a_4,a_5,a_6,a_7,a_8};
    int output =0;
    for(int temp =0, multiplier=10000000; temp <8; temp++)
    {
        output += multiplier * A[temp];
        multiplier /= 10;
    }
    return output;
}

void preProcessor::valueRenderer(int index,int value)
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
}

void preProcessor::checkTyre(int multiplier, int value)
{
    int temp[8];
    int flag = TyreString;
    switch (multiplier) {
        case 1: temp[0]=value; break;
        case 10: temp[1]=value; break;
        case 100: temp[2]=value; break;
        case 1000: temp[3]=value; break;
        case 10000: temp[4]=value; break;
        case 100000: temp[5]=value; break;
        case 1000000: temp[6]=value; break;
        case 10000000: temp[7]=value; break;
    }


        flag = flag/multiplier;
        flag = flag % 10;
        flag = flag * multiplier;
        TyreString = (TyreString - flag) + (multiplier * value);

    qDebug() << TyreString;
    //return 0;
Relay();
}

void preProcessor::checkBrakes(int multiplier, int value)
{
    //return 0;
    int temp[8];
    int flag = BrakeString;
    switch (multiplier) {
        case 1: temp[0]=value; break;
        case 10: temp[1]=value; break;
        case 100: temp[2]=value; break;
        case 1000: temp[3]=value; break;
        case 10000: temp[4]=value; break;
        case 100000: temp[5]=value; break;
        case 1000000: temp[6]=value; break;
        case 10000000: temp[7]=value; break;
    }


        flag = flag/multiplier;
        flag = flag % 10;
        flag = flag * multiplier;
        BrakeString = (BrakeString - flag) + (multiplier * value);


    qDebug() << BrakeString;
Relay();
}

void preProcessor::checkDoors(int multiplier, int value)
{
    int temp[8];
    int flag = DoorString;
    switch (multiplier) {
        case 1: temp[0]=value; break;
        case 10: temp[1]=value; break;
        case 100: temp[2]=value; break;
        case 1000: temp[3]=value; break;
        case 10000: temp[4]=value; break;
        case 100000: temp[5]=value; break;
        case 1000000: temp[6]=value; break;
        case 10000000: temp[7]=value; break;
    }


        flag = flag/multiplier;
        flag = flag % 10;
        flag = flag * multiplier;
        DoorString = (DoorString - flag) + (multiplier * value);

    qDebug() <<DoorString;
    Relay();
}

void preProcessor::ToggleValues(int multiplier, int value)
{
    int temp[8];
    int flag = ToggleString;
    switch (multiplier) {
        case 1: temp[0]=value; break;
        case 10: temp[1]=value; break;
        case 100: temp[2]=value; break;
        case 1000: temp[3]=value; break;
        case 10000: temp[4]=value; break;
        case 100000: temp[5]=value; break;
        case 1000000: temp[6]=value; break;
        case 10000000: temp[7]=value; break;
    }


        flag = flag/multiplier;
        flag = flag % 10;
        flag = flag * multiplier;
        ToggleString = (ToggleString - flag) + (multiplier * value);

    qDebug() << ToggleString;
     Relay();
}

void preProcessor::DiagnosticData(int multiplier, int value)
{
    int temp[8];
    int flag = DiagnosticString;
    switch (multiplier) {
        case 1: temp[0]=value; break;
        case 10: temp[1]=value; break;
        case 100: temp[2]=value; break;
        case 1000: temp[3]=value; break;
        case 10000: temp[4]=value; break;
        case 100000: temp[5]=value; break;
        case 1000000: temp[6]=value; break;
        case 10000000: temp[7]=value; break;
    }


        flag = flag/multiplier;
        flag = flag % 10;
        flag = flag * multiplier;
        DiagnosticString = (DiagnosticString - flag) + (multiplier * value);

    qDebug() << DiagnosticString;
    Relay();
}

void preProcessor::Relay()
{
    QString Tyr = QString::number(TyreString), Br = QString::number(BrakeString), Ds = QString::number(DoorString),
            Ts = QString::number(ToggleString);// Dia = QString::number(DiagnosticString);

    QString Output = "[" + Tyr + "," + Br + "," +  Ds + "," + Ts + "]" ;

    qDebug() << "Final String" <<Output;

    //+ "," + Dia +
}


#endif // MAINHEADER_H
