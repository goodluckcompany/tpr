#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(calculate()));
    connect(ui->checkBox,SIGNAL(toggled(bool)),ui->doubleSpinBox_5,SLOT(setEnabled(bool)));
    connect(ui->checkBox_2,SIGNAL(toggled(bool)),ui->doubleSpinBox_6,SLOT(setEnabled(bool)));
    connect(ui->checkBox_3,SIGNAL(toggled(bool)),ui->doubleSpinBox_7,SLOT(setEnabled(bool)));
    connect(ui->action,SIGNAL(triggered(bool)),this,SLOT(setTest1()));
    connect(ui->action_2,SIGNAL(triggered(bool)),this,SLOT(setTest2()));
    connect(ui->action_3,SIGNAL(triggered(bool)),this,SLOT(setTest3()));
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

Answer * MainWindow::calculateUsefulnessAccurateInformation(Alternative **_alternatives)
{
    Alternative ** alt = _alternatives;
    double v1 = alt[0]->getValuation();
    double v2 = alt[1]->getValuation();
    double v3 = alt[2]->getValuation();

    double indP = (v2 - v3)/(v1 - v3);
    double u1 = alt[0]->getProbability()*(v1 - v2);
    double u2 = (1 - alt[0]->getProbability())*(v2 - v3);

    if(alt[0]->getProbability() <= indP)
    {
        return new Answer(u1,"");
    }
    else
    {
        return new Answer(u2,"");
    }

}

void MainWindow::calculate()
{
    /*Массива вероятностей события*/
    double probability[2];
      probability[0]  =  ui->doubleSpinBox->value(); // вероятность роста рынка
      probability[1] = 1 - probability[0]; // вероятность падения рынка

      /*Переменная для учёта дополнительный рисков*/
       double addprob = 1;

      if(ui->doubleSpinBox_5->isEnabled())
          addprob = addprob * ui->doubleSpinBox_5->value();
      if (ui->doubleSpinBox_6->isEnabled())
          addprob = addprob * ui->doubleSpinBox_6->value();
      if (ui->doubleSpinBox_7->isEnabled())
          addprob = addprob * ui->doubleSpinBox_7->value();

        if (addprob != 1)
            {
                probability[0] = probability[0] - addprob;
                probability[1] = 1 - probability[0];
            if (probability[0]<0)
            {
                probability[0] = 0;
                probability[1] = 1;
            }
        }

    /*Массив возможных решений*/
    QString decisions[2];
    decisions[0] = QString(trUtf8("инвестировать в облигации"));
    decisions[1] = QString(trUtf8("инвестировать в акции"));

    /*Массива ценности каждой альтернативы*/
    double valuation[4];

    valuation[0] =  ui->doubleSpinBox_2->value();//ценность первой альтернативы
    valuation[1] =  ui->doubleSpinBox_3->value();//ценность второй альтернативы
    valuation[2] =  ui->doubleSpinBox_4->value();//ценность третей альтернативы


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
    Answer * UsefulnessAccurateInformation = calculateUsefulnessAccurateInformation(alernatives);


    //Заполняем поле вывода
    ui->plainTextEdit->setPlainText(trUtf8("Было принято решение: ")+BayesianDecision->getDecision());
    ui->plainTextEdit->appendPlainText(trUtf8("Полезность решения: ")+QString::number(BayesianDecision->getUsefulness()));
    ui->plainTextEdit->appendPlainText(trUtf8("Было принято решение: ")+MinMaxDecision->getDecision());
    ui->plainTextEdit->appendPlainText(trUtf8("Полезность решения: ")+QString::number(MinMaxDecision->getUsefulness()));
    ui->plainTextEdit->appendPlainText(trUtf8("Полезность точной информации: ")+QString::number(UsefulnessAccurateInformation->getUsefulness()));
}

void MainWindow::setTest1()
{
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->doubleSpinBox_2->setValue(5000);
    ui->doubleSpinBox_3->setValue(1000);
    ui->doubleSpinBox_4->setValue(-5000);
    ui->checkBox->setChecked(true);
    ui->doubleSpinBox_5->setValue(0.07);
}
void MainWindow::setTest2()
{
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->doubleSpinBox_2->setValue(10000);
    ui->doubleSpinBox_3->setValue(2000);
    ui->doubleSpinBox_4->setValue(-7000);
    ui->checkBox_2->setChecked(true);
    ui->doubleSpinBox_6->setValue(0.33);
    ui->checkBox_3->setChecked(true);
    ui->doubleSpinBox_7->setValue(0.04);
}
void MainWindow::setTest3()
{
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->doubleSpinBox_2->setValue(8500);
    ui->doubleSpinBox_3->setValue(1550);
    ui->doubleSpinBox_4->setValue(-8500);
    ui->checkBox->setChecked(true);
    ui->doubleSpinBox_5->setValue(0.75);
    ui->checkBox_3->setChecked(true);
    ui->doubleSpinBox_7->setValue(0.45);
}
