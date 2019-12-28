#ifndef SIMULATOR_H
#define SIMULATOR_H
#include<QObject>
class QPixmap;
class QWidget;
/*
 * 我们必须对每个步骤都了如指掌,有点类似于牛顿经典力学中的愿望,知道了一个物体的位置和动量,就可以预测其未来.
 * 这个类本质上是事先运行一遍对特定输入的算法,然后把算法中每一个步骤记录成数据,粒度由实现者自定义.
 * 于是特定输入的任意算法就可统一形成新的步骤组成的序列.
 * 于是我们要还原算法的步骤,就可以放心从开头序列一直执行完毕,最终形成原始算法的整个模拟过程,当然,取决于每一步的粒度.
 */
class Simulator : public QObject
{
    Q_OBJECT
public:
    Simulator(QVector<int> * properties_=nullptr);
    Simulator(const Simulator &)=delete;
    //使每个组成图片的基本图形变大
    void virtual makeElementsBig(int factor);
    //处理模拟,生成绘图数据.所有数据都要从此函数生成,每次模拟只调用一次
    virtual void produceSimulateData()=0;
    //清除上次模拟数据和产生的变化,还原成初始状态
    virtual void clearSimulateData()=0;
    //一般用于返回给显示控件绘图所使用的pixmap
    virtual QPixmap * getPixmap()const=0;
    //返回使用的设置控件
    virtual QWidget * getUi()=0;
    //显示的条目名
    virtual QString getName()const=0;
    virtual void setPmpSize()const=0;
    //获取当前帧快照.例如,更改大小后需要重绘
    virtual void currentSnapshot(int n_)const=0;
    //当前模拟状态
    virtual int currentIndex()const=0;
    //生成每一个连续帧
    virtual void nextFrame(int n_)=0;
    //返回当前可容纳所有内容的最小大小.例如,显示控件大小必须至少等于此大小
    virtual QSize calculationMinPixSize()=0;
signals:
    void pixmapSizeChanged(int w_,int h_);
    void simulationFinished();
private:
protected:
    //所有元素的属性.用于修改从而增大或减少元素的大小
    QVector<int> * properties;
};

#endif // SIMULATOR_H
