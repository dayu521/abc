#ifndef SIMULATOR_H
#define SIMULATOR_H
#include<QObject>
class QPixmap;
class QWidget;
/*
 * 我们必须对每个步骤都了如指掌,有点类似于牛顿经典力学中的愿望,知道了一个物体的位置和动量,就可以预测其未来.
 * 这个类本质上是事先运行一遍对特定输入的算法,然后把算法中每一个步骤(action)记录成数据,粒度由实现者自定义.
 * 于是特定输入的任意算法就可统一形成新的步骤组成的序列.
 * 于是我们要还原算法的步骤,就可以放心从开头序列一直执行完毕,最终形成原始算法的整个模拟过程,当然,取决于每一步的粒度.
 */
class Simulator
{
public:
    enum class AA{};
    struct Act
    {
        int xfrom;
        int yfrom;
        int dx;
    };
public:
    Simulator();
    Simulator(const Simulator &)=delete;
    virtual ~Simulator();
    //使每个组成图片的像素变多,从而变大元素,详见piece文件对变大的简单辨别.
    void virtual makeElementsBig(int factor)=0;

    //处理模拟,生成绘图数据.所有数据都要从此函数生成,每次模拟只调用一次
    virtual void produceActionData()=0;

    //清除模拟数据
    virtual void clearActionData()=0;

    //准备重新放映
    virtual void prepareReplay()=0;

    //返回使用的设置控件
    virtual QWidget * getUi();

    //显示的条目名
    virtual QString getName()const=0;

    virtual void setPixmap(QPixmap *);

    //获取当前action快照.例如,更改大小后需要重绘
    virtual void currentSnapshot()const=0;

    //当前模拟的action的总量
    virtual int actionNumber()const=0;

    //执行下一个连续的action
    virtual void nextAction()=0;

    //返回模拟是否结束
    virtual bool isOver()const{return currentAction>=currentActionNumber;}

    //是否有动画
    virtual bool hasAnimation()const;

    //动画的下一帧
    virtual void nextFrame();

    //开始某个动画,做一些准备.
    virtual void animationStart();

    //返回当前可容纳所有内容的最小大小.例如,显示控件大小必定至少等于此大小
    virtual QSize calculationMinPixSize()=0;

    //保存状态
    virtual void saveStatus();

    //恢复
    virtual void restore();
//signals:
//    void pixmapSizeChanged(int w_,int h_);
//    void simulationFinished();
private:

protected:
    QPixmap *pix;
    int currentAction=0;
    int currentActionNumber=0;
};

#endif // SIMULATOR_H
