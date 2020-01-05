#include "myscreen.h"
#include<QPainter>
#include<QPixmap>
#include<QtDebug>
#include"simulator.h"

MyScreen::MyScreen(QWidget *parent) : QWidget(parent)
{
    pixContainer.append(new QPixmap{800,800});
    pixContainer.append(new QPixmap{1600,1600});
    pix=pixContainer[currentPixIndex];
    initMesg();
    resize(pix->size());
}

MyScreen::~MyScreen()
{
    qDeleteAll(pixContainer);
}

void MyScreen::setPixmapSource(Simulator *x_)
{
    x_->setPixmap(pix);
}

//----<---current--->----
//    left        right
void MyScreen::makeLager(int w_, int h_)
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
        pix=pixContainer[cur_+1];
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
        if(maxH_==0)
            maxH_=maxW_;
        if(maxW_==0)
            maxW_=maxH_;
        pixContainer.append(new QPixmap{maxW_,maxH_});
    }
    currentPixIndex=cur_;
    pix=pixContainer[cur_];
    resize(pix->size());
}

void MyScreen::initMesg(const QString s)
{
    pix->fill(Qt::white);
    QPainter p(pix);
    auto font_=p.font();
    font_.setPixelSize(36);
    p.setFont(font_);
    p.drawText(50,50,s);
    p.drawText(50,100,"多使用鼠标右键上下文菜单");
}

void MyScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);
    p.drawPixmap(0,0,*pix);
}

