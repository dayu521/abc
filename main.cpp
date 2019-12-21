#include "widget.h"

#include <QApplication>
//#include<QPushButton>
//#include<QPointer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
//    QPushButton * p=new QPushButton;
//    QPointer<QPushButton> pp(p);
//    delete pp;
//    if(pp)
//        pp->show();
    return a.exec();
}
