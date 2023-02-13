#include "mainHeader.h"
/*#define FrontTyrePressureThreshold 20
#define RearTyrePressureThreshold 24

#define TyreTemperatureThreshold 110

#define BrakeTemperatureThreshold 700
#define BrakeWearThreshold 78
*/
#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>


#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <math.h>

preProcessor preProcessorClass;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    usbDevice = new QSerialPort(this);
    connect(usbDevice,SIGNAL(readyRead()),this,SLOT(onSerialDataAvailable()));

    baudrate = QSerialPort::Baud115200;

    serialDeviceIsConnected = false;
    getAvalilableSerialDevices();

    //Initialise
    preProcessorClass.valueRenderer(1, preProcessorClass.initialise(
                                        ((ui->T1_t->value() > FrontTyrePressureThreshold) ? 0 : 1),
                                        ((ui->T2_t->value() > FrontTyrePressureThreshold) ? 0 : 1),
                                        ((ui->T3_t->value() > FrontTyrePressureThreshold) ? 0 : 1),
                                        ((ui->T4_t->value() > FrontTyrePressureThreshold) ? 0 : 1),
                                        ((ui->T1_p->value() > FrontTyrePressureThreshold) ? 0 : 1),
                                        ((ui->T2_p->value() > FrontTyrePressureThreshold) ? 0 : 1),
                                        ((ui->T3_p->value() > FrontTyrePressureThreshold) ? 0 : 1),
                                        ((ui->T4_p->value() > FrontTyrePressureThreshold) ? 0 : 1)
                                        ));

    preProcessorClass.valueRenderer(2, preProcessorClass.initialise(
                                        ((ui->B1_t->value() > BrakeTemperatureThreshold) ? 0 : 1),
                                        ((ui->B1_w->value() > BrakeWearThreshold) ? 0 : 1),
                                        ((ui->B2_t->value() > BrakeTemperatureThreshold) ? 0 : 1),
                                        ((ui->B2_w->value() > BrakeWearThreshold) ? 0 : 1),
                                        ((ui->B3_t->value() > BrakeTemperatureThreshold) ? 0 : 1),
                                        ((ui->B3_w->value() > BrakeWearThreshold) ? 0 : 1),
                                        ((ui->B4_t->value() > BrakeTemperatureThreshold) ? 0 : 1),
                                        ((ui->B4_w->value() > BrakeWearThreshold) ? 0 : 1)
                                        ));

    preProcessorClass.valueRenderer(3, preProcessorClass.initialise(
                                        ui->D1->isChecked(), ui->D2->isChecked(), ui->D3->isChecked(), ui->D4->isChecked(),
                                        ui->EngineBay->isChecked(),ui->Hatch->isChecked(), ui->BayLight->isChecked(), ui->HatchLight->isChecked()
                                        ));

    preProcessorClass.valueRenderer(4, preProcessorClass.initialise(
                                        ui->Nitro->isChecked(), ui->DRS->isChecked(), ui->ExhaustBypass->isChecked(),
                                        ui->TC->isChecked(), ui->ABS->isChecked(), ui->Cabin->isChecked(),
                                        ui->Engine->isChecked(), ui->OilPressure->isChecked()
                                        ));
    //preProcessorClass.Relay();
    //qDebug() << "Message to device: ";
    //Function to initialise all variables
    setWindowTitle(tr("OBD2 CAN Bus Simulator"));
}


MainWindow::~MainWindow()
{
    delete ui;
    delete usbDevice;
}



//Tyre Temperature

void MainWindow::on_T1_t_editingFinished()
{
    preProcessorClass.generatedValue = ui->T1_t->value();
    qDebug() << "Message to device: T1_t " << preProcessorClass.generatedValue;
    preProcessorClass.checkTyre(1, ((ui->T1_t->value() > TyreTemperatureThreshold) ? 0 : 1) );

}

void MainWindow::on_T2_t_editingFinished()
{
    preProcessorClass.generatedValue = ui->T2_t->value();
    qDebug() << "Message to device: T2_t " << preProcessorClass.generatedValue;
    preProcessorClass.checkTyre(10, ((ui->T2_t->value() > TyreTemperatureThreshold) ? 0 : 1) );
}

void MainWindow::on_T3_t_editingFinished()
{
    preProcessorClass.generatedValue = ui->T3_t->value();
    qDebug() << "Message to device: T3_t " << preProcessorClass.generatedValue;
    preProcessorClass.checkTyre(100, ((ui->T3_t->value() > TyreTemperatureThreshold) ? 0 : 1) );
}

void MainWindow::on_T4_t_editingFinished()
{
    preProcessorClass.generatedValue = ui->T4_t->value();
    qDebug() << "Message to device: T4_t " << preProcessorClass.generatedValue;
    preProcessorClass.checkTyre(1000, ((ui->T4_t->value() > TyreTemperatureThreshold) ? 0 : 1) );
}


//Tyre Pressure
void MainWindow::on_T1_p_editingFinished()
{
    preProcessorClass.generatedValue = ui->T1_p->value();
    qDebug() << "Message to device: T1_p " << preProcessorClass.generatedValue;
    preProcessorClass.checkTyre(10000, ((ui->T1_p->value() > FrontTyrePressureThreshold) ? 0 : 1) );
}

void MainWindow::on_T2_p_editingFinished()
{
    preProcessorClass.generatedValue = ui->T2_p->value();
    qDebug() << "Message to device: T2_p " << preProcessorClass.generatedValue;
    preProcessorClass.checkTyre(100000, ((ui->T2_p->value() >FrontTyrePressureThreshold) ? 0 : 1) );
}

void MainWindow::on_T3_p_editingFinished()
{
    preProcessorClass.generatedValue = ui->T3_p->value();
    qDebug() << "Message to device: T3_p " << preProcessorClass.generatedValue;
    preProcessorClass.checkTyre(1000000, ((ui->T3_p->value() > RearTyrePressureThreshold) ? 0 : 1) );
}

void MainWindow::on_T4_p_editingFinished()
{
    preProcessorClass.generatedValue = ui->T4_p->value();
    qDebug() << "Message to device: T4_p " << preProcessorClass.generatedValue;
    preProcessorClass.checkTyre(10000000, ((ui->T4_p->value() > RearTyrePressureThreshold) ? 0 : 1) );
}


//Door state section
void MainWindow::on_D1_toggled(bool checked)
{
    if(ui->D1->isChecked() == 0)
        qDebug() << "Door 1 closed";
    else
        qDebug() << "Door 1 opened";

    preProcessorClass.checkDoors(1, ui->D1->isChecked());
    //preProcessorClass.Relay();
}

void MainWindow::on_D2_toggled(bool checked)
{
    if(ui->D2->isChecked() == 0)
        qDebug() << "Door 2 closed";
    else
        qDebug() << "Door 2 opened";

    preProcessorClass.checkDoors(10, ui->D2->isChecked());
    //preProcessorClass.Relay();
}

void MainWindow::on_D3_toggled(bool checked)
{
    if(ui->D3->isChecked() == 0)
        qDebug() << "Door 3 closed";
    else
        qDebug() << "Door 3 opened";

    preProcessorClass.checkDoors(100, ui->D3->isChecked());
    //preProcessorClass.Relay();
}

void MainWindow::on_D4_toggled(bool checked)
{
    if(ui->D4->isChecked() == 0)
        qDebug() << "Door 4 closed";
    else
        qDebug() << "Door 4 opened";

    preProcessorClass.checkDoors(1000, ui->D4->isChecked());
}

void MainWindow::on_EngineBay_toggled(bool checked)
{
    if(ui->EngineBay->isChecked() == 0)
        qDebug() << "Engine Bay closed";
    else
        qDebug() << "Engine Bay opened";

    preProcessorClass.checkDoors(10000, ui->EngineBay->isChecked());
}

void MainWindow::on_Hatch_toggled(bool checked)
{
    if(ui->Hatch->isChecked() == 0)
        qDebug() << "Hatch is closed";
    else
        qDebug() << "Hatch is opened";

    preProcessorClass.checkDoors(100000, ui->Hatch->isChecked());
}

void MainWindow::on_BayLight_toggled(bool checked)
{
    if(ui->BayLight->isChecked() == 0)
        qDebug() << "Bay Light is off";
    else
        qDebug() << "Bay Light is on";

    preProcessorClass.checkDoors(1000000, ui->BayLight->isChecked());
}

void MainWindow::on_HatchLight_toggled(bool checked)
{
    if(ui->HatchLight->isChecked() == 0)
        qDebug() << "Hatch Light is off";
    else
        qDebug() << "Hatch Light is on";

    preProcessorClass.checkDoors(10000000, ui->HatchLight->isChecked());
}


//Brakes
void MainWindow::on_B1_t_editingFinished()
{
    qDebug() << "Message to device: B1_t " << ui->B1_t->value();
    preProcessorClass.checkTyre(1, ((ui->B1_t->value() > BrakeTemperatureThreshold) ? 0 : 1));
}

void MainWindow::on_B1_w_editingFinished()
{
    qDebug() << "Message to device: B1_w " << ui->B1_w->value();
    preProcessorClass.checkTyre(10, ((ui->B1_w->value() > BrakeWearThreshold) ? 0 : 1));
}

void MainWindow::on_B2_t_editingFinished()
{
    qDebug() << "Message to device: B2_t " << ui->B2_t->value();
    preProcessorClass.checkTyre(100, ((ui->B2_t->value() > BrakeTemperatureThreshold) ? 0 : 1));
}

void MainWindow::on_B2_w_editingFinished()
{
    qDebug() << "Message to device: B2_w " << ui->B2_w->value();
    preProcessorClass.checkTyre(1000, ((ui->B2_w->value() > BrakeWearThreshold) ? 0 : 1));
}

void MainWindow::on_B3_t_editingFinished()
{
    qDebug() << "Message to device: B3_t " << ui->B3_t->value();
    preProcessorClass.checkTyre(10000, ((ui->B3_t->value() > BrakeTemperatureThreshold) ? 0 : 1));
}

void MainWindow::on_B3_w_editingFinished()
{
    qDebug() << "Message to device: B3_w " << ui->B3_w->value();
    preProcessorClass.checkTyre(100000, ((ui->B4_w->value() > BrakeWearThreshold) ? 0 : 1));
}

void MainWindow::on_B4_t_editingFinished()
{
    qDebug() << "Message to device: B4_t " << ui->B4_t->value();
    preProcessorClass.checkTyre(1000000, ((ui->B4_t->value() > BrakeTemperatureThreshold) ? 0 : 1) );
}

void MainWindow::on_B4_w_editingFinished()
{
    qDebug() << "Message to device: B4_w " << ui->B4_w->value();
    preProcessorClass.checkTyre(10000000, ((ui->B4_w->value() > BrakeWearThreshold) ? 0 : 1) );
}


//Toggles
void MainWindow::on_Nitro_toggled(bool checked)
{
    if(ui->Nitro->isChecked() == 0)
        qDebug() << "Nitros Off";
    else
        qDebug() << "Nitros Engaged";

    preProcessorClass.ToggleValues(1, ui->Nitro->isChecked());
}

void MainWindow::on_DRS_toggled(bool checked)
{
    if(ui->DRS->isChecked() == 0)
        qDebug() << "DRS Deactivated";
    else
        qDebug() << "DRS Activated";

    preProcessorClass.ToggleValues(10, ui->DRS->isChecked());
}

void MainWindow::on_ExhaustBypass_toggled(bool checked)
{
    if(ui->ExhaustBypass->isChecked() == 0)
        qDebug() << "Door 1 closed";
    else
        qDebug() << "Door 1 opened";

    preProcessorClass.ToggleValues(100, ui->ExhaustBypass->isChecked());
}

void MainWindow::on_TC_toggled(bool checked)
{
    if(ui->TC->isChecked() == 0)
        qDebug() << "Traction Control off";
    else
        qDebug() << "Traction control on";

    preProcessorClass.ToggleValues(1000, ui->TC->isChecked());
}

void MainWindow::on_ABS_toggled(bool checked)
{
    if(ui->ABS->isChecked() == 0)
        qDebug() << "ABS off";
    else
        qDebug() << "ABS on";

    preProcessorClass.ToggleValues(10000, ui->ABS->isChecked());
}

void MainWindow::on_Cabin_toggled(bool checked)
{
    if(ui->Cabin->isChecked() == 0)
        qDebug() << "Cabin atmosphere at risk, Deploy HVAC";
    else
        qDebug() << "Clean air";

    preProcessorClass.ToggleValues(100000, ui->Cabin->isChecked());
}

void MainWindow::on_Engine_toggled(bool checked)
{
    if(ui->Engine->isChecked() == 0)
        qDebug() << "Check Engine";
    else
        qDebug() << "Engine Okay";

    preProcessorClass.ToggleValues(1000000, ui->Engine->isChecked());
}

void MainWindow::on_OilPressure_toggled(bool checked)
{
    if(ui->OilPressure->isChecked() == 0)
        qDebug() << "Oil Pressure low";
    else
        qDebug() << "Oil pressure okay";

    preProcessorClass.ToggleValues(10000000, ui->OilPressure->isChecked());
}


void MainWindow::getAvalilableSerialDevices()
{
    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    serialComPortList.clear();
    ui->serialPortSelect_comboBox->clear();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        QString dbgStr = "Vendor ID: ";


       if(serialPortInfo.hasVendorIdentifier())
       {
          dbgStr+= serialPortInfo.vendorIdentifier();
       }
       else
       {
          dbgStr+= " - ";
       }
       dbgStr+= "  Product ID: ";
       if(serialPortInfo.hasProductIdentifier())
       {

          dbgStr+= QString::number(serialPortInfo.hasProductIdentifier());
       }
       else
       {
          dbgStr+= " - ";
       }
       dbgStr+= " Name: " + serialPortInfo.portName();
       dbgStr+= " Description: "+serialPortInfo.description();
      qDebug()<<dbgStr;
      serialComPortList.push_back(serialPortInfo);
      ui->serialPortSelect_comboBox->addItem(serialPortInfo.portName() +" "+serialPortInfo.description());
    }
}
void MainWindow::serialWrite(QString message)
{
    if(serialDeviceIsConnected == true)
    {
        usbDevice->write(message.toUtf8()); // Send the message to the device
        qDebug() << "Message to device: "<<message;
    }
}
void MainWindow::serialRead()
{
    if(serialDeviceIsConnected == true)
    {
        serialBuffer += usbDevice->readAll(); // Read the available data
    }
}
void MainWindow::onSerialDataAvailable()
{
    if(serialDeviceIsConnected == true)
    {
        serialRead(); // Read a chunk of the Message
        //To solve that problem I send a end char "]" in My case. That helped my to know when a message is complete

        if(serialBuffer.indexOf(" ") != -1) //Message complete
        {
            qDebug() << "Message from device: "<<serialBuffer;
            serialWrite("echoFromGui");

            //Do something with de message here

            serialBuffer = "";  //Clear the buffer;
        }
    }
}


void MainWindow::on_connect_button_clicked()
{
    if(serialDeviceIsConnected == false)
    {
        usbDevice->setPortName(serialComPortList[ui->serialPortSelect_comboBox->currentIndex()].portName());
        deviceDescription = serialComPortList[ui->serialPortSelect_comboBox->currentIndex()].description();
        qDebug() << "connecting to: "<<usbDevice->portName();
        if(usbDevice->open(QIODevice::ReadWrite))
        {
            //Now the serial port is open try to set configuration
            if(!usbDevice->setBaudRate(baudrate))        //Depends on your boud-rate on the Device
                qDebug()<<usbDevice->errorString();

            if(!usbDevice->setDataBits(QSerialPort::Data8))
                qDebug()<<usbDevice->errorString();

            if(!usbDevice->setParity(QSerialPort::NoParity))
                qDebug()<<usbDevice->errorString();

            if(!usbDevice->setStopBits(QSerialPort::OneStop))
                qDebug()<<usbDevice->errorString();

            if(!usbDevice->setFlowControl(QSerialPort::NoFlowControl))
                qDebug()<<usbDevice->errorString();

            //If any error was returned the serial il corrctly configured

            qDebug() << "Connection to: "<< usbDevice->portName() << " " << deviceDescription << " connected";
            serialDeviceIsConnected = true;
        }
        else
        {
            qDebug() << "Connection to: "<< usbDevice->portName() << " " << deviceDescription << " not connected";
            qDebug() <<"         Error: "<<usbDevice->errorString();
            serialDeviceIsConnected = false;
        }
    }
    else
    {
        qDebug() << "Can't connect, another device is connected";
    }
}

void MainWindow::on_disconnect_button_clicked()
{
    if(serialDeviceIsConnected)
    {
        usbDevice->close();
        serialDeviceIsConnected = false;
        qDebug() << "Connection to: "<< usbDevice->portName() << " " << deviceDescription << " closed";
    }
    else
    {
       qDebug() << "Can't disconnect, no device is connected";
    }
}

//void MainWindow::on_Coolant_toggled(bool checked)
//{
//    if(ui->Coolant->isChecked() == 0)
//        qDebug() << "Coolant Replace";
//    else
//        qDebug() << "Coolant Okay";

//    preProcessorClass.checkDoors(100000000, ui->Coolant->isChecked());
//}








