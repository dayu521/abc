#include "widget.h"
#include"rbtreesim.h"
#include<memory>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setSimulator({std::shared_ptr<Simulator>(new RBtreeSim),std::shared_ptr<Simulator>(new RBtreeSim("尼玛死了"))});
    w.show();
    return a.exec();
}
