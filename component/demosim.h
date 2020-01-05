#ifndef RBTREESIM_H
#define RBTREESIM_H
#include"simulator.h"

class DemoSim : public Simulator
{
public:
    DemoSim(QString name_="画正方形例子");
    ~DemoSim();
    // Simulator interface
public:
    virtual QWidget *getUi() override;
    virtual QString getName() const override;
    virtual void produceSimulateData() override;
    virtual void clearSimulateData() override;
    virtual void setPixmap(QPixmap *)  override;
    virtual void currentSnapshot(int n_) const override;
    virtual QSize calculationMinPixSize() override;
    virtual void nextFrame(int n_) override;
    virtual int frameAllNumber() const override;
    void prepareRepaintPixmap() override;
    virtual void makeElementsBig(int factor) override;
public slots:
    void setPixmapsize();
private:
    QWidget * panel;
    QString name;
    int _diameter =40;   //节点直径
    int _radius = _diameter / 2;    //半径
    int _nodeLineHeight = 3 * _diameter / 2;     //垂直距离
    int _fontSize=_radius;      //字体大小
    int k;
    int mm=100;
};
#endif // RBTREESIM_H
