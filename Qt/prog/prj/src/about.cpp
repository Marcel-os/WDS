#include "about.h"
#include "ui_about.h"
#include <QDesktopServices>
#include <QUrl>

/*!
* \file
* \brief Definicja metod klasy About
*
* Zawiera definicje metod klasy About.
*/

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QPixmap pixmap_Poli("C:/Users/Marcel/Documents/Projekty_Qt/druga_apka/logo1.png");
    QPixmap pixmap_Pwsp("C:/Users/Marcel/Documents/Projekty_Qt/druga_apka/logo2.png");
    QPixmap pixmap_Git("C:/Users/Marcel/Documents/Projekty_Qt/druga_apka/logo3.png");
    ui->label_Logo1->setPixmap(pixmap_Poli);
    ui->label_Logo2->setPixmap(pixmap_Pwsp);
    ui->label_Logo3->setPixmap(pixmap_Git);
}

About::~About()
{
    delete ui;
}

/*!
* Otwiera w domyślnej przeglądarce link do strony projektu PoliWRocket.
*/

void About::on_pushButton_poliwrocket_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.facebook.com/poliwrocket/"));
}

/*!
* Otwiera w domyślnej przeglądarce link do strony koła naukowego PWR in space.
*/

void About::on_pushButton_pwrinspace_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.facebook.com/pwrinspace/"));
}

/*!
* Otwiera w domyślnej przeglądarce link do strony repozytorium.
*/

void About::on_pushButton_github_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Marcel-os/WDS"));
}
