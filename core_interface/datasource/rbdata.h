#ifndef RBDATA_H
#define RBDATA_H
#include"wrap_far_away.h"

class RbData : public WrapFarAway
{
public:
    RbData();
    ~RbData();
    enum struct MethodA:int{AddOne=0,AddMuch,RemoveOne};
private:

};

#endif // RBDATA_H
