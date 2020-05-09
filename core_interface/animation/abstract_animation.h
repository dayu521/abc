#ifndef ABSTRACTANIMATION_H
#define ABSTRACTANIMATION_H
#include"something.h"
#include<vector>
using Instruction=Util::InstructionTP<6>;

class FreezePainter
{
public:
    explicit FreezePainter(){}
    virtual ~FreezePainter(){}

    //动画的下N帧
    virtual void nextNFrame(int i=0)=0;

    //上N帧
    virtual void previousFrame(int i=0)=0;

    //获取当前动画的快照.例如,更改大小后需要重绘
    virtual void currentSnapshot()const=0;

    //是否播放完成
    virtual bool isBlow()=0;

    //清除模型数据
    virtual void clearAllModelDatas()=0;

    //准备模型数据
    virtual void initModelData()=0;

    //改变元素大小
    virtual void changeElementSize(int factor)=0;

    virtual bool acceptableScale(int factor)=0;

    //返回当前可容纳所有内容的最小大小.例如,显示控件大小必定至少等于此大小(width,height)
    virtual std::tuple<Util::__width_int,Util::__height_int> calculationMinPixSize()=0;

    void setInput(std::vector<Instruction> v)
    {
        instructions=std::move(v);
    }

protected:
    int current{0};
    int all{0};
    std::vector<Instruction> instructions{};
};

#endif // ABSTRACTANIMATION_H
