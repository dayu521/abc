#ifndef RBTREE_H
#define RBTREE_H
#include"simulator.h"
#include"datasource/far_away.h"

class Rbtree :public Simulator
{
public:
    explicit Rbtree();
    virtual ~Rbtree();
    // Simulator interface
public:
    virtual void convertInput(const std::vector<int> &) override;
    virtual void prepareReplay() override;
};

#endif // RBTREE_H
