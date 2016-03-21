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
    u1 = alt[0]->getProbability()*alt[0]->getValuation()+alt[1]->getProbability()*alt[1]->getValuation();
    u2 = alt[2]->getProbability()*alt[2]->getValuation()+alt[3]->getProbability()*alt[3]->getValuation();
    if(u1 >= u2)
    {
        return new Answer(u1,alt[0]->getDecision());
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
    probability[0] = 0.6;// Не будет заморозков
    probability[1] = 1 - probability[0];//Будут заморозки

    /*Массива ценности каждой альтернативы*/
    double valuation[4];
    valuation[0] = 1;
    valuation[1] = 0;
    valuation[2] = 0.7;
    valuation[3] = 0.4;

    /*Массив возможных решений*/
    QString decisions[2];
    decisions[0] = QString(trUtf8("не защищать посевы"));
    decisions[1] = QString(trUtf8("защищать посевы"));

    /*Массив альтернатив*/
    Alternative * alernatives[4];
    alernatives[0] = new Alternative(decisions[0],probability[0],valuation[0]);
    alernatives[1] = new Alternative(decisions[0],probability[1],valuation[1]);
    alernatives[2] = new Alternative(decisions[1],probability[0],valuation[2]);
    alernatives[3] = new Alternative(decisions[1],probability[1],valuation[3]);

    //Произодим расчет Байесовского решения
    Answer * BayesianDecision = calculateBayesianDecision(alernatives);


    //Заполняем поле вывода
    ui->plainTextEdit->setPlainText(trUtf8("Было принято решение: ")+BayesianDecision->getDecision());
    ui->plainTextEdit->appendPlainText(trUtf8("Полезность решения: ")+QString::number(BayesianDecision->getUsefulness()));
}
