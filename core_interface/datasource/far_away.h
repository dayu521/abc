#ifndef ABSTRACTDATASOURCE_H
#define ABSTRACTDATASOURCE_H
#include<vector>
#include<atomic>
#include<functional>
#include<unordered_map>

enum struct FAStatus:unsigned int{
    Uncertain,
    Ready,
    Running,
    GodJob,
//    Error
};

template <int N>
struct InstructionTP
{
    bool isPartOfOther{false};
    int action{-1};
    int data[N]{};
};

struct Input
{
    int method{-1};
    int dataLength{0};
    int * data{nullptr};
    ~Input(){ delete  data;}
};

using Instruction=InstructionTP<6>;

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
    std::vector<Instruction> oupt{};
    std::unordered_map<int,Method> ms{};
};

#endif // ABSTRACTDATASOURCE_H
