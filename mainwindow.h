#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "alternative.h"
#include "answer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //Байесовское решение
    Answer * calculateBayesianDecision(Alternative ** _alternatives);

    //Алтернатива Баесовскому решению, выбрать лучшее решение при худших обстаятельствах
    Answer * calculateMinMaxDecision(Alternative ** _alternatives);

    //Полезность точной информации
    Answer * calculateUsefulnessAccurateInformation(Alternative ** _alternatives);
private slots:
    void calculate();
    void setTest1();
    void setTest2();
    void setTest3();
};

#endif // MAINWINDOW_H
