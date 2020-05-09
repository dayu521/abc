#ifndef ABSTRACTDATASOURCE_H
#define ABSTRACTDATASOURCE_H
#include<vector>
#include<atomic>
#include<functional>
#include<unordered_map>
#include"something.h"

enum struct FAStatus:unsigned int{
    Uncertain,
    Ready,
    Running,
    GodJob,
//    Error
};

using Instruction=Util::InstructionTP<6>;
using Input=Util::Input;

class FarAway
{
public:
    explicit FarAway();

    FarAway(const FarAway &)=delete ;

    virtual ~FarAway()=0;

    virtual void doWork()=0;

    //method+datalength+data....
    //  1      1     N
    virtual bool setInput(std::vector<Input>)=0;

    virtual std::vector<Instruction> getOutput()=0;

    virtual FAStatus status()
    {
        return st;
    }
protected:
    using Method=std::function<void ()>;
    virtual void registerMethod(int methodKey_,Method m_);

protected:
    FAStatus st{FAStatus::Uncertain};
    std::vector<Input> input{};
    int index{0};
    std::vector<Instruction> output{};
    std::unordered_map<int,Method> ms{};
};

#endif // ABSTRACTDATASOURCE_H
