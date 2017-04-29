#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->calcButton, &QPushButton::pressed, this, &MainWindow::calc);
    ui->textBrowser->append("Calculation will take a few seconds. The programm won`t respond during calculation.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calc(){
    ui->textBrowser->clear();
    basis = new Basis(ui->j1Box->value(), ui->j2Box->value());
    basis->start();
    State *currC = basis->root;
    while(currC->j >= 1){
        State *curr = currC;
        while(curr->m >= -curr->j){
            QString tmp = "|" + QString::number(ui->j1Box->value()) + ", " + QString::number(ui->j2Box->value()) + ", " + QString::number(curr->j) + ", " + QString::number(curr->m) + ">";
            tmp += " = " ;
            QHash<QPair<qreal, qreal>, qreal>::iterator i;
            for (i = curr->corr.begin(); i != curr->corr.end(); ++i){
                tmp += QString::number(i.value()) + "*|" + QString::number(i.key().first) + ", " +  QString::number(i.key().second) + "> + ";
            }
            tmp.chop(2);
            ui->textBrowser->append(tmp);
            if(curr->m != -curr->j){
                curr = curr->right;
            }else{
                break;
            }
        }
        if(currC->j != 1){
            ui->textBrowser->append("");
            currC = currC->left;
        }else{
            break;
        }
    }
}
