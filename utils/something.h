#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include<stdexcept>
#include<array>
#include<iostream>

namespace Util {

    template<typename ...T>
    void logExcept(const T & ...){};

    using __width_int=int;
    using __height_int=int;
    using __factor_int=int;

    inline const int width=800;
    inline const int height=600;

    inline const int MAX_WIDTH=8000;
    inline const int MAX_HEIGHT=5000;

    constexpr unsigned short MAX_PIX_COUNTS=4;

    constexpr __factor_int factor=5;

    template <int N>
    struct InstructionTP
    {
        int action{-1};
        int data[N]{};
        bool isPartOfOther{false};
    };

    struct Input
    {
        int method{-1};
        int dataLength{0};
        int * data{nullptr};
        Input(int method_,int datal_=0):method(method_),dataLength(datal_),data(new int[datal_]){}
    };

    template <typename InputIterator>
    inline void clearAllInput(InputIterator begin_,InputIterator end_)
    {
        for(;begin_!=end_;begin_++)
            delete [] (*begin_).data;
    }

    struct Psize
    {
        int w{0};
        int h{0};
    };

    constexpr std::array<Psize,MAX_PIX_COUNTS> arr={Psize{1,2},{2,3},{5,3},{}};
}

#endif // MYEXCEPTION_H
