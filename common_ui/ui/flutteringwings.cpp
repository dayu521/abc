#include "flutteringwings.h"
#include<QPainter>
#include<QPixmap>
#include"animation/abstract_animation.h"
#include"simulator.h"
#include"something.h"

FlutteringWings::FlutteringWings(QWidget *parent) : QWidget(parent),
    animationTimer(new QTimer)
{

//    pixContainer.append(std::make_shared<QPixmap>(this->width(),this->height()));
    pixContainer.append(std::make_shared<QPixmap>(Util::width,Util::height));
    pix=pixContainer[0].get();

    initMesgOnPix();
    for(int i=0;i<Util::numberOfobjFd;i++)
        mappingVec.push_back({{i},0});

    animationTimer->setInterval(200);
    connect(animationTimer,&QTimer::timeout,[this](){
        if(currentFp->isBlow()){
            animationTimer->stop();
            emit playCompleted();
            return ;
        }
        currentFp->nextNFrame();
        update();
    });

    throttleTimer=new QTimer(this);
    throttleTimer->setSingleShot(true);
    connect(throttleTimer,&QTimer::timeout,[this](){
        currentFp->changeElementSize(factor);    //必定成功
        changeCanvasSize(wantedWidth,wantedHeight);     //必定成功
        if(!animationTimer->isActive()&&currentFp->isRunning()){
            pix->fill();
            currentFp->currentSnapshot();
            update();
        }
        emit elementsSizeChanged(true);
    });
}

FlutteringWings::~FlutteringWings()
{

}

void FlutteringWings::addMapping(std::initializer_list<SimMapping> s)
{

}

//----<---current--->----
//    left        right
void FlutteringWings::changeCanvasSize(Util::__width_int w_,Util::__height_int h_, bool isForce_)
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
            if(pixContainer.size()>=Util::MAX_PIX_COUNTS)
                throw std::range_error("Exceeding the maximum number");
        }  catch (std::range_error & e) {
            Util::logExcept(e.what(),Util::MAX_PIX_COUNTS);
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

bool FlutteringWings::makeElementsBig(int factor)
{
    fuck=SizeError;
    auto [accept,w,h]=currentFp->acceptableScale(factor);
    if(!accept)
        return false;
    if(w>Util::MAX_WIDTH||h>Util::MAX_HEIGHT)
        return false;
    fuck=Ok;
    this->factor=factor;
    std::tie(wantedWidth,wantedHeight)={w,h};
    throttleTimer->start(200);      //清除重置之前未完成的计时器，开始新计时
    return true;
}

void FlutteringWings::initMesgOnPix(const QString & s)
{
    pix->fill(Qt::white);
    QPainter p(pix);
    auto font_=p.font();
    font_.setPixelSize(36);
    p.setFont(font_);
    p.drawText(50,50,s);
    p.drawText(50,100,"多使用鼠标右键上下文菜单");
}

void FlutteringWings::playAnimation()
{
    if(!animationTimer->isActive()&&fuck&Ok)
        animationTimer->start();
    emit canNotPlay();
}

void FlutteringWings::stopAnimation()
{
    if(animationTimer->isActive())
        animationTimer->stop();
}

void FlutteringWings::prepareReplayAnimation()
{
    currentFp->initModelData();
    initMesgOnPix();
}

void FlutteringWings::setInterval(int millisecond_)
{
    animationTimer->setInterval(millisecond_);
}

void FlutteringWings::setSim(int which_)
{
    stopAnimation();
    if(which_>Util::numberOfobjFd||which_<0)
        throw std::range_error("No such Simulator!");
    else if(currentSimIndex==which_)
        ;
    else{
        if(currentSimIndex>=0)
            saveStatus(currentSimIndex);
        applyStatus(which_);
        update();
    }
}

void FlutteringWings::preCheck()
{
    fuck=UnCheck;
    auto [w,h]=currentFp->getSize();
    if(w>Util::MAX_WIDTH||h>Util::MAX_HEIGHT){
            fuck|=SizeError;
    }

    if(fuck==UnCheck){
        changeCanvasSize(w,h);
        pix->fill();
        fuck=Ok;
    }else
        emit errorResult(fuck);
}

void FlutteringWings::saveStatus(int which_)
{
    mappingVec[which_].pixFd=currentPixIndex;
    currentFp=nullptr;
}

void FlutteringWings::applyStatus(int which_)
{
    //模拟器下标
    currentSimIndex=which_;
    //获取模拟器
    sim=Util::obj.GetObj(mappingVec[which_].fd);
    //模拟器pixmap的下标
    currentPixIndex=mappingVec[which_].pixFd;
    //模拟器对应pixmap
    pix=pixContainer[mappingVec[which_].pixFd].get();
    //模拟器的Fp
    currentFp=sim->getFP().get();
    //设置画布
    currentFp->setPix(pix);
    pix->fill();
    if(currentFp->isRunning())
        currentFp->currentSnapshot();
    else
        initMesgOnPix(tr("切换到 %1").arg(Util::name[which_]));
}

void FlutteringWings::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);
    p.drawPixmap(0,0,*pix);
}

