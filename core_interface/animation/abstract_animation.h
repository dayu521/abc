#ifndef ABSTRACTANIMATION_H
#define ABSTRACTANIMATION_H
#include"something.h"
#include<vector>

using Instruction=Util::InstructionTP<6>;
class QPixmap;

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

    virtual std::tuple<typename Util::__width_int,typename Util::__height_int> getSize()=0;

    //返回此缩放是否接受,如果接受,接收后需要的width和height
    virtual std::tuple<bool,typename Util::__width_int,typename Util::__height_int> acceptableScale(int factor)=0;

    void setInput(std::vector<Instruction> v)
    {
        instructions=std::move(v);
        current=0;
        all=instructions.size();
    }

    virtual void pullInform(const std::vector<Util::Input> &info_)=0;

    void setPix(QPixmap * p)
    {
        pix=p;
    }

    bool isRunning()
    {
        return current>0;
    }

protected:
    int current{0};
    int all{0};
    std::vector<Instruction> instructions{};
    QPixmap * pix{};
};

#endif // ABSTRACTANIMATION_H
