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

void Widget::addSimulator(std::initializer_list<Fufu> list_)
{
//    std::copy(list_.begin(),list_.end(),simContainer);
    int i_=simContainer.size();
    for(auto x_:list_){
        simContainer.append(x_);
        simContainer[i_].id=i_;
        int index_=dataInputPane->addWidget(x_.sim->getUi());
        ui->menuList->insertItem(index_,x_.sim->getName());//第一次也将触发currentIndexChanged信号
        i_++;
    }
    changeSimulator(0);
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

    ui->rightContainerWidget->resize(800,800);
}

void Widget::prepareNewSimulation()
{

}

void Widget::initAction()
{
    menu=new QMenu(this);

    auto startAct=menu->addAction("生成模拟数据");
    connect(startAct,&QAction::triggered,[=](){
//        simContainer[currentSimulatorIndex].frameStatusIndex=0;
        currentSimulator->clearSimulateData();
        ui->textBrowser->append(QString("清除已模拟的数据"));
        currentSimulator->produceSimulateData();
        ui->textBrowser->append(QString("[%1]模拟数据生成完成").arg(currentSimulator->getName()));
        currentframeNumber=currentSimulator->frameAllNumber();
        currentframeIndex=0;
        simContainer[currentSimulatorIndex].stat=HasData;
    });

    auto restart_Act=menu->addAction("重新放映");
    connect(restart_Act,&QAction::triggered,[=](){
        currentframeIndex=0;
//        currentSimulator->clearSimulateData();
        ui->rightContainerWidget->initMesg("请开始重新进行放映");
//        if(mode==Automatic)
//            animationTimer->start();
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
            animationTimer->stop();
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
        if(currentframeIndex>=currentframeNumber){
            animationTimer->stop();
            ui->textBrowser->append("放映完成");
            return ;
        }
        currentSimulator->nextFrame(currentframeIndex);
        currentframeIndex++;
        ui->rightContainerWidget->update();
    });

    connect(ui->menuList,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int x){
        animationTimer->stop();
        changeSimulator(x);
    });

    throttleTimer=new QTimer(this);
    throttleTimer->setSingleShot(true);
    connect(throttleTimer,&QTimer::timeout,[this](){
        auto size_=currentSimulator->calculationMinPixSize();
        ui->rightContainerWidget->makeLager(size_.width(),size_.height());
        ui->rightContainerWidget->setPixmapSource(currentSimulator);
        currentSimulator->currentSnapshot(currentframeIndex);
        ui->rightContainerWidget->update();
    });
    connect(this,&Widget::changeElementsSize,[this](int x_){
        currentSimulator->makeElementsBig(x_);
        throttleTimer->start(200);
    });

    ui->horizontalSlider->setValue(settings.animationInterval);
}

void Widget::changeSimulator(int index_)
{
    //保存当前模拟器状态,以待恢复
    simContainer[currentSimulatorIndex].frameStatusIndex=currentframeIndex;
    //恢复新模拟器状态
    currentframeIndex=simContainer[index_].frameStatusIndex;
    currentSimulatorIndex=index_;
    currentSimulator=simContainer[index_].sim.get();
    //相应的控制面板变更
    dataInputPane->setCurrentIndex(index_);
    dataInputPane->resize(dataInputPane->currentWidget()->size());
    //给模拟器更新画布pixmap
    auto size_=currentSimulator->calculationMinPixSize();
    ui->rightContainerWidget->makeLager(size_.width(),size_.height());
    ui->rightContainerWidget->setPixmapSource(currentSimulator);
    ui->rightContainerWidget->initMesg();
    ui->rightContainerWidget->update();

    setWindowTitle(currentSimulator->getName());
    showMsg();
}

void Widget::showMsg()
{
    auto cout=ui->textBrowser;
    cout->clear();
    cout->append(QString("当前模拟:[ %1 ]").arg(currentSimulator->getName()));
    if(mode==Automatic)
        cout->append(QString("自动放映开启"));
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
    if(simContainer[currentSimulatorIndex].stat==Unused){
        ui->textBrowser->append("请先模拟,产生绘图数据");
        return ;
    }
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

void Widget::on_horizontalSlider_valueChanged(int value)
{
    animationTimer->setInterval(value);
}
