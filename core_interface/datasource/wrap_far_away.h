
#ifndef RBTREEDATASOURCE_H
#define RBTREEDATASOURCE_H

#include"far_away.h"
#include<memory>
//#include<QThread>
#include<QMutex>
#include<QCoreApplication>

class WrapFarAway : public FarAway
{
public:
    explicit WrapFarAway();

//    static std::shared_ptr<QThread> getThread()
//    {
//        static auto thread=std::make_shared<QThread>();
//        return thread;
//    }

    // FarAway interface
public:
    virtual void doWork() override;
    virtual bool setInput(const std::vector<Input> &) override;
    virtual std::vector<Instruction> &getOutput() override;
    virtual Status status() override
    {
        QMutexLocker L{&stMutex};
        return FarAway::status();
    }
private:
    QMutex mutex{};
    QMutex stMutex{};
};

#endif // RBTREEDATASOURCE_H

