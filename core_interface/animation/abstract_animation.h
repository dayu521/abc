#ifndef ABSTRACTANIMATION_H
#define ABSTRACTANIMATION_H

class FreezePainter
{
public:
    explicit FreezePainter();
    virtual ~FreezePainter();

    //动画的下N帧
    virtual void nextNFrame(int i=0)=0;

    //上N帧
    virtual void previousFrame(int i=0)=0;

    //获取当前动画的快照.例如,更改大小后需要重绘
    virtual void currentSnapshot()const=0;

    //改变元素大小
    virtual void changeElementSize(int factor)=0;

};

#endif // ABSTRACTANIMATION_H
