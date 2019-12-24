#ifndef RBTREESIM_H
#define RBTREESIM_H
#include"simulator.h"

class RBtreeSim : public Simulator
{
    Q_OBJECT
public:
    RBtreeSim(QString name_="红黑树");
    ~RBtreeSim();
    // Simulator interface
public:
    virtual QWidget *getUi() override;
    virtual QString getName() const override;
    virtual void startSimulate() override;
    virtual void clearSimulate() override;
    virtual QPixmap simulation() const override;
private:
    QWidget * panel;
    QString name;
};

#endif // RBTREESIM_H
