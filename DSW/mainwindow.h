#ifndef MAINWINDOW _H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dsw.h"
#include <QGraphicsItem>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    DSW* dsw;
    QGraphicsItem* item;
    QGraphicsScene* scene;

};

#endif // MAINWINDOW_H
