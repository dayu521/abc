#ifndef QUICKSORTSIM_H
#define QUICKSORTSIM_H
#include"simulator.h"

//数据结构与算法分析c++描述第三版
class QuicksortSimulation:public Simulator
{
public:
    QuicksortSimulation();
    void quickSort(QVector<int> & v){quickSort(v,0,v.size()-1);}
    // Simulator interface
public:
    virtual void makeElementsBig(int factor) override;
    virtual void produceSimulateData() override;
    virtual void clearSimulateData() override;
    virtual void prepareRepaintPixmap() override;
    virtual QString getName() const override;
    virtual void currentSnapshot(int n_) const override;
    virtual int frameAllNumber() const override;
    virtual void nextFrame(int n_) override;
    virtual QSize calculationMinPixSize() override;
private:
    int width;  //元素宽度
    int dHeight;    //单位高度.元素高度=单位高度*数值大小
    QVector<int> data;
    QVector<int> elementContainer;
    enum Action{
        Swap,
        ToRight,
        ToLeft,
        DrawLine,
        ChangeColor
    };

private:
    void quickSort(QVector<int>& vec_,int left_,int right_);
    int median3(QVector<int> & vec_,int left_,int right);
};

#endif // QUICKSORTSIM_H
