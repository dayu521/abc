#ifndef CONVENIENCE_H
#define CONVENIENCE_H
#include<tuple>

namespace Util {

    /******************************************************/

    template<int n,typename T1,typename ...T>
    struct FuckAll :FuckAll<n-1,T1,T1,T...>
    {};

    template<typename T1, typename ...T>
    struct FuckAll<0,T1,T...>
    {
        typedef  std::tuple<T...> Fa;
    };

    /*
     *简化函数返回值std::tuple声明.
     *当存储多个相同类型的tuple时需要写多个类型参数,例如存储3个int类型
     *   std::tuple<int,int,int> f();
     *于是可以替换写作为:
     *   TupleForArray<int,3> f();
     *有些情况下可以decltype(auto)
     */
    template <typename T,int n>
    using TupleWrapArray=typename FuckAll<n,T>::Fa;

    /*****************************************************/

    template <typename ...T>
    std::tuple<T...> __putArray(T...arr)
    {
        return std::make_tuple(arr...);
    }

    template <bool fuck,typename T1,typename T2>
    struct IfThenElse;

    template <typename T1,typename T2>
    struct IfThenElse<true,T1,T2>
    {
        typedef T1 Result;
    };
    template <typename T1,typename T2>
    struct IfThenElse<false,T1,T2>
    {
        typedef T2 Result;
    };

    struct S1{};
    struct S2{};

    template <int,typename ArrType,typename ...T>
    constexpr decltype (auto) __putArray(S2,ArrType,T &...arr)
    {
        return std::make_tuple(arr...);
    }

    template <int size,typename ArrType,typename ...T>
    constexpr decltype (auto) __putArray(S1,ArrType arr,T &... t)
    {
        typedef typename IfThenElse<size-1,S1,S2>::Result Fk;
        return __putArray<size-1,ArrType>(Fk(),arr,arr[size-1],t...);
    }

    /*
     * 简化构造数组时需要分别传递每个数组元素.
     * 当传递 int a[]={1,2,3,4,5} 中的5个元素给std::tuple时:
     *      std::make_tuple(a[0],a[1],a[2],a[3],a[4]);
     * 于是可替换为
     *      make_TupleForArray(a);
     */
    template <typename T,std::size_t N>
    constexpr decltype (auto) make_TupleForArray(T (&arr)[N])
    {
        return __putArray<N,T *>(S1(),static_cast<T *>(arr));
    }

}

#endif // CONVENIENCE_H
