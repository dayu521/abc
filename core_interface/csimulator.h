#ifndef CSIMULATOR_H
#define CSIMULATOR_H

#include<memory>
#include"simulator.h"

class Csimulator : public Simulator
{  
    // Simulator interface
public:
    explicit Csimulator(std::shared_ptr<FreezePainter> fp_, std::shared_ptr<FarAway> fa_);

    virtual void produceModelData() override;
    virtual void clearModelData() override;
    virtual void prepareReplay() override;
    virtual bool cancel() override;
    virtual void setInputData(const std::vector<int> &) override;
};

#endif // CSIMULATOR_H
