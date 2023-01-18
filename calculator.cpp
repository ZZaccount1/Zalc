#include <iostream>
#include <QRegularExpression>

#include "calculator.h"
#include "./ui_calculator.h"

double calcVal = 0.0;

double memVal = 0.0;

bool addTrigger = false;
bool subTrigger = false;
bool multTrigger = false;
bool divTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i = 0; i < 10; i++)
    {
        QString butName = "Button" + QString::number(i);

        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtraction, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Division, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearButton()));

    connect(ui->MemAdd, SIGNAL(released()), this, SLOT(MemAdd()));
    connect(ui->MemClear, SIGNAL(released()), this, SLOT(MemRem()));
    connect(ui->MemGet, SIGNAL(released()), this, SLOT(MemGet()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0.0) || (displayVal.toDouble() == 0))
    {
        ui->Display->setText(butVal);
    }
    else
    {
        double dblVal = (displayVal + butVal).toDouble();
        ui->Display->setText(QString::number(dblVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed()
{
    addTrigger = false;
    subTrigger = false;
    multTrigger = false;
    divTrigger = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString operationChar = "";

    if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
        operationChar = "+";
    }
    else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0)
    {
        subTrigger = true;
        operationChar = "-";
    }
    else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0)
    {
        multTrigger = true;
        operationChar = "*";
    }
    else if (QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
        operationChar = "/";
    }
    ui->Display->setText(operationChar);
}

void Calculator::EqualButton()
{
    double solution = 0.0;
    QString displayText = ui->Display->text();
    double dblText = displayText.toDouble();
    if(addTrigger || subTrigger|| multTrigger || divTrigger)
    {
        if(addTrigger)
        {
            solution = calcVal + dblText;
        }
        else if(subTrigger)
        {
            solution = calcVal - dblText;
        }
        else if(multTrigger)
        {
            solution = calcVal * dblText;
        }
        else if(divTrigger)
        {
            solution = calcVal / dblText;
        }
    }

    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign()
{
    QString displayVal = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayVal);
    if(match.hasMatch())
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void Calculator::ClearButton()
{
    ui->Display->setText("");
    calcVal = 0.0;
    addTrigger = false;
    subTrigger = false;
    multTrigger = false;
    divTrigger = false;
}
void Calculator::MemAdd()
{
    memVal = (ui->Display->text()).toDouble();
    //std::cout<<memVal<<"\t"<<calcVal<<std::endl;
    Calculator::ClearButton();
}

void Calculator::MemRem()
{
    memVal = 0.0;
}

void Calculator::MemGet()
{
    ui->Display->setText(QString::number(memVal));
}
