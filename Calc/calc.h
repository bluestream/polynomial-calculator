#ifndef CALC_H
#define CALC_H

#include "gradoprimo.h"
#include "gradosecondo.h"
#include "gradon.h"
#include <QMainWindow>
#include <QStringList>

namespace Ui {
class calc;
}

class calc : public QMainWindow
{
    Q_OBJECT

public:
    // costruttori/distruttori
    explicit calc(QWidget* parent = 0);
    ~calc();

    // metodi di classe
    void digitClicked();                    // gestice i numeri inseriti
    void xClicked();                        // gestisce gli esponenti inseriti
    void operationClicked();                // gestisce le operazioni inserite
    monomio getMonomio(QString);            // ricava un monomio dalla stringa di input
    equazione* getEquation(polinomio&);     // ricava la corrispondente equazione da un polinomio
    void storeMonomio(QString);
    void checkInput();

private slots:
    // pulsanti numerici
    void on_button0_clicked();
    void on_button1_clicked();
    void on_button2_clicked();
    void on_button3_clicked();
    void on_button4_clicked();
    void on_button5_clicked();
    void on_button6_clicked();
    void on_button7_clicked();
    void on_button8_clicked();
    void on_button9_clicked();

    // clear
    void on_buttonClear_clicked();

    // delete
    void on_buttonDelete_clicked();

    // pulsanti per x^exp
    void on_button_x_clicked();
    void on_button_x2_clicked();
    void on_button_x3_clicked();
    void on_button_xn_clicked();

    // pulsanti operazioni
    void on_buttonAdd_clicked();
    void on_buttonSub_clicked();
    void on_buttonMult_clicked();
    void on_buttonDiv_clicked();

    // equals
    void on_buttonEquals_clicked();

    // negate
    void on_buttonNegate_clicked();

    // derivate
    void on_buttonDerivate_clicked();

    // solve
    void on_buttonSolve_clicked();

private:
    Ui::calc* ui;

    polinomio temp, stored;
    QString op;
    bool pendingOp, solved;
};

#endif // CALC_H
