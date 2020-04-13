#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include<stdexcept>

namespace Util {
    class TooMuchException final: public std::range_error
    {
    public:
        explicit TooMuchException(const std::string info="数量过多"):std::range_error(info){}
    };
}

#endif // MYEXCEPTION_H
