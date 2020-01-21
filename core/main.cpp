#include "widget.h"
#include"demosim.h"
#include"rbtreesimulation.h"
#include"quicksortsim.h"
#include<memory>
#include<QTranslator>
#include<QtDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator tr;
    if(tr.load(QLocale(),QLatin1String("fuck"),QLatin1String("_")))
        a.installTranslator(&tr);
    Widget w;
    w.addSimulator({{std::shared_ptr<Simulator>(new RBtreeSimulation)},
                    {std::shared_ptr<Simulator>(new DemoSim)},
                    {std::shared_ptr<Simulator>(new QuickSortSimulation)}});
    w.show();
    return a.exec();
}
