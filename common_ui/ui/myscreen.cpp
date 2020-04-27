#include "myscreen.h"
#include<QPainter>
#include<QPixmap>

#include"simulator.h"
#include"something.h"
#include"rbtreesimulation.h"
//#include<loki/Factory.h>

FlutteringWings::FlutteringWings(QWidget *parent) : QWidget(parent)
{

    initMesg();
    pixContainer.append(std::make_shared<QPixmap>(this->width(),this->height()));
    registerSim<RBtreeSimulation>();
    for(auto iterator:objRegisters.keys()){
        creatorObject(iterator);
    }
}

FlutteringWings::~FlutteringWings()
{

}

//----<---current--->----
//    left        right
void FlutteringWings::changeCanvasSize(__width w_, __height h_)
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
        if(maxH_==0)
            maxH_=maxW_;
        if(maxW_==0)
            maxW_=maxH_;
        pixContainer.append(std::make_shared<QPixmap>(maxW_,maxH_));
    }
    currentPixIndex=cur_;
    pix=pixContainer[cur_].get();
    resize(pix->size());
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

void FlutteringWings::switchS(int witch_)
{
    if(witch_>vecSim.size()||witch_<0)
        throw std::range_error("no such Simulator!");
    else if(currentPixIndex==witch_)
        ;
    else{
        currentPixIndex=witch_;
        sim=vecSim[currentPixIndex].first;
        pix=pixContainer[vecSim[currentPixIndex].second].get();
    }
}

void FlutteringWings::creatorObject(int type_)
{
    if(!objRegisters.contains(type_))
        throw std::runtime_error("no such Obj");
    else if(objRegisters[type_].first)
        ;
    else{
        vecSim.append(std::make_pair((objRegisters[type_].second)(),0));
        objRegisters[type_].first=true;
    }
}

void FlutteringWings::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);
    p.drawPixmap(0,0,*pix);
}

