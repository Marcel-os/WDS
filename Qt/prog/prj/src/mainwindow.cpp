#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include <QDebug>
#include <QList>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QSerialPort>
#include <QThread>
#include <string>
#include <math.h>
#include <QPixmap>

/*!
* \file
* \brief Definicja metod klasy MainWindow
*
* Zawiera definicje metod klasy MainWindow.
*/


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlots();
    QPixmap pixmap_RPY("C:/Users/Marcel/Documents/Projekty_Qt/druga_apka/RPY.png");
    ui->label_pic->setPixmap(pixmap_RPY);
    this->device = new QSerialPort(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
* Metoda dodaje nowe punkty do odpowiednich wykresów z zachowanim reżimu czasowego.
*/
void MainWindow::addPoint()
{
    double t = (QDateTime::currentMSecsSinceEpoch() - this->start_time)/1000.0;
    ui->customPlot_Acc->graph(0)->addData(t, this->AccXf);
    ui->customPlot_Acc->graph(1)->addData(t, this->AccYf);
    ui->customPlot_Acc->graph(2)->addData(t, this->AccZf);

    ui->customPlot_Gyr->graph(0)->addData(t, this->GyrXf);
    ui->customPlot_Gyr->graph(1)->addData(t, this->GyrYf);
    ui->customPlot_Gyr->graph(2)->addData(t, this->GyrZf);

    ui->customPlot_Mag->graph(0)->addData(t, this->MagXf);
    ui->customPlot_Mag->graph(1)->addData(t, this->MagYf);
    ui->customPlot_Mag->graph(2)->addData(t, this->MagZf);

    ui->customPlot_Temp->graph(0)->addData(t, this->Tempf);
    ui->customPlot_Pres->graph(0)->addData(t, this->Presf);
}

/*!
* Metoda odświeża wszystkie wykresy po edycji, np po dodaniu punktów.
*/
void MainWindow::plot()
{
    ui->customPlot_Acc->xAxis->rescale();
    ui->customPlot_Acc->xAxis->setRange(ui->customPlot_Acc->xAxis->range().upper, 10, Qt::AlignRight);
    ui->customPlot_Acc->replot();
    ui->customPlot_Acc->update();

    ui->customPlot_Gyr->xAxis->rescale();
    ui->customPlot_Gyr->xAxis->setRange(ui->customPlot_Gyr->xAxis->range().upper, 10, Qt::AlignRight);
    ui->customPlot_Gyr->replot();
    ui->customPlot_Gyr->update();

    ui->customPlot_Mag->xAxis->rescale();
    ui->customPlot_Mag->xAxis->setRange(ui->customPlot_Mag->xAxis->range().upper, 10, Qt::AlignRight);
    ui->customPlot_Mag->replot();
    ui->customPlot_Mag->update();

    ui->customPlot_Temp->xAxis->rescale();
    ui->customPlot_Temp->yAxis->setRange(this->Tempf-5,this->Tempf+5);
    ui->customPlot_Temp->yAxis2->setRange(this->Tempf-5,this->Tempf+5);
    ui->customPlot_Temp->xAxis->setRange(ui->customPlot_Temp->xAxis->range().upper, 100, Qt::AlignRight);
    ui->customPlot_Temp->replot();
    ui->customPlot_Temp->update();

    ui->customPlot_Pres->xAxis->rescale();
    ui->customPlot_Pres->yAxis->setRange(this->Presf-10,this->Presf+10);
    ui->customPlot_Pres->yAxis2->setRange(this->Presf-10,this->Presf+10);
    ui->customPlot_Pres->xAxis->setRange(ui->customPlot_Pres->xAxis->range().upper, 100, Qt::AlignRight);
    ui->customPlot_Pres->replot();
    ui->customPlot_Pres->update();
}
/*!
* Metoda czyści obszar wszytskich wykresów.
*/
void MainWindow::clear_data_plot()
{
    ui->customPlot_Acc->graph(0)->data()->clear();
    ui->customPlot_Acc->graph(1)->data()->clear();
    ui->customPlot_Acc->graph(2)->data()->clear();

    ui->customPlot_Gyr->graph(0)->data()->clear();
    ui->customPlot_Gyr->graph(1)->data()->clear();
    ui->customPlot_Gyr->graph(2)->data()->clear();

    ui->customPlot_Mag->graph(0)->data()->clear();
    ui->customPlot_Mag->graph(1)->data()->clear();
    ui->customPlot_Mag->graph(2)->data()->clear();

    ui->customPlot_Temp->graph(0)->data()->clear();
    ui->customPlot_Pres->graph(0)->data()->clear();

    ui->customPlot_Acc->replot();
    ui->customPlot_Gyr->replot();
    ui->customPlot_Mag->replot();
    ui->customPlot_Temp->replot();
    ui->customPlot_Pres->replot();
}
/*!
* Metoda inicjalizująca wykresy w oknie MainWindow.
*/
void MainWindow::makePlots()
{

    //BEGIN Wykres Akcelerometru
    ui->customPlot_Acc->addGraph()->setName("oś X");
    ui->customPlot_Acc->addGraph()->setName("oś Y");
    ui->customPlot_Acc->addGraph()->setName("oś Z");

    ui->customPlot_Acc->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->customPlot_Acc->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->customPlot_Acc->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    ui->customPlot_Acc->xAxis->setLabel("czas (sekundy)");
    ui->customPlot_Acc->yAxis->setLabel("przyspieszenie (m/s^2)");

    ui->customPlot_Acc->legend->setVisible(true);
    QCPLayoutGrid *subLayoutACC = new QCPLayoutGrid;
    ui->customPlot_Acc->plotLayout()->addElement(1, 0, subLayoutACC);
    subLayoutACC->setMargins(QMargins(5, 0, 5, 5));
    subLayoutACC->addElement(0, 0, ui->customPlot_Acc->legend);
    ui->customPlot_Acc->legend->setFillOrder(QCPLegend::foColumnsFirst);
    ui->customPlot_Acc->plotLayout()->setRowStretchFactor(1, 0.001);

    ui->customPlot_Acc->xAxis->rescale();
    ui->customPlot_Acc->xAxis->setRange(ui->customPlot_Acc->xAxis->range().upper, 10, Qt::AlignRight);
    ui->customPlot_Acc->yAxis->setRange(-20, 20);
    ui->customPlot_Acc->yAxis2->setRange(-20, 20);
    ui->customPlot_Acc->yAxis->setTickLabels(false);
    ui->customPlot_Acc->yAxis2->setVisible(true);
    //END Wykres Akcelerometru

    //BEGIN Wykres Żyroskopu
    ui->customPlot_Gyr->addGraph()->setName("oś X");
    ui->customPlot_Gyr->addGraph()->setName("oś Y");
    ui->customPlot_Gyr->addGraph()->setName("oś Z");

    ui->customPlot_Gyr->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->customPlot_Gyr->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->customPlot_Gyr->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    ui->customPlot_Gyr->xAxis->setLabel("czas (sekundy)");
    ui->customPlot_Gyr->yAxis->setLabel("prędkośc kątowa (st/s)");

    ui->customPlot_Gyr->legend->setVisible(true);
    QCPLayoutGrid *subLayoutGYR = new QCPLayoutGrid;
    ui->customPlot_Gyr->plotLayout()->addElement(1, 0, subLayoutGYR);
    subLayoutGYR->setMargins(QMargins(5, 0, 5, 5));
    subLayoutGYR->addElement(0, 0, ui->customPlot_Gyr->legend);
    ui->customPlot_Gyr->legend->setFillOrder(QCPLegend::foColumnsFirst);
    ui->customPlot_Gyr->plotLayout()->setRowStretchFactor(1, 0.001);

    ui->customPlot_Gyr->xAxis->rescale();
    ui->customPlot_Gyr->xAxis->setRange(ui->customPlot_Gyr->xAxis->range().upper, 10, Qt::AlignRight);
    ui->customPlot_Gyr->yAxis->setRange(-2000, 2000);
    ui->customPlot_Gyr->yAxis2->setRange(-2000, 2000);
    ui->customPlot_Gyr->yAxis->setTickLabels(false);
    ui->customPlot_Gyr->yAxis2->setVisible(true);
    //END Wykres Żyroskopu

    //BEGIN Wykres Magnetometru
    ui->customPlot_Mag->addGraph()->setName("oś X");
    ui->customPlot_Mag->addGraph()->setName("oś Y");
    ui->customPlot_Mag->addGraph()->setName("oś Z");

    ui->customPlot_Mag->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->customPlot_Mag->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->customPlot_Mag->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    ui->customPlot_Mag->xAxis->setLabel("czas (sekundy)");
    ui->customPlot_Mag->yAxis->setLabel("Gaus (Gs)");

    ui->customPlot_Mag->legend->setVisible(true);
    QCPLayoutGrid *subLayoutMAG = new QCPLayoutGrid;
    ui->customPlot_Mag->plotLayout()->addElement(1, 0, subLayoutMAG);
    subLayoutMAG->setMargins(QMargins(5, 0, 5, 5));
    subLayoutMAG->addElement(0, 0, ui->customPlot_Mag->legend);
    ui->customPlot_Mag->legend->setFillOrder(QCPLegend::foColumnsFirst);
    ui->customPlot_Mag->plotLayout()->setRowStretchFactor(1, 0.001);

    ui->customPlot_Mag->xAxis->rescale();
    ui->customPlot_Mag->xAxis->setRange(ui->customPlot_Mag->xAxis->range().upper, 10, Qt::AlignRight);
    ui->customPlot_Mag->yAxis->setRange(-2, 2);
    ui->customPlot_Mag->yAxis2->setRange(-2, 2);
    ui->customPlot_Mag->yAxis->setTickLabels(false);
    ui->customPlot_Mag->yAxis2->setVisible(true);
    //END Wykres Magnetometru

    //BEGIN Wykres Temperatury
    ui->customPlot_Temp->addGraph();
    ui->customPlot_Temp->graph(0)->setPen(QPen(QColor(255, 0, 0)));

    ui->customPlot_Temp->xAxis->setLabel("czas (sekundy)");
    ui->customPlot_Temp->yAxis->setLabel("temperatura (oC)");

    ui->customPlot_Temp->xAxis->rescale();
    ui->customPlot_Temp->xAxis->setRange(ui->customPlot_Mag->xAxis->range().upper, 100, Qt::AlignRight);
    ui->customPlot_Temp->graph(0)->rescaleValueAxis(false, true);
    ui->customPlot_Temp->yAxis->setTickLabels(false);
    connect(ui->customPlot_Temp->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->customPlot_Temp->yAxis, SLOT(setRange(QCPRange)));
    ui->customPlot_Temp->yAxis2->setVisible(true);
    //END Wykres Temperatury

    //BEGIN Wykres Ciśneinia
    ui->customPlot_Pres->addGraph();
    ui->customPlot_Pres->graph(0)->setPen(QPen(QColor(255, 0, 0)));

    ui->customPlot_Pres->xAxis->setLabel("czas (sekundy)");
    ui->customPlot_Pres->yAxis->setLabel("ciśnienie (hPa)");

    ui->customPlot_Pres->xAxis->rescale();
    ui->customPlot_Pres->xAxis->setRange(ui->customPlot_Mag->xAxis->range().upper, 100, Qt::AlignRight);
    ui->customPlot_Pres->graph(0)->rescaleValueAxis(false, true);
    ui->customPlot_Pres->yAxis->setTickLabels(false);
    connect(ui->customPlot_Pres->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->customPlot_Pres->yAxis, SLOT(setRange(QCPRange)));
    ui->customPlot_Pres->yAxis2->setVisible(true);
    //END Wykres Ciśneinia

    ui->customPlot_Acc->replot();
    ui->customPlot_Gyr->replot();
    ui->customPlot_Mag->replot();
    ui->customPlot_Temp->replot();
    ui->customPlot_Pres->replot();
}

/*!
* Metoda sprawdzająca czy aktualnie jesteśmy połączeni z urządzeniem
*/
void MainWindow::check_connection(){
    if(device->isOpen()) {
        ui->statusbar->showMessage("Połączono z " + this->device->portName() );
    }else{
         ui->statusbar->showMessage("Rozłączono");
    }
}

/*!
* Reakcja na kliknięcie przycisku szukaj, sprawdzenie dostepnych urządzeń.
*/
void MainWindow::on_pushButton_szukaj_clicked()
{
    this->addToLogs("Szukam urządzeń....");
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    ui->comboBox_devices->clear();
    for(int i = 0; i < devices.count(); i++) {
        this->addToLogs("Znalazłem urządzenie: " + devices.at(i).portName() + " " + devices.at(i).description());
        ui->comboBox_devices->addItem(devices.at(i).portName() + "\t" + devices.at(i).description());
    }
    this->check_connection();
}

void MainWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->textEdit_logi->append(currentDateTime + "  " + message);
    this->check_connection();
}

/*!
* Reakcja na kliknięcie przycisku połącz, wypisanie do logu ważnych informacji.
*/
void MainWindow::on_pushButton_polacz_clicked()
{
    if(ui->comboBox_devices->count() == 0) {
      this->addToLogs("Nie wykryto żadnych urządzeń!");
      return;
    }

    QString portName = ui->comboBox_devices->currentText().split("\t").first();

    this->device->setPortName(portName);
    if(!device->isOpen()) {
        if(device->open(QSerialPort::ReadWrite)) {
            this->device->setBaudRate(QSerialPort::Baud115200);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);

            this->addToLogs("Otwarto port szeregowy.");
            connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
            this->clear_data_plot();
            this->start_time = QDateTime::currentMSecsSinceEpoch();
        } else {
            this->addToLogs("Otwarcie porty szeregowego się nie powiodło!");
        }
    } else {
      this->addToLogs("Port już jest otwarty!");
      return;
    }
    this->check_connection();

}

/*!
* Reakcja na kliknięcie przycisku rozłącz, rozłączenie urządzenia.
*/
void MainWindow::on_pushButton_zamknij_clicked()
{
    if(this->device->isOpen()) {
      this->device->close();
      this->addToLogs("Zamknięto połączenie.");
    } else {
      this->addToLogs("Port nie jest otwarty!");
      return;
    }
    this->check_connection();
}
/*!
* Odczyt danych z urządzenia, kontrola poprawności oraz przepisanie do
* odpowiednich zmiennych oraz wykresów, pasków postępu itd.
*/
void MainWindow::readFromPort()
{
    while(this->device->canReadLine()) {
        QString line = this->device->readLine();
        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);

        this->addToLogs(line.left(pos));

        this->AccXf = line.mid(1,5).toFloat()/100.0;
        this->AccYf = line.mid(7,5).toFloat()/100.0;
        this->AccZf = line.mid(13,5).toFloat()/100.0;

        this->GyrXf = line.mid(19,5).toFloat();
        this->GyrYf = line.mid(25,5).toFloat();
        this->GyrZf = line.mid(31,5).toFloat();

        this->MagXf = line.mid(37,5).toFloat()/1000.0;
        this->MagYf = line.mid(43,5).toFloat()/1000.0;
        this->MagZf = line.mid(49,5).toFloat()/1000.0;

        this->Tempf = line.mid(55,4).toFloat()/10.0;
        this->Presf = line.mid(60,5).toFloat()/10.0;
        this->Altif = line.mid(66,5).toFloat()/10.0;
        this->Voltage = line.mid(72,3).toFloat()/100.0;

        ui->progressBar_AccX->setValue(this->AccXf * 5.0);
        ui->progressBar_AccY->setValue(this->AccYf * 5.0);
        ui->progressBar_AccZ->setValue(this->AccZf * 5.0);

        ui->progressBar_GyrX->setValue(this->GyrXf * 0.05);
        ui->progressBar_GyrY->setValue(this->GyrYf * 0.05);
        ui->progressBar_GyrZ->setValue(this->GyrZf * 0.05);

        ui->progressBar_MagX->setValue(this->MagXf * 50.0);
        ui->progressBar_MagY->setValue(this->MagYf * 50.0);
        ui->progressBar_MagZ->setValue(this->MagZf * 50.0);

        ui->lcdNumber_Temp->display(this->Tempf);
        ui->lcdNumber_Pres->display(this->Presf);
        ui->lcdNumber_Alt->display(this->Altif);
        ui->lcdNumber_Voltage->display(this->Voltage);

        float roll = 180 * atan (this->AccYf/sqrt(this->AccXf*AccXf + this->AccZf*this->AccZf))/3.14159;
        float pitch = 180 * atan (this->AccXf/sqrt(this->AccYf*this->AccYf + this->AccZf*this->AccZf))/3.14159;
        //float yaw = 180 * atan2((sin(roll*0.0175)*MagZf - cos(roll*0.0175)*MagYf),(cos(pitch*0.0175)*MagXf + sin(roll*0.0175)*sin(pitch*0.0175)*MagYf + cos(roll*0.0175)*sin(pitch*0.0175)*MagZf))/3.14159;
        float yaw = 180 * atan (this->AccZf/sqrt(this->AccXf*this->AccXf + this->AccZf*this->AccZf))/3.14159;

        ui->widget_gl->setXRotation((int)roll * 16);
        ui->widget_gl->setYRotation((int)pitch * 16);
        ui->widget_gl->setZRotation((int)yaw * 16);

        ui->progressBar_Roll->setValue(roll);
        ui->progressBar_Pitch->setValue(pitch);
        ui->progressBar_Yaw->setValue(yaw);

        addPoint();
        plot();

        this->check_connection();
    }
}

/*!
* Reakcja na kliknięcie przycisku wyczyść.
*/
void MainWindow::on_pushButton_clear_clicked()
{
    ui->textEdit_logi->clear();
    this->check_connection();
}
/*!
* Reakcja na kliknięcie przycisku o Aplikacji.
*/
void MainWindow::on_pushButton_About_clicked()
{
    About about;
    about.setModal(true);
    about.exec();
}
