#ifndef ABSTRACTDATASOURCE_H
#define ABSTRACTDATASOURCE_H
#include<vector>
#include<atomic>

enum struct Status:unsigned int{
    Uncertain,
    Ready,
    Running,
    GodJob,
    Canceled,
//    Error
};

struct Instruction
{
    bool isPartOfOther{false};
    int method{-1};
    int data[6]{};
};

class FarAway
{
public:
    explicit FarAway();

    FarAway(const FarAway &)=delete ;

    virtual ~FarAway();

    virtual void doWork()=0;

    //method+data
    virtual void initInput(const std::vector<int>&)=0;

    virtual std::vector<Instruction> & getOutput()=0;

    virtual Status status()const
    {
        return st;
    }

    virtual bool cancel()
    {
        bool old=wantCancel;
        wantCancel=!wantCancel;
        return old;
    }

protected:

    std::atomic<bool> wantCancel{false};

    Status st{Status::Uncertain};

};

#endif // ABSTRACTDATASOURCE_H
