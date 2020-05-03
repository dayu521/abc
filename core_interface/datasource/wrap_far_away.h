#ifndef RBTREEDATASOURCE_H
#define RBTREEDATASOURCE_H

#include"far_away.h"
#include<QObject>
#include<memory>
#include<QThread>

class WrapFarAway : public FarAway ,public QObject
{
    Q_OBJECT
public:
    explicit WrapFarAway(std::shared_ptr<FarAway> fa_);

    static std::shared_ptr<QThread> getThread()
    {
        static auto thread=std::make_shared<QThread>();
        return thread;
    }

public slots:
    void doWork_slot()
    {
        doWork();
        emit start_signal();
    }
signals:
    void start_signal();
    // FarAway interface
public:
    virtual void doWork() override{}
    virtual void initInput(const std::vector<int> &) override;
    virtual std::vector<Instruction> &getOutput() override;
    virtual Status status() const override
    {
        return rfa->status();
    }
private:
    std::shared_ptr<FarAway> rfa;
};

#endif // RBTREEDATASOURCE_H
