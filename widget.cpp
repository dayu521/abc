#include "widget.h"
#include "ui_widget.h"
#include<QMenuBar>
#include<QHBoxLayout>
#include<QScrollArea>
#include<QLabel>
#include<QTimer>
#include<QDebug>
#include<QPainter>
#include<QPushButton>
#include<QAction>
#include<QList>
#include<QPropertyAnimation>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initInterface();
    setContextMenuPolicy(Qt::ActionsContextMenu);
    auto ap=new QPropertyAnimation(ui->leftContainerWidget,"geometry",this);
    auto ac1_=new QAction("显示侧栏");
    connect(ac1_,&QAction::triggered,[=](bool){
        ui->leftContainerWidget->show();
    });
    auto ac2_=new QAction("隐藏侧栏");
    connect(ac2_,&QAction::triggered,[=](bool){
        ui->leftContainerWidget->hide();
    });
    auto ac3_=new QAction("设置");
    connect(ac3_,&QAction::triggered,[=](bool){
        globalSetting->move(width()/2-globalSetting->width()/2,height()/2-globalSetting->height()/2);
        globalSetting->show();
    });
    addActions({ac1_,ac2_,ac3_});

    animationTimer=new QTimer(this);
    animationTimer->setInterval(500);
    connect(animationTimer,&QTimer::timeout,[=](){
        rightContainerWidget->paint(i++);
        rightContainerWidget->update();
    });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::initInterface()
{
    globalSetting=new SettingPane();
}

void Widget::prepareNewSimulation()
{

}

void Widget::resizeEvent(QResizeEvent *event)
{
//    qDebug()<<"窗口宽度"<<width();
//    qDebug()<<"左边滚动区域宽度"<<rightContainerWidgetWrap->width();
//    qDebug()<<"右边显示区域宽度"<<rightContainerWidgetWrap->width();
}


void Widget::on_startBtn_clicked()
{
    qDebug()<<ui->leftContainerWidget->size();
}
