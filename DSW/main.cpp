#include "mainwindow.h"
#include <QApplication>
#include "dsw.h"
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    int width = w.frameGeometry().width();
    int height = w.frameGeometry().height();
    QDesktopWidget wid;
    int screenWidth = wid.screen()->width();
    int screenHeight = wid.screen()->height();
    w.setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);

    w.show();

    return a.exec();
}
