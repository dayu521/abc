#include "widget.h"
#include "ui_widget.h"
#include<QTimer>
#include<QDebug>
#include<QPainter>
#include<QAction>
#include"simulator.h"
#include<QStackedWidget>
#include<QKeyEvent>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    initUI();
    initAction();
    loadCnf();
    prepare();
}

void Widget::setSimulator(std::initializer_list<std::shared_ptr<Simulator> > list_)
{
//    std::copy(list_.begin(),list_.end(),simContainer);
    for(auto x_:list_){
        simContainer.append(x_);
        int index_=dataInputPane->addWidget(x_->getUi());
        ui->menuList->insertItem(index_,x_->getName());//第一次也将触发currentIndexChanged信号
    }
    setWindowTitle(simContainer[currentIndex]->getName());
    currentSimulator=simContainer[currentIndex].get();
    ui->rightContainerWidget->setSource(currentSimulator);
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
    settings.canvasWidth=800;
    settings.canvasHeight=500;
}

void Widget::initUI()
{
    globalSetting=new SettingPane(settings,this);
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

    });

    connect(ui->menuList,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int x){
        currentIndex=x;
        currentSimulator=simContainer[x].get();
        //相应的控制面板变更
        dataInputPane->setCurrentIndex(x);
        dataInputPane->resize(dataInputPane->currentWidget()->size());
        //画布换新的simulator的pixmap
        ui->rightContainerWidget->setSource(currentSimulator);
        setWindowTitle(currentSimulator->getName());
    });

    throttleTimer=new QTimer(this);
    throttleTimer->setSingleShot(true);
    connect(throttleTimer,&QTimer::timeout,[=](){
        auto size_=currentSimulator->calculationPixSize();
        if((ui->rightContainerWidget->size()-size_).isValid())
            ;
        else
            ui->rightContainerWidget->resize(size_);
        ui->rightContainerWidget->setSource(currentSimulator);
        currentSimulator->currentSnapshot();
        ui->rightContainerWidget->update();
    });
    connect(this,&Widget::changeElementsSize,[=](int x_){
        currentSimulator->makeElementsBig(x_);
        throttleTimer->start(200);
    });

}

void Widget::resizeEvent(QResizeEvent *event)
{

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control)
        isctl=true;
    //下面可以先统一测试isctl
    else if(event->key()==Qt::Key_Plus){
        if(isctl){
            emit changeElementsSize(factor);
        }
    }else if(event->key()==Qt::Key_Minus){
        if(isctl){
            emit changeElementsSize(-factor);
        }
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control)
        isctl=false;
}


void Widget::on_startBtn_clicked()
{
    qDebug()<<ui->leftContainerWidget->size();
}
