#include "widget.h"
#include "ui_widget.h"
#include<QTimer>
#include<QDebug>
#include<QPainter>
#include<QAction>
#include"simulator.h"
#include<QStackedWidget>
#include<QKeyEvent>
#include<QMenu>
#include<QActionGroup>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//    setContextMenuPolicy(Qt::ActionsContextMenu);
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
    globalSetting->installEventFilter(this);
    connect(globalSetting,&SettingPane::changeAnimationSpeed,[=](int x_){
        animationTimer->setInterval(x_);
    });

    dataInputPane=new QStackedWidget();
    dataInputPane->installEventFilter(this);
}

void Widget::prepareNewSimulation()
{

}

void Widget::initAction()
{
    menu=new QMenu(this);

    auto startAct=menu->addAction("开始模拟");
    connect(startAct,&QAction::triggered,[=](){
        changeSimulator(currentIndex);
        ui->textBrowser->append(QString("清除已模拟的数据"));
        currentSimulator->produceSimulateData();
        ui->textBrowser->append(QString("[%1]模拟完成").arg(currentSimulator->getName()));
    });

    auto restart_Act=menu->addAction("重新放映");
    connect(restart_Act,&QAction::triggered,[=](){
        mm=0;
        currentSimulator->clearSimulateData();
        if(mode==Automatic)
            animationTimer->start();
    });

    ui->rigthBottom->hide();
//    auto ac2_=new QAction("显示底栏");
//    connect(ac2_,&QAction::triggered,[=](bool){
//        if(ui->rigthBottom->isHidden()){
//            ui->rigthBottom->show();
//            ac2_->setText("隐藏底栏");
//        } else{
//            ui->rigthBottom->hide();
//            ac2_->setText("显示底栏");
//        }
//    });

    auto set_Act=menu->addAction("配置设置");
    connect(set_Act,&QAction::triggered,[=](bool){
        globalSetting->move(width()/2-globalSetting->width()/2,height()/2-globalSetting->height()/2);
        globalSetting->show();
    });
    auto data_InputAct=menu->addAction("数据设定面板");
    connect(data_InputAct,&QAction::triggered,[=](bool){
        dataInputPane->setCurrentIndex(ui->menuList->currentIndex());
        dataInputPane->show();
    });

    auto menu_sub1=menu->addMenu("其他设置");
    auto autop_Act=menu_sub1->addAction("自动放映");
    autop_Act->setCheckable(true);
    autop_Act->setChecked(true);
    mode=Automatic;
    connect(autop_Act,&QAction::triggered,[=](bool checked){
        if(!checked){
            mode=Manual;
            ui->textBrowser->append("关闭自动放映:请使用 [ 和 ] 进行放映");
        }else{
            mode=Automatic;
            ui->textBrowser->append("自动放映开启:请使用鼠标左键开始/暂停");
        }
    });

    //    ui->leftContainerWidget->hide();
    auto show_SideAct=menu_sub1->addAction("显示侧栏");
    show_SideAct->setCheckable(true);
    show_SideAct->setChecked(true);
    connect(show_SideAct,&QAction::triggered,[=](bool checked){
        if(checked){
            ui->leftContainerWidget->show();
        } else
            ui->leftContainerWidget->hide();
    });
    menu->addMenu(menu_sub1);
}

void Widget::prepare()
{
    animationTimer=new QTimer(this);
    animationTimer->setInterval(settings.animationInterval);
    connect(animationTimer,&QTimer::timeout,[=](){
        if(mm>=100){
            animationTimer->stop();
            ui->textBrowser->append("放映完成");
            return ;
        }
        currentSimulator->nextFrame(mm);
        mm++;
        ui->rightContainerWidget->update();
    });

    connect(ui->menuList,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int x){
        changeSimulator(x);
    });

    throttleTimer=new QTimer(this);
    throttleTimer->setSingleShot(true);
    connect(throttleTimer,&QTimer::timeout,[=](){
        auto size_=currentSimulator->calculationMinPixSize();
        if((ui->rightContainerWidget->size()-size_).isValid())
            ;
        else
            ui->rightContainerWidget->resize(size_);
        ui->rightContainerWidget->setSource(currentSimulator);
        currentSimulator->currentSnapshot(mm);
        ui->rightContainerWidget->update();
    });
    connect(this,&Widget::changeElementsSize,[=](int x_){
        currentSimulator->makeElementsBig(x_);
        throttleTimer->start(200);
    });

}

void Widget::changeSimulator(int index_)
{
    currentIndex=index_;
    currentSimulator=simContainer[index_].get();
    currentSimulator->clearSimulateData();
    animationTimer->stop();
    //相应的控制面板变更
    dataInputPane->setCurrentIndex(index_);
    dataInputPane->resize(dataInputPane->currentWidget()->size());
    //画布换新的simulator的pixmap
    ui->rightContainerWidget->setSource(currentSimulator);
    mm=0;
    setWindowTitle(currentSimulator->getName());
    showMsg();
}

void Widget::showMsg()
{
    auto cout=ui->textBrowser;
    cout->clear();
    cout->append(QString("当前模拟:[ %1 ]").arg(currentSimulator->getName()));
    cout->append(QString("模式:[ 自动放映 ]"));
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

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(mode==Automatic){
        if(event->button()==Qt::LeftButton){
            animationTimer->isActive()?animationTimer->stop():animationTimer->start();
            ui->textBrowser->append(animationTimer->isActive()?"开始":"暂停");
            event->accept();
        }
    }
}

bool Widget::eventFilter(QObject *object, QEvent *event)
{
    if(event->type()==QEvent::KeyPress||event->type()==QEvent::KeyRelease){
        QCoreApplication::sendEvent(this,event);
        return true;
    }
    return false;
}

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(QCursor::pos()+QPoint(5,5));
}

void Widget::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
//    QCoreApplication::quit();
    qApp->closeAllWindows();
}


void Widget::on_startBtn_clicked()
{
    qDebug()<<ui->leftContainerWidget->size();
}
