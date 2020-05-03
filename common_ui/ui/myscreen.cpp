#include "myscreen.h"
#include<QPainter>
#include<QPixmap>
#include"animation/abstract_animation.h"
#include"simulator.h"
#include"something.h"
#include"rbtreesimulation.h"

FlutteringWings::FlutteringWings(QWidget *parent) : QWidget(parent),
    animationTimer(new QTimer)
{
    initMesg();
    pixContainer.append(std::make_shared<QPixmap>(this->width(),this->height()));
    pixContainer.append(std::make_shared<QPixmap>(Util::width,Util::height));
    pix=pixContainer[0].get();

    animationTimer->setInterval(500);
    connect(animationTimer,&QTimer::timeout,[this](){
        sim->getFP()->nextNFrame();
        update();
    });

    connect(this,&FlutteringWings::hasNoModelData,[this](){
        sim->produceModelData();
    });
}

FlutteringWings::~FlutteringWings()
{

}

//----<---current--->----
//    left        right
void FlutteringWings::changeCanvasSize(__width w_, __height h_, bool isForce_)
{
    auto maxW_=w_;
    auto maxH_=h_;
    auto cur_=currentPixIndex;

    //测试是否变小方向
    while (cur_>=0) {
        if(maxW_<=pixContainer[cur_]->width()&&maxH_<=pixContainer[cur_]->height()){
            cur_--;
        }else{
            break;
        }
    }
    if(cur_<currentPixIndex){
        currentPixIndex=cur_+1;
        pix=pixContainer[cur_+1].get();
        resize(pix->size());
        return ;
    }
    //否则为变大方向
    while (cur_<pixContainer.size()) {
        if(maxW_<=pixContainer[cur_]->width()&&maxH_<=pixContainer[cur_]->height())
            break ;
        else
            cur_++ ;
    }
    if(cur_>=pixContainer.size()){
        try {
            if(pixContainer.size()>=MAXCOUNTS)
                throw Util::TooMuchException();
        }  catch (Util::TooMuchException &) {
            Util::logExcept("pix数量超过预定义,");
            return ;
        }
        if(!isForce_){
            maxW_=pix->size().width()*2;
            maxH_=pix->size().height()*2;
        }else if(maxH_==0)//不会全为0,因为被第一个while循环过滤掉了
            maxH_=maxW_;
        else if(maxW_==0)
            maxW_=maxH_;

        pixContainer.append(std::make_shared<QPixmap>(maxW_,maxH_));
    }
    currentPixIndex=cur_;
    pix=pixContainer[cur_].get();
    resize(pix->size());
}

void FlutteringWings::makeElementsBig(int factor)
{
    sim->getFP()->changeElementSize(factor);
    if(!animationTimer->isActive()){
        sim->getFP()->currentSnapshot();
        update();
    }
}

void FlutteringWings::initMesg(const QString & s)
{
    pix->fill(Qt::white);
    QPainter p(pix);
    auto font_=p.font();
    font_.setPixelSize(36);
    p.setFont(font_);
    p.drawText(50,50,s);
    p.drawText(50,100,"多使用鼠标右键上下文菜单");
}

bool FlutteringWings::playAnimation()
{
    if(sim->currentStatus()!=Simulator::Status::HasModelData){
        emit hasNoModelData();
        return false;
    }
    if(!animationTimer->isActive())
        animationTimer->start();
    return true;
}

void FlutteringWings::stopAnimation()
{
    if(animationTimer->isActive())
        animationTimer->stop();
}

void FlutteringWings::setInterval(int millisecond_)
{
    animationTimer->setInterval(millisecond_);
}

void FlutteringWings::switchS(int which_)
{
    if(which_>Util::numberOfobjFd||which_<0)
        throw std::range_error("No such Simulator!");
    else if(currentSimIndex==which_)
        ;
    else{
        saveStatus(currentSimIndex);
        currentSimIndex=which_;
        sim=Util::obj.GetObj(currentSimIndex);
        pix=pixContainer[vecSim[currentSimIndex].pixFd].get();
        restore(currentSimIndex);
    }
}

void FlutteringWings::saveStatus(int which_)
{
    vecSim[which_].pixFd=currentPixIndex;
}

void FlutteringWings::restore(int which_)
{
    currentPixIndex=vecSim[which_].pixFd;
}

void FlutteringWings::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);
    p.drawPixmap(0,0,*pix);
}

