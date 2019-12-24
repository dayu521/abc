#include "rbtreesim.h"
#include<QPixmap>
#include<QWidget>
#include<QPushButton>

RBtreeSim::RBtreeSim(QString name_):name(name_)
{
    panel=new QWidget;
    panel->setAutoFillBackground(true);
    auto pp=panel->palette();
    pp.setColor(QPalette::Background,Qt::red);
    panel->resize(800,500);
    panel->setPalette(pp);
    auto btn=new QPushButton(name,panel);

}

RBtreeSim::~RBtreeSim()
{
}

QWidget *RBtreeSim::getUi()
{
    return panel;
}

QString RBtreeSim::getName() const
{
    return name;
}

void RBtreeSim::startSimulate()
{

}

void RBtreeSim::clearSimulate()
{

}

QPixmap RBtreeSim::simulation() const
{
    return QPixmap();
}
