#ifndef SIMULATOR_H
#define SIMULATOR_H
#include<QObject>
class QPixmap;

class Simulator : public QObject
{
    Q_OBJECT
public:
    Simulator();
    void startSimulate();
    QPixmap simulation();
signals:
//    void paintFinished(QPixmap p_);
    void simulationFinished();
private:

};

#endif // SIMULATOR_H
