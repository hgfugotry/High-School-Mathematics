#include<fstream>
#include<string>
#include<vector>
#include<regex>
#include<cctype>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QString>
#include<QFile>
#include"arithmeticOfStdString/arithmeticOfStdString.h"

#define ERRORINPUT "Error Input!"

bool isAllEmpty(std::string str)
{
    if(str.begin()==str.end())
        return true;
    for(char i:str)
    {
        if(!std::isspace(i))
            return false;
    }
    return true;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->variableEdit->setReadOnly(true);

    connect(ui->expressionEdit,SIGNAL(returnPressed()),this,SLOT(on_calculateButton_clicked()));
    connect(ui->actionOpen_O,&QAction::triggered,this,&MainWindow::actionOpenSlot);
    connect(ui->actionSave_As_S,&QAction::triggered,this,&MainWindow::actionSaveAsSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

namespace namespace0
{
    char variable='a';
    std::string variableStdString="";
    std::vector<char> vars;
}

void MainWindow::on_calculateButton_clicked()
{
    unsigned int line=1;

    std::string str="",expression="";
    expression=ui->expressionEdit->text().toStdString();

    if(namespace0::vars.begin()!=namespace0::vars.end())
    {
        std::vector<std::string> expressions;
        std::string varstrs=ui->dataEdit->toPlainText().toStdString();
        str=varstrs;
        auto errorInput=[&line](std::string& varstrs,const size_t& varnum)
        {
            unsigned long num=0;
            for(unsigned long i=0;i<varstrs.size();i++)
            {
                if(!std::isspace(varstrs[i]))
                    num++;
                while(!std::isspace(varstrs[i]))
                {
                    i++;
                }
                if(varstrs[i]=='\n'||i>=varstrs.size()-1)
                {
                    if(num!=varnum&&num!=0)
                    {
                        return true;
                    }
                    ++line;
                    num=0;
                }
            }
            return false;
        };
        auto sayError=[&str](unsigned int line,char* errorCode="0")
        {
            char linestr[15];
            sprintf(linestr,"%u",line);
            str+=ERRORINPUT;
            str+="Line ";
            str+=linestr;
            str+=".Code ";
            str+=errorCode;
        };
        if(errorInput(varstrs,namespace0::vars.size()))
        {
            sayError(line,"0");
            goto a;
        }

        while(!isAllEmpty(varstrs))
        {
            line=1;
            std::vector<std::string> values;
            for(unsigned long i=0;i<namespace0::vars.size();i++)
            {
                values.push_back(calculateStdStringExpression(cinReadStdStringFromStdString(varstrs)));
                if(*(values.end()-1)=="")
                {
                    sayError(line,"1");
                }
            }
            expressions.push_back(replaceVariable(expression,values,namespace0::vars));
            if(*(expressions.end()-1)=="")
            {
                sayError(line,"2");
            }
            line++;
        }

        str+="\n\nResult:\n";
        line=1;
        for(std::string i:expressions)
        {
            std::string temp=calculateStdStringExpression(i);
            if(temp=="")
            {
                sayError(line,"3");
            }
            str+=temp;
            str+="\n";
            ++line;
        }
        a:ui->dataEdit->setText(str.c_str());
    }
    else
    {
        str=calculateStdStringExpression(expression);
        if(str=="")
            str=ERRORINPUT;
        ui->expressionEdit->setText(str.c_str());
    }
}

void MainWindow::on_helpButton_clicked()
{
    std::string information="+：加法运算\n"
                              "-：减法运算\n"
                              "*：乘法运算\n"
                              "/：除法运算\n"
                              "^：幂运算（只支持整数指数幂）\n"
                              "()：提高运算优先级\n";
    QMessageBox::information(this,"Help",information.c_str());
}

void MainWindow::actionOpenSlot()
{
    QString file=QFileDialog::getOpenFileName(this, tr("Open File"),QCoreApplication::applicationFilePath(),tr("*.txt"));
    if(file.isEmpty())
        ;
    else
    {
        QFile data(file);
        data.open(QIODevice::ReadOnly);
        QByteArray ba=data.readAll();
        ui->dataEdit->setText(QString(ba));
        data.close();
    }
}

void MainWindow::actionSaveAsSlot()
{
    QString file=QFileDialog::getSaveFileName(this, tr("Open File"),QCoreApplication::applicationFilePath(),tr("*.txt"));
    if(file.isEmpty())
        ;
    else
    {
        QFile data(file);
        data.open(QIODevice::WriteOnly);
        QByteArray ba(ui->dataEdit->toPlainText().toStdString().c_str());
        data.write(ba);
        data.close();
    }
}

void MainWindow::on_createAVariableButton_clicked()
{
    if(namespace0::variable<='z')
    {
        namespace0::vars.push_back(namespace0::variable);
        namespace0::variableStdString+=namespace0::variable;
        namespace0::variableStdString+=" ";
        ui->variableEdit->setText(namespace0::variableStdString.c_str());
        namespace0::variable++;
    }
    else
    {
        QMessageBox::warning(this,"WARNING","CANNOT CREATE NEW VARIABLE!");
    }
}

void MainWindow::on_deleteAVariableButton_clicked()
{
    if(namespace0::variable>'a')
    {
        namespace0::vars.pop_back();
        namespace0::variableStdString.erase(namespace0::variableStdString.end()-1);
        namespace0::variableStdString.erase(namespace0::variableStdString.end()-1);
        ui->variableEdit->setText(namespace0::variableStdString.c_str());
        namespace0::variable--;
    }
    else
    {
        QMessageBox::warning(this,"WARNING","IT HASN'T ANY VARIABLE IN THE VARIABLE BLOCK!");
    }
}


void MainWindow::on_versionButton_clicked()
{
    QMessageBox::information(this,"Version information","Version:1.0.0\n\t\tMade by LiuLiYuan");
}
