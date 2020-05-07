#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include<stdexcept>
#include<array>

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

    struct Psize
    {
        int w{0};
        int h{0};
    };

    constexpr std::array<Psize,MAX_PIX_COUNTS> arr={Psize{1,2},{2,3},{5,3},{}};
}

#endif // MYEXCEPTION_H
