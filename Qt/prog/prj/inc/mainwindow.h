#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*!
* \file
* \brief Definicja klasy MainWindow
*
* Plik zawiera definicję klasy MainWindow, która jest klasą
* pochodną klasy QMainWindow.
*/

#include <QMainWindow>
#include <QSerialPort>

/*!
* \brief Tworzy okienko główne
*
* Główne okno aplikacji, zawiera wiele widgetów.
*/

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /*!
    * \brief Dodaje punkt do wykresów.
    */
    void addPoint();
    /*!
    * \brief Rysuje wykresy.
    */
    void plot();
    /*!
    * \brief Usuwa dane z wykresów.
    */
    void clear_data_plot();

private slots:
    /*!
    * \brief Reakcja na kliknięcie przycisku szukaj.
    */
    void on_pushButton_szukaj_clicked();
    /*!
    * \brief Reakcja na kliknięcie przycisku połącz.
    */
    void on_pushButton_polacz_clicked();
    /*!
    * \brief Reakcja na kliknięcie przycisku zamknij.
    */
    void on_pushButton_zamknij_clicked();
    /*!
    * \brief Czytanie danych z portu szeregowego.
    */
    void readFromPort();
    /*!
    * \brief Reakcja na kliknięcie przycisku wyczyść.
    */
    void on_pushButton_clear_clicked();
    /*!
    * \brief Reakcja na kliknięcie przycisku.
    */
    void on_pushButton_clicked();
    /*!
    * \brief Generowanie wykresu.
    */
    void makePlots();
    /*!
    * \brief Reakcja na kliknięcie o aplikacji.
    */
    void on_pushButton_About_clicked();

private:
    Ui::MainWindow *ui;
    void addToLogs(QString message);
    /*!
    * \brief Sprawdzenie połączenia.
    */
    void check_connection();
    QSerialPort *device;
    long long start_time = 0;
    float AccXf;
    float AccYf;
    float AccZf;
    float GyrXf;
    float GyrYf;
    float GyrZf;
    float MagXf;
    float MagYf;
    float MagZf;
    float Tempf;
    float Presf;
    float Altif;
    float Voltage;
};

#endif // MAINWINDOW_H
