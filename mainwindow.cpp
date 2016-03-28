#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(calculate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

Answer * MainWindow::calculateBayesianDecision(Alternative **_alternatives)
{
    Alternative ** alt = _alternatives;
    double u1,u2; //Функция полезности при принятии решения d1 и d2 соответствено;
    u1 = alt[1]->getValuation();
    u2 = alt[0]->getProbability()*alt[0]->getValuation()+alt[2]->getProbability()*alt[2]->getValuation();
    if(u1 >= u2)
    {
        return new Answer(u1,alt[1]->getDecision());
    }
    else
    {
        return new Answer(u2,alt[0]->getDecision());
    }
}

Answer * MainWindow::calculateMinMaxDecision(Alternative **_alternatives)
{
    Alternative ** alt = _alternatives;
    double u1,u2; //Функция полезности при принятии решения d1 и d2 соответствено;
    u1 = alt[1]->getValuation();
    u2 = alt[2]->getValuation();

    if(u1 >= u2)
    {
        return new Answer(u1,alt[1]->getDecision());
    }
    else
    {
        return new Answer(u2,alt[2]->getDecision());
    }
}


void MainWindow::calculate()
{
    /*Массива вероятностей события*/
    double probability[2];
      probability[0]  =  ui->lineEdit->text().toDouble(); // вероятность роста рынка
      probability[1] = 1 - probability[0]; // вероятность падения рынка

    /*Массив возможных решений*/
    QString decisions[2];
    decisions[0] = QString(trUtf8("инвестировать в облигации"));
    decisions[1] = QString(trUtf8("инвестировать в акции"));

    /*Массива ценности каждой альтернативы*/
    double valuation[4];

    valuation[0] =  ui->lineEdit1->text().toDouble();//ценность первой альтернативы
    valuation[1] =  ui->lineEdit2->text().toDouble();//ценность второй альтернативы
    valuation[2] =  ui->lineEdit3->text().toDouble();//ценность третей альтернативы


    /*Массив альтернатив*/
    Alternative * alernatives[3];
    //успешное вложение в акции: рынок растет, купили акции
    alernatives[0] = new Alternative(decisions[1],probability[0],valuation[0]);

    //успешно вложили в облигации: рынок падает, купили облигации
    alernatives[1] = new Alternative(decisions[0],probability[1],valuation[1]);

    //неуспешно вложили в акции: рынок падает, купили акции
    alernatives[2] = new Alternative(decisions[1],probability[1],valuation[2]);



    //Произодим расчет Байесовского решения
    Answer * BayesianDecision = calculateBayesianDecision(alernatives);
    //Производим расчет Минимксного решения
    Answer * MinMaxDecision = calculateMinMaxDecision(alernatives);



    //Заполняем поле вывода
    ui->plainTextEdit->setPlainText(trUtf8("Было принято решение: ")+BayesianDecision->getDecision());
    ui->plainTextEdit->appendPlainText(trUtf8("Полезность решения: ")+QString::number(BayesianDecision->getUsefulness()));
    ui->plainTextEdit2->setPlainText(trUtf8("Было принято решение: ")+MinMaxDecision->getDecision());
    ui->plainTextEdit2->appendPlainText(trUtf8("Полезность решения: ")+QString::number(MinMaxDecision->getUsefulness()));
}
