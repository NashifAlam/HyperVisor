#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_T1_t_editingFinished();

    void on_T2_t_editingFinished();

    void on_T1_p_editingFinished();

    void on_T2_p_editingFinished();

    void on_T3_t_editingFinished();

    void on_T4_t_editingFinished();

    void on_T3_p_editingFinished();

    void on_T4_p_editingFinished();


    void onSerialDataAvailable();
    void on_connect_button_clicked();
    void on_disconnect_button_clicked();


    void on_D1_toggled(bool checked);

    void on_D2_toggled(bool checked);

    void on_D3_toggled(bool checked);

    void on_D4_toggled(bool checked);

    void on_EngineBay_toggled(bool checked);

    void on_Hatch_toggled(bool checked);

    void on_BayLight_toggled(bool checked);

    void on_HatchLight_toggled(bool checked);

    void on_B1_t_editingFinished();

    void on_B1_w_editingFinished();

    void on_B2_t_editingFinished();

    void on_B2_w_editingFinished();

    void on_B3_t_editingFinished();

    void on_B3_w_editingFinished();

    void on_B4_t_editingFinished();

    void on_B4_w_editingFinished();

    void on_Nitro_toggled(bool checked);

    void on_DRS_toggled(bool checked);

    void on_ExhaustBypass_toggled(bool checked);

    void on_TC_toggled(bool checked);

    void on_ABS_toggled(bool checked);

    void on_Cabin_toggled(bool checked);

    void on_Engine_toggled(bool checked);

    void on_OilPressure_toggled(bool checked);

    //void on_Coolant_toggled(bool checked);

private:
    void getAvalilableSerialDevices();
    void serialRead();
    void serialWrite(QString message);

    Ui::MainWindow *ui;


    qint32 baudrate;
    QSerialPort *usbDevice;
    std::vector<QSerialPortInfo> serialComPortList; //A list of the available ports for the dropdownmenue in the GUI

    QString deviceDescription;
    QString serialBuffer;

    bool serialDeviceIsConnected;
};
#endif // MAINWINDOW_H
