#ifndef RBTREESIM_H
#define RBTREESIM_H
#include"simulator.h"

class Widget;

class DemoSim : public Simulator
{
    Q_OBJECT
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
public slots:
    void setPixmapsize();
private:
    QWidget * panel;
    QString name;
    /*
     * 0=节点半径
     * 1=节点直径,半径*2
     * 2=行间距,半径*3/2
     * 3=字体大小
     */
    QVector<int> elementProperties{20,  //半径
                                   40,  //直径
                                   20*3/2,      //间距
                                   16    //字体大小
                                  };
    int k;
    int mm=100;
};
#endif // RBTREESIM_H
