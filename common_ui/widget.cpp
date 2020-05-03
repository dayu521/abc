#include "widget.h"
#include "ui_widget.h"
#include<QTimer>
#include<QDebug>
#include<QPainter>
#include<QAction>
#include"register_type.h"
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

void Widget::addMapping(std::initializer_list<WidgetMappingInfo> list_)
{
    ui->menuList->disconnect();//先断开信号连接
    for(auto x_:list_){
        simMappingContainer.insert(x_.fd,x_);
        int index_=dataInputPane->addWidget(new QWidget);
        simMappingContainer[x_.fd].dataInputPaneIndex=index_;
        ui->menuList->addItem(x_.showName);//第一次也将触发currentIndexChanged信号
        simMappingContainer[x_.fd].menuListIndex=ui->menuList->count()-1;
    }
    //恢复信号连接
    connect(ui->menuList,QOverload<int>::of(&QComboBox::currentIndexChanged),[this](int x){
        timeLine->stop();
        changeSimulator(x);
    });
    currentSimMapping=(list_.begin())->fd;
    currentSimulator=Util::obj.GetObj(currentSimMapping);
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
    connect(globalSetting,&SettingPane::changeAnimationSpeed,[this](int x_){
        timeLine->setInterval(x_);
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

    // =fuc
    auto startAct=menu->addAction(tr("生成模拟数据"));
    connect(startAct,&QAction::triggered,[this](){
//        ui->rightContainerWidget->
        currentSimulator->clearActionData();
        ui->textBrowser->append(tr("清除已模拟的数据"));
        currentSimulator->produceActionData();
        ui->textBrowser->append(tr("[%1]模拟数据生成完成").arg(currentSimulator->getName()));
        //给模拟器更新画布pixmap
        auto size_=currentSimulator->calculationMinPixSize();
        ui->rightContainerWidget->changeCanvasSize(size_.width(),size_.height());
        ui->rightContainerWidget->setPixmapSource(currentSimulator);
        currentActionNumber=currentSimulator->actionNumber();
        currentActionIndex=0;
        simMappingContainer[currentSimMapping].stat=HasData;
    });

    auto restart_Act=menu->addAction(tr("重新放映"));
    connect(restart_Act,&QAction::triggered,[this](){
        currentActionIndex=0;
        currentSimulator->prepareReplay();
        ui->rightContainerWidget->initMesg(tr("请开始重新进行放映"));
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

    auto set_Act=menu->addAction(tr("配置设置"));
    connect(set_Act,&QAction::triggered,[this](bool){
        globalSetting->move(width()/2-globalSetting->width()/2,height()/2-globalSetting->height()/2);
        globalSetting->show();
    });
    auto data_InputAct=menu->addAction(tr("数据设定面板"));
    connect(data_InputAct,&QAction::triggered,[this](bool){
        dataInputPane->setCurrentIndex(ui->menuList->currentIndex());
        dataInputPane->show();
    });

    auto menu_sub1=menu->addMenu(tr("其他设置"));
    auto autop_Act=menu_sub1->addAction(tr("自动放映"));
    autop_Act->setCheckable(true);
    autop_Act->setChecked(true);
    mode=Automatic;
    connect(autop_Act,&QAction::triggered,[this](bool checked){
        if(!checked){
            mode=Manual;
            timeLine->stop();
            ui->textBrowser->append(tr("关闭自动放映:请使用 [ 和 ] 进行放映"));
        }else{
            mode=Automatic;
            ui->textBrowser->append(tr("自动放映开启:请使用鼠标左键开始/暂停"));
        }
    });

    //    ui->leftContainerWidget->hide();
    auto show_SideAct=menu_sub1->addAction(tr("显示侧栏"));
    show_SideAct->setCheckable(true);
    show_SideAct->setChecked(true);
    connect(show_SideAct,&QAction::triggered,[this](bool checked){
        if(checked){
            ui->leftContainerWidget->show();
        } else
            ui->leftContainerWidget->hide();
    });
    menu->addMenu(menu_sub1);
}

void Widget::prepare()
{
    timeLine=new QTimer(this);
    timeLine->setInterval(settings.animationInterval);
    connect(timeLine,&QTimer::timeout,[this](){
        if(currentSimulator->isOver()){
            timeLine->stop();
            ui->textBrowser->append(tr("放映完成"));
            return ;
        }
        currentSimulator->nextFrame();
        ui->rightContainerWidget->update();
    });


    connect(ui->menuList,QOverload<int>::of(&QComboBox::currentIndexChanged),[this](int x){
        timeLine->stop();
        ui->rightContainerWidget->switchS(x);
        currentSimulator=ui->rightContainerWidget->getS();
        changeSimulator(x);
    });

    throttleTimer=new QTimer(this);
    throttleTimer->setSingleShot(true);
    connect(throttleTimer,&QTimer::timeout,[this](){
        if(simMappingContainer[currentSimMapping].stat==Status::Unused)
            return ;
        auto size_=currentSimulator->calculationMinPixSize();
        ui->rightContainerWidget->changeCanvasSize(size_.width(),size_.height());
        ui->rightContainerWidget->setPixmapSource(currentSimulator);
        currentSimulator->currentSnapshot();
        ui->rightContainerWidget->update();
    });
    connect(this,&Widget::changeElementsSize,[this](int x_){
        currentSimulator->makeElementsBig(x_);
        throttleTimer->start(200);      //清除重置之前未完成的计时器，开始新计时
    });

    ui->horizontalSlider->setValue(settings.animationInterval);
}

void Widget::changeSimulator(int index_)
{
    //相应的控制面板变更
    dataInputPane->setCurrentIndex(index_);
    dataInputPane->resize(dataInputPane->currentWidget()->size());

//    ui->rightContainerWidget->setPixmapSource(currentSimulator);
    ui->rightContainerWidget->initMesg();
    ui->rightContainerWidget->update();

    setWindowTitle(currentSimulator->getName());
    showMsg();
}

void Widget::showMsg()
{
    auto cout=ui->textBrowser;
    cout->clear();
    cout->append(tr("当前模拟:[ %1 ]").arg(currentSimulator->getName()));
    if(mode==Automatic)
        cout->append(QString(tr("自动放映开启")));
}

void Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
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
    if(simMappingContainer[currentSimMapping].stat==Unused){
        ui->textBrowser->append(tr("请先模拟,产生绘图数据"));
        return ;
    }
    if(mode==Automatic){
        if(event->button()==Qt::LeftButton){
            timeLine->isActive()?timeLine->stop():timeLine->start();
            ui->textBrowser->append(timeLine->isActive()?tr("开始"):tr("暂停"));
            event->accept();
        }
    }
}

bool Widget::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object)
    if(event->type()==QEvent::KeyPress||event->type()==QEvent::KeyRelease){
        QCoreApplication::sendEvent(this,event);
        return true;
    }
    return false;
}

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event)
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
    timeLine->setInterval(value);
}
