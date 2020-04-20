#ifndef LOKI_WRAP_H
#define LOKI_WRAP_H

#include<loki/Typelist.h>
#include<loki/NullType.h>

namespace Util {

    template <typename ...T>
    struct MakeTypelist{
        typedef Loki::NullType Result;
    };

    template <typename T,typename ...TT>
    struct MakeTypelist<T,TT...>{
        typedef Loki::Typelist<T,typename MakeTypelist<TT...>::Result> Result;
    };

}

#endif // LOKI_WRAP_H
