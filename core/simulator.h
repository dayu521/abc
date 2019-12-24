#ifndef SIMULATOR_H
#define SIMULATOR_H
#include<QObject>
class QPixmap;
class QWidget;

class Simulator : public QObject
{
    Q_OBJECT
public:
    Simulator();
    virtual void startSimulate()=0;
    virtual void clearSimulate()=0;
    virtual QPixmap simulation()const=0;
    //自定义输入方式和控制的界面
    virtual QWidget * getUi()=0;
    //显示的条目名
    virtual QString getName()const=0;
signals:
//    void paintFinished(QPixmap p_);
    void simulationFinished();
private:

};

#endif // SIMULATOR_H
