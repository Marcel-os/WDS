#ifndef ABOUT_H
#define ABOUT_H

/*!
* \file
* \brief Definicja klasy About
*
* Plik zawiera definicję klasy About, która jest klasą
* pochodną klasy QDialog.
*/

#include <QDialog>

/*!
* \brief Tworzy okienko "O Aplikacji"
*
* Okienko z informacjami na temat samej aplikacji,
* autora oraz przedstawia linki do stron WWW.
*/

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private slots:

	/*!
	* \brief Otwiera w przeglądarce link.
	*/

    void on_pushButton_poliwrocket_clicked();

    /*!
	* \brief Otwiera w przeglądarce link.
	*/

    void on_pushButton_pwrinspace_clicked();

    /*!
	* \brief Otwiera w przeglądarce link.
	*/

    void on_pushButton_github_clicked();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
