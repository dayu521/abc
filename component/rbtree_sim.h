#ifndef RBTREE_H
#define RBTREE_H
#include"simulator.h"

class Rbtree : public Simulator
{
public:
    explicit Rbtree();
    virtual ~Rbtree();
    // Simulator interface
public:
    virtual void setInputData(int *data, int size) override;
    virtual void produceModelData() override;
    virtual void clearModelData() override;
    virtual void prepareReplay() override;
    virtual bool cancel() override;

};

#endif // RBTREE_H
