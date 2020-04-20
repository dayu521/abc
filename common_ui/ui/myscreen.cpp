#include "myscreen.h"
#include<QPainter>
#include<QPixmap>
#include<QtDebug>
#include"simulator.h"
#include"something.h"

MyScreen::MyScreen(QWidget *parent) : QWidget(parent)
{
    pixContainer.append(std::make_shared<QPixmap>(800,800));
    pixContainer.append(std::make_shared<QPixmap>(1600,1600));
    pix=pixContainer[currentPixIndex];
    initMesg();
    resize(pix->size());
}

MyScreen::~MyScreen()
{

}

void MyScreen::setPixmapSource(Simulator *x_)
{
    if(x_==nullptr){
        Util::logExcept("Simulator为空!");
        return ;
    }
    x_->setPixmap(pix);
}

//----<---current--->----
//    left        right
void MyScreen::changeCanvasSize(int w_, int h_)
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
    pix=pixContainer[cur_];
    resize(pix->size());
}

void MyScreen::initMesg(const QString & s)
{
    pix->fill(Qt::white);
    QPainter p(pix.get());
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

