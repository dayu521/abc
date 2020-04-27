#ifndef CSIMULATOR_H
#define CSIMULATOR_H

#include<memory>
#include"simulator.h"

class FarAway;
class FreezePainter;

class Csimulator :public Simulator
{

    // Simulator interface
public:
    virtual void produceModelData() override;
    virtual void clearModelData() override;
    virtual void prepareReplay() override;
    virtual int currentStatus() const override;
    virtual bool cancel() override;
    virtual bool isOver() const override;
    virtual void saveStatus() override;
    virtual void restore() override;
private:
    std::unique_ptr<FreezePainter> animation{};
    std::unique_ptr<FarAway> dataSource{};

};

#endif // CSIMULATOR_H
