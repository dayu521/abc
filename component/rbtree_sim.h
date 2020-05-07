#ifndef RBTREE_H
#define RBTREE_H
#include"simulator.h"
#include"datasource/far_away.h"
#include"freeboy.h"

#include<QObject>
#include<QThread>

class Rbtree : public QObject ,public Simulator
{
    Q_OBJECT
public:
    explicit Rbtree();
    virtual ~Rbtree();
    // Simulator interface
public:
    virtual void setInputData(const std::vector<int> &) override;
    virtual void produceModelData() override;
    virtual void clearModelData() override;
    virtual void prepareReplay() override;
signals:
    void start();
    void completed();
private:
    FreeBoy * fb{nullptr};
    QThread * thread{nullptr};
};

#endif // RBTREE_H
