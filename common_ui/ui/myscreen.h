#ifndef MYSCREEN_H
#define MYSCREEN_H
#include<QWidget>
#include<QTimer>
#include<memory>
#include"register_type.h"

class Simulator;
namespace {
    constexpr unsigned short MAXCOUNTS=8;
}

struct SimMapping :Util::ObjFD
{
    int pixFd{0};
};

class FlutteringWings : public QWidget
{
    Q_OBJECT
public:
    explicit FlutteringWings(QWidget *parent = nullptr);
    ~FlutteringWings() override;

    using __width=int;
    using __height=int;

    void changeCanvasSize(__width w_,__height h_,bool isForce_=false);

    void makeElementsBig(int factor);

    void initMesg(const QString & s="请先进行数据模拟,生成绘图数据");

    //返回当前可容纳所有内容的最小大小.例如,显示控件大小必定至少等于此大小(width,height)
    virtual std::tuple<__width,__height> calculationMinPixSize()=0;

    //播放动画
    virtual bool playAnimation();

    //停止动画
    virtual void stopAnimation();

    //设置动画间隔
    void setInterval(int millisecond_);

    //切换模拟器
    void switchS( int which_);

    //保存状态
    void saveStatus(int which_);

    //恢复
    void restore(int which_);

signals:
    void hasNoModelData();
public slots :
    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    int currentPixIndex{0};
    QPixmap * pix{};
    QVector<std::shared_ptr<QPixmap>> pixContainer{};

    int currentSimIndex{0};
    std::shared_ptr<Simulator> sim{};

    SimMapping vecSim[Util::numberOfobjFd]{};

    QTimer * animationTimer{};
};


#endif // MYSCREEN_H
