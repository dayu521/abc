#ifndef RBTREEMODEL_H
#define RBTREEMODEL_H
#include"animation/abstract_animation.h"

class RbtreeModel : public FreezePainter
{
public:
    explicit RbtreeModel();
    ~RbtreeModel();

    // FreezePainter interface
public:
    virtual void nextNFrame(int i) override;
    virtual void previousFrame(int i) override;
    virtual void currentSnapshot() const override;
    virtual void changeElementSize(int factor) override;
    virtual bool acceptableScale(int factor) override;
    virtual std::tuple<Util::__width_int,Util::__height_int> calculationMinPixSize() override;
    virtual bool isBlow() override;
    virtual void clearAllModelDatas() override;
    virtual void initModelData() override;

private:
    struct Elements
    {
        int diameter {40};   //节点直径
        int radius {diameter / 2};    //半径
        int nodeLineHeight {3 * diameter / 2};     //垂直距离
        int fontSize {radius};      //字体大小
    };

private:
    Elements ele{};

};

#endif // RBTREEMODEL_H
