#ifndef ABSTRACTDATASOURCE_H
#define ABSTRACTDATASOURCE_H
#include<vector>

enum struct Status:unsigned int{
    Uncertain,
    Ready,
    Running,
    GodJob,
    Canceled,
    Error
};

class FarAway
{
public:
    explicit FarAway();

    FarAway(const FarAway &)=delete ;

    virtual ~FarAway();

    virtual void init(const std::vector<int>&)=0;

    virtual bool commitTask()=0;

    virtual void doWork()=0;

    //method+data
    virtual void Input(const std::vector<int>&)=0;

    virtual std::vector<int> & Output()=0;

    virtual Status status()const=0;

    bool cancel()
    {
        bool old=wantCancel;
        wantCancel=!wantCancel;
        return old;
    }

protected:

    bool wantCancel{false};

    Status st{Status::Uncertain};

};

#endif // ABSTRACTDATASOURCE_H
