#ifndef CONVENIENCE_H
#define CONVENIENCE_H
#include<tuple>
#include<functional>

namespace Util {

    template<int n,typename T1,typename ...T>
    struct FuckAll :FuckAll<n-1,T1,T1,T...>
    {};

    template<typename T1, typename ...T>
    struct FuckAll<0,T1,T...>
    {
        typedef  std::tuple<T...> Fa;
    };

    /*
     *对std::tuple的简单包装.
     *当存储多个相同类型的tuple时需要写多个类型参数,例如存储3个int类型
     *   std::tuple<int,int,int> a;
     *于是可以写作
     *   TupleForArray<int,3> a;
     */
    template <typename T,int n>
    using TupleForArray=typename FuckAll<n,T>::Fa;

    template <typename ...T>
    std::tuple<T...> __putArray(T...arr)
    {
        return std::make_tuple(arr...);
    }

//    template <typename T1, typename ...T>
//    std::tuple<T...> putArray(T1 & arr,T... args,int n)
//    {
//        if(n==0)
//            return _putArray(args...);
//        using EleType=decltype (arr[n]);
//        putArray<T1,EleType,T...>(arr[n],args...,n-1);
//    }
    template <typename T1, typename ...T>
    std::tuple<T...> _putArray(T1 & arr,int n,T &... args)
    {
        if(n==0)
            return __putArray(args...);
        return _putArray<T1,T...>(arr,n-1,arr[n],args...);
    }

    template <typename T>
    decltype (auto) make_TupleForArray(T * arr,int n)
    {
        return _putArray(arr,n);
    }

//    template<typename T>
//    using make_TupleForArray=std::function<decltype (putArray<T>)>;
//    typedef make_TupleForArray ;

}

#endif // CONVENIENCE_H
