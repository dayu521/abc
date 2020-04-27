#ifndef SIMULATOR_H
#define SIMULATOR_H
//#include<memory>
#include<tuple>
#include<type_traits>

//#include "abstract_data_source.h"
/*
 * 我们必须对每个步骤都了如指掌,有点类似于牛顿经典力学中的愿望,知道了一个物体的位置和动量,就可以预测其未来.
 * 这个类本质上是事先运行一遍对特定输入的算法,然后把算法中每一个步骤(action)记录成数据,粒度由实现者自定义.
 * 于是特定输入的任意算法就可统一形成新的步骤组成的序列.
 * 于是我们要还原算法的步骤,就可以放心从开头序列一直执行完毕,最终形成原始算法的整个模拟过程,当然,取决于每一步的粒度.
 */
class Simulator
{
public:
    explicit Simulator();

    Simulator(const Simulator &)=delete;

    virtual ~Simulator();

    //处理模拟,生成绘图数据.所有数据都要从此函数生成,每次模拟只调用一次
    virtual void produceModelData()=0;

    //清除模拟数据
    virtual void clearModelData()=0;

    //准备重新放映
    virtual void prepareReplay()=0;

    //当前模拟的状态
    virtual int currentStatus()const=0;

    //取消模拟
    virtual bool cancel()=0;

    //返回模拟是否结束
    virtual bool isOver()const=0;

    //保存状态
    virtual void saveStatus()=0;

    //恢复
    virtual void restore()=0;

};

#endif // SIMULATOR_H
