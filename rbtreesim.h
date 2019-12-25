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
    virtual QPixmap *getPixmap() const override;
    virtual void setPmpSize() const override;
    virtual void currentSnapshot() const override;
    virtual QSize calculationPixSize() override;
    virtual void nextFrame() const override;
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
    QVector<int> elementProperties;
    static const int pixCount=3;
    QPixmap * pix[pixCount];
    int pixSize[pixCount]{1000,2000,4000};
    int currentPixIndex=0;
    int k;
};
#endif // RBTREESIM_H
