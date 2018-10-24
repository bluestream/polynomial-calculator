#include "calc.h"
#include "ui_calc.h"

/**********
 * PUBLIC *
 *********/

// costruttori/distruttori
calc::calc(QWidget *parent) : QMainWindow(parent), ui(new Ui::calc), pendingOp(false), solved(false)
{
    ui->setupUi(this);
}

calc::~calc()
{
    delete ui;
}

// metodi di classe
void calc::digitClicked()
{
    checkInput();
    ui->displayError->clear();
    QPushButton* digitButton = qobject_cast<QPushButton*>(sender());
    QString currentText = ui->displayInput->text();
    try {
        if (currentText.endsWith('x'))
            throw eccezione("ERRORE\nInserisci un'operazione dopo il grado di x");
        if (currentText.isEmpty())
            ui->displayInput->setText(digitButton->text());
        if (currentText == "0" || currentText == "-0" || currentText == "+0")
            ui->displayInput->setText(currentText.replace("0", digitButton->text()));
        else ui->displayInput->setText(currentText + digitButton->text());
    }
    catch (eccezione& e) {
        ui->displayError->setText(e.getMsg());
    }
}

void calc::xClicked()
{
    checkInput();
    ui->displayError->clear();
    QPushButton* xButton = qobject_cast<QPushButton*>(sender());
    QString currentText = ui->displayInput->text();
    try {
        if (currentText.contains('x'))
            throw eccezione("ERRORE\nInserisci un'operazione dopo il grado di x");
        if (xButton->text() == "x^n")
            ui->displayInput->setText(currentText + "x^");
        else ui->displayInput->setText(currentText + xButton->text());
    }
    catch (eccezione& e) {
        ui->displayError->setText(e.getMsg());
    }
}

void calc::operationClicked()
{
    checkInput();
    ui->displayError->clear();
    QPushButton* opButton = qobject_cast<QPushButton*>(sender());
    QString currentText = ui->displayInput->text();
    try {
        // controlli preliminari
        if (currentText.endsWith('^'))
            throw eccezione("ERRORE\nInserisci un esponente prima di selezionare un'operazione");
        // addizione e sottrazione
        if (opButton->text() == "+" || opButton->text() == "-") {
            if (currentText.isEmpty() || currentText == "+" || currentText == "-")
                ui->displayInput->setText(opButton->text());
            else {
                storeMonomio(currentText);
                ui->displayString->setText(ui->displayString->text() + currentText);
                ui->displayInput->setText(opButton->text());
            }
        }
        // moltiplicazione e divisione
        else {
            if (currentText.isEmpty() || currentText == "+" || currentText == "-")
                throw eccezione("ERRORE\nInserisci un numero prima di selezionare un'operazione");
            if (pendingOp)
                throw eccezione("ERRORE\nTermina l'operazione in corso tramite il pulsante '=' per continuare"
                                " con una nuova operazione");
            ui->displayString->setText(ui->displayString->text() + currentText + " " + opButton->text() + " ");
            ui->displayInput->clear();
            storeMonomio(currentText);
            pendingOp = true;
            op = opButton->text();
            stored = temp;
            temp.clearItems();
        }
    }
    catch (eccezione& e) {
        ui->displayError->setText(e.getMsg());
    }
}

monomio calc::getMonomio(QString s)
{
    int coeff = 0;
    int exp = 0;
    // se la stringa NON contiene 'x', ho solo il coefficiente
    if (!s.contains('x')) {
        coeff = s.toInt();
        return monomio(coeff, 0);
    }
    // se la stringa contiene solo 'x' ma non '^', ho un coefficiente e l'esponente == 1
    if (s.contains('x') && !s.contains('^')) {
        s.remove('x');
        if (s.isEmpty())                    // caso 'x'
            return monomio(1, 1);
        if (s.size() == 1) {
            if (s.contains("+"))            // caso "+x"
                return monomio(1, 1);
            if (s.contains("-"))            // caso "-x"
                return monomio(-1, 1);
        }
        coeff = s.toInt();
        return monomio(coeff, 1);
    }
    // se la stringa contiene "x^", ho sia coefficiente che esponente
    if (s.contains("x^")) {
        QStringList SL = s.split("x^");
        QString e = SL.back();
        exp = e.toInt();
        QString c = SL.front();
        if (c.isEmpty())                    // caso "x^"
            return monomio(1, exp);
        if (c.size() == 1) {
            if (c.contains("+"))            // caso "+x^"
                return monomio(1, exp);
            if (c.contains("-"))            // caso "-x^"
                return monomio(-1, exp);
        }
        coeff = c.toInt();
        return monomio(coeff, exp);
    }
    return monomio(coeff, exp);
}

equazione* calc::getEquation(polinomio& p)
{
    p.simplify();
    p.sortItems();
    equazione* e = NULL;
    // creazione effettiva sottooggetti
    if (p.getHighestDegree() == 1)
        return e = new gradoPrimo(p);
    if (p.getHighestDegree() == 2)
        return e = new gradoSecondo(p);
    return e = new gradoN(p);
}

void calc::storeMonomio(QString s)
{
    monomio m = getMonomio(s);
    temp.addMonomio(m);
    //std::cerr << "STORED: " << stored << endl;
    //std::cerr << "TEMP: " << temp << endl;
}

void calc::checkInput()
{
    if (solved)
        on_buttonClear_clicked();
}

/*****************
 * PRIVATE SLOTS *
 ****************/

// PULSANTI NUMERICI
void calc::on_button0_clicked() { digitClicked(); }
void calc::on_button1_clicked() { digitClicked(); }
void calc::on_button2_clicked() { digitClicked(); }
void calc::on_button3_clicked() { digitClicked(); }
void calc::on_button4_clicked() { digitClicked(); }
void calc::on_button5_clicked() { digitClicked(); }
void calc::on_button6_clicked() { digitClicked(); }
void calc::on_button7_clicked() { digitClicked(); }
void calc::on_button8_clicked() { digitClicked(); }
void calc::on_button9_clicked() { digitClicked(); }

// CLEAR
void calc::on_buttonClear_clicked()
{
    ui->displayError->clear();
    ui->displayString->clear();
    ui->displayInput->clear();
    temp.clearItems();
    stored.clearItems();
    solved = false;
    pendingOp = false;
    op.clear();
}

// DELETE
void calc::on_buttonDelete_clicked()
{
    ui->displayError->clear();
    QString currentText = ui->displayInput->text();
    if (!currentText.isEmpty()) {
        currentText.chop(1);
        ui->displayInput->setText(currentText);
    }
}

// PULSANTI PER X^EXP
void calc::on_button_x_clicked() { xClicked(); }
void calc::on_button_x2_clicked() { xClicked(); }
void calc::on_button_x3_clicked() { xClicked(); }
void calc::on_button_xn_clicked() { xClicked(); }

// PULSANTI OPERAZIONI
void calc::on_buttonAdd_clicked() { operationClicked(); }
void calc::on_buttonSub_clicked() { operationClicked(); }
void calc::on_buttonMult_clicked() { operationClicked(); }
void calc::on_buttonDiv_clicked() { operationClicked(); }

// EQUALS
void calc::on_buttonEquals_clicked()
{
    if (op == "/" || op == "solve")
        checkInput();
    ui->displayError->clear();
    QString currentText = ui->displayInput->text();
    try {
        if (currentText.isEmpty())
            throw eccezione("ERRORE\nInserisci un numero");
        if (currentText == "+" || currentText == "-")
            ui->displayInput->clear();
        // input valido
        else {
            if (!solved) {
                ui->displayString->setText(ui->displayString->text() + currentText);
                storeMonomio(currentText);
            }
            else ui->displayString->setText(currentText);
        }
        // controllo operazione
        if (pendingOp) {
            if (op == "*") {
                temp = stored * temp;
                temp.simplify();
                temp.sortItems();
                ui->displayInput->setText(temp.toQString());
            }
            if (op == "/") {
                vector<polinomio> result = stored.divide(temp);
                QString q = result[0].toQString();
                QString r = result[1].toQString();
                if (r.isEmpty())
                    r = "0";
                ui->displayInput->setText("Q: " + q + "\t" + "R: " + r);
            }
            pendingOp = false;
        }
        else {
            temp.simplify();
            temp.sortItems();
            ui->displayInput->setText(temp.toQString());
        }
        solved = true;
    }
    catch (eccezione& e) {
        if (e.getMsg() == "ERRORE\nNon e' possibile dividere per 0")
            on_buttonClear_clicked();
        ui->displayError->setText(e.getMsg());
    }
}

// NEGATE
void calc::on_buttonNegate_clicked()
{
    if (op == "/" || op == "solve")
        checkInput();
    ui->displayError->clear();
    QString currentText = ui->displayInput->text();
    try {
        if (currentText.isEmpty())
            throw eccezione("ERRORE\nInserisci un numero");
        if (currentText != "+" && currentText != "-") {
            if (!solved) {
                ui->displayString->setText(ui->displayString->text() + currentText);
                storeMonomio(currentText);
            }
            else ui->displayString->setText(currentText);
        }
        temp.negate();
        QString s = temp.toQString();
        ui->displayInput->setText(s);
        solved = true;
    }
    catch (eccezione& e) {
        ui->displayError->setText(e.getMsg());
    }
}

// DERIVATE
void calc::on_buttonDerivate_clicked()
{
    if (op == "/" || op == "solve")
        checkInput();
    ui->displayError->clear();
    QString currentText = ui->displayInput->text();
    try {
        if (currentText.isEmpty())
            throw eccezione("ERRORE\nInserisci un numero");
        if (currentText != "+" && currentText != "-") {
            if (!solved) {
                ui->displayString->setText(ui->displayString->text() + currentText);
                storeMonomio(currentText);
            }
            else ui->displayString->setText(currentText);
        }
        temp = temp.derivate();
        QString s = temp.toQString();
        ui->displayInput->setText(s);
        solved = true;
    }
    catch (eccezione& e) {
        ui->displayError->setText(e.getMsg());
    }
}

// SOLVE
void calc::on_buttonSolve_clicked()
{
    if (op == "/" || op == "solve")
        checkInput();
    ui->displayError->clear();
    QString currentText = ui->displayInput->text();
    try {
        if (currentText.isEmpty())
            throw eccezione("ERRORE\nInserisci un numero");
        if (currentText != "+" && currentText != "-") {
            if (!solved) {
                ui->displayString->setText(ui->displayString->text() + currentText);
                storeMonomio(currentText);
            }
            else ui->displayString->setText(currentText);
        }
        equazione* e = getEquation(temp);
        ui->displayString->setText(temp.toQString());
        vector<double> result = e->solve();
        ui->displayInput->clear();
        for (unsigned int i = 0; i < result.size(); ++i) {
            QString index = QString::number(i+1);
            QString x = QString::number(result[i]);
            ui->displayInput->setText(ui->displayInput->text() + "\tx" + index + ": " + x);
        }
        ui->displayError->setText(e->getType());
        solved = true;
        op = "solve";
    }
    catch (eccezione& e) {
        ui->displayError->setText(e.getMsg());
    }
}
