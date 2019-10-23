#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dsw.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QScrollArea>
#include <QElapsedTimer>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*ubacivanje elemenata u stablo*/
void MainWindow::on_pushButton_clicked()
{
    dsw = new DSW();
    ui->pushButton->setEnabled(false);

    int i=0;
    int numberOfNodes = ui->brojCvorova->text().toInt();

    QString text = ui->cvorovi->text();
    QStringList list = text.split(" ",QString::SkipEmptyParts);


    foreach(QString num, list){
        dsw->insert(num.toInt());
        ++i;
    }

    if(i != numberOfNodes || numberOfNodes==0){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","Niste dobro uneli parametre!");
        messageBox.setFixedSize(500,200);
        dsw->~DSW();
        ui->pushButton->setEnabled(true);
        return;
    }

    cout << "Ubaci u stablo: "<<endl;
    dsw->preorder();
    dsw->inorder();
    dsw->postorder();
    cout << "-----------------------------------------------------------------"<< endl;

    QPixmap m = dsw->show();
    QDir dir;
    QString str1=dir.absolutePath() + "/output.png";
    QImage image(str1);
    item=new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addItem(item);
}

/*Transformacija stabla u niz*/
void MainWindow::on_pushButton_2_clicked()
{

    ui->pushButton_2->setEnabled(false);
    dsw->treeToArray();
    QPixmap m = dsw->show();
    QDir dir;
    QString str1=dir.absolutePath() + "/output.png";
    QImage image(str1);
    item=new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addItem(item);

    cout << "Transformacija u niz: "<<endl;
    dsw->preorder();
    dsw->inorder();
    dsw->postorder();
    cout << "-----------------------------------------------------------------"<< endl;

}

/*Transformacija niza u stablo*/
void MainWindow::on_pushButton_3_clicked()
{

    dsw->arrayToTree();
    QPixmap m = dsw->show();
    QDir dir;
    QString str1=dir.absolutePath() + "/output.png";
    QImage image(str1);
    item=new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addItem(item);

    cout << "Niz u stablo: "<<endl;
    dsw->preorder();
    dsw->inorder();
    dsw->postorder();
    cout << "-----------------------------------------------------------------"<< endl;

    dsw->~DSW();
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
}


