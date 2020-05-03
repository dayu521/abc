#ifndef REGIESTER_TYPE_H
#define REGIESTER_TYPE_H
#include"rbtree_sim.h"
#include"demosim.h"
#include"quicksortsim.h"
#include"convenience.h"

namespace Util {

    //注册模拟器Simulator的类型,类型标识是int,按照顺序从0开始
    //例如,以下例子中,0表示Rbtree,1表示DemoSim,2表示QuickSortSimulation...
    inline ObjManager<Simulator,Rbtree,DemoSim,QuickSortSimulation> obj;

    using AlreadyRegisterTypes=decltype (obj);
    template<typename T>
    inline const auto objFd=AlreadyRegisterTypes::FdOfType<T>;

    inline const int numberOfobjFd=AlreadyRegisterTypes::NumberOfType;

    struct ObjFD
    {
        const int fd{0};
    };

}

#endif // REGIESTER_TYPE_H
