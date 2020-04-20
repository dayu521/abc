#ifndef CSIMULATOR_H
#define CSIMULATOR_H

#include<memory>
#include"simulator.h"

template<typename Source>
class Csimulator :public Simulator
{
    // Simulator interface
public:
    virtual void makeElementsBig(int factor) override;
    virtual void produceActionData() override;
    virtual void clearActionData() override;
    virtual void prepareReplay() override;
    virtual const char *getName() const override;
    virtual void currentSnapshot() const override;
    virtual int actionNumber() const override;
    virtual void nextAction() override;
    virtual bool isOver() const override;
    virtual void nextFrame() override;
    virtual void animationStart() override;
    virtual std::tuple<int, int> calculationMinPixSize() override;
    virtual void saveStatus() override;
    virtual void restore() override;
};

#endif // CSIMULATOR_H
