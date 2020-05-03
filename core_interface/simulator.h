#ifndef SIMULATOR_H
#define SIMULATOR_H
#include<memory>
#include<vector>

class FarAway;
class FreezePainter;

/*
 * 我们必须对每个步骤都了如指掌,有点类似于牛顿经典力学中的愿望,知道了一个物体的位置和动量,就可以预测其未来.
 * 这个类本质上是事先运行一遍对特定输入的算法,然后把算法中每一个步骤(action)记录成数据,粒度由实现者自定义.
 * 于是特定输入的任意算法就可统一形成新的步骤组成的序列.
 * 于是我们要还原算法的步骤,就可以放心从开头序列一直执行完毕,最终形成原始算法的整个模拟过程,当然,取决于每一步的粒度.
 */
class Simulator
{
public:
    enum Status{Empty,UnCertain,HasModelData};
public:
    explicit Simulator(std::shared_ptr<FreezePainter> fp_, std::shared_ptr<FarAway> fa_);

    Simulator(const Simulator &)=delete;

    virtual ~Simulator();
    //设置输入
    virtual void setInputData(const std::vector<int> &)=0;

    //生成模拟数据
    virtual void produceModelData()=0;

    //清除模拟数据
    virtual void clearModelData()=0;

    //准备重新放映
    virtual void prepareReplay()=0;

    //当前模拟的状态
    Status currentStatus()const
    {
        return st;
    }

    //打断数据生成
    virtual bool cancel();

    std::shared_ptr<FreezePainter> getFP()const
    {
        return animation;
    }

protected:
    std::shared_ptr<FreezePainter> animation{};
    std::shared_ptr<FarAway> dataSource{};
    Status st{Empty};
};

#endif // SIMULATOR_H
