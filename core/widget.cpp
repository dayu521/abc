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
#include"simulator.h"
#include<QPoint>
#include<QStackedWidget>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    initUI();
    initAction();
    prepare();
}

void Widget::setSimulator(std::initializer_list<std::shared_ptr<Simulator> > list_)
{
//    std::copy(list_.begin(),list_.end(),simContainer);
    for(auto x_:list_){
        simContainer.append(x_);
        int index_=dataInputPane->addWidget(x_->getUi());
        ui->menuList->insertItem(index_,x_->getName());
    }
    setWindowTitle(simContainer[currentIndex]->getName());
}

Widget::~Widget()
{
    delete ui;
    delete globalSetting;
    delete dataInputPane;
}

void Widget::loadCnf()
{
    settings.animationInterval=500;
}

void Widget::initUI()
{
    globalSetting=new SettingPane();
    dataInputPane=new QStackedWidget();

}

void Widget::prepareNewSimulation()
{

}

void Widget::initAction()
{
    auto startAct=new QAction("开始模拟");
    connect(startAct,&QAction::triggered,[=](){
        if(animationTimer->isActive()){
            animationTimer->stop();
            startAct->setText("开始模拟");
        }else {
            animationTimer->start();
            startAct->setText("暂停");
        }
    });

    ui->leftContainerWidget->hide();
    auto show_SideAct=new QAction("显示侧栏");
    connect(show_SideAct,&QAction::triggered,[=](bool){
        if(ui->leftContainerWidget->isHidden()){
            ui->leftContainerWidget->show();
            show_SideAct->setText("隐藏侧栏");
        } else{
            ui->leftContainerWidget->hide();
            show_SideAct->setText("显示侧栏");
        }
    });

    ui->rigthBottom->hide();
    auto ac2_=new QAction("显示底栏");
    connect(ac2_,&QAction::triggered,[=](bool){
        if(ui->rigthBottom->isHidden()){
            ui->rigthBottom->show();
            ac2_->setText("隐藏底栏");
        } else{
            ui->rigthBottom->hide();
            ac2_->setText("显示底栏");
        }
    });

    auto ac3_=new QAction("配置设置");
    connect(ac3_,&QAction::triggered,[=](bool){
        globalSetting->move(width()/2-globalSetting->width()/2,height()/2-globalSetting->height()/2);
        globalSetting->show();
    });
    auto data_InputAct=new QAction("数据设定面板");
    connect(data_InputAct,&QAction::triggered,[=](bool){
        dataInputPane->setCurrentIndex(ui->menuList->currentIndex());
        dataInputPane->show();
    });

    addActions({startAct,data_InputAct,show_SideAct,ac2_,ac3_});
}

void Widget::prepare()
{
    animationTimer=new QTimer(this);
    animationTimer->setInterval(settings.animationInterval);
    connect(animationTimer,&QTimer::timeout,[=](){
        ui->rightContainerWidget->paint(simContainer[currentIndex]->simulation());
    });

    connect(ui->menuList,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int x){
        currentIndex=x;
        dataInputPane->setCurrentIndex(x);
        dataInputPane->resize(dataInputPane->currentWidget()->size());
        setWindowTitle(simContainer[x]->getName());
    });
    ui->menuList->setCurrentIndex(currentIndex);
    dataInputPane->setCurrentIndex(currentIndex);

}

void Widget::resizeEvent(QResizeEvent *event)
{

}


void Widget::on_startBtn_clicked()
{
    qDebug()<<ui->leftContainerWidget->size();
}
