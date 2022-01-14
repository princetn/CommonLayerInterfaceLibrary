/*
*  Format utility to help double/float precision
*  Author: Amir Gasmi <argasmi@gmail.com>
*  Date: 1/13/2022.
*/

#ifndef __FORMAT__
#define __FORMAT__
#include <sstream>
#include <iomanip>
#include <string>

namespace Formatter
{
    template<typename T>
    class Format
    {
    public:
        Format(unsigned int digits = 6);
        ~Format();
        std::string operator() (T v);


    private:
        unsigned int _digits;

    };


}


template<typename T>
Formatter::Format<T>::Format(unsigned int digits)
    :_digits(digits)
{
}
template<typename T>
Formatter::Format<T>::~Format()
{
}
template<typename T>
std::string Formatter::Format<T>::operator()(T v)
{
    std::ostringstream ss;
    //ss.setf(std::ios::fixed, std::ios::floatfield);
    
    ss << std::fixed;
    ss << std::setprecision(_digits);
    
    ss << v;


    return ss.str();
}

#endif