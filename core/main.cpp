#include "widget.h"
#include"demosim.h"
#include"rbtreesimulation.h"
#include<memory>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.addSimulator({{std::shared_ptr<Simulator>(new RBtreeSimulation)},{std::shared_ptr<Simulator>(new DemoSim)}});
    w.show();
    return a.exec();
}
