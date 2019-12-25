#ifndef SIMULATOR_H
#define SIMULATOR_H
#include<QObject>
class QPixmap;
class QWidget;

class Simulator : public QObject
{
    Q_OBJECT
public:
    Simulator(QVector<int> * properties_=nullptr);
    Simulator(const Simulator &)=delete;
    void virtual makeElementsBig(int factor);
    virtual void startSimulate()=0;
    virtual void clearSimulate()=0;
    //一般用于返回给显示控件绘图所使用的pixmap
    virtual QPixmap * getPixmap()const=0;
    //Simulator各自特定的输入方式和控制的界面
    virtual QWidget * getUi()=0;
    //显示的条目名
    virtual QString getName()const=0;
    virtual void setPmpSize()const=0;
    //获取当前帧快照.例如,更改大小后需要重绘
    virtual void currentSnapshot()const=0;
    //生成每一帧
    virtual void nextFrame()const=0;
    //返回当前可容纳所有内容的最小大小.例如,显示控件大小必须至少等于此大小
    virtual QSize calculationPixSize()=0;
signals:
    void pixmapSizeChanged(int w_,int h_);
    void simulationFinished();
private:
protected:
    //所有元素的属性.用于修改从而增大或减少元素的大小
    QVector<int> * properties;
};

#endif // SIMULATOR_H
