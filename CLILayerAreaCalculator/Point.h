/*
* This is a Point Class.
* Author: Amir Gasmi <argasmi@gmail.com>
* Date: 1/10/2022
*/

#ifndef __POINT__
#define __POINT__
#include "Property.h"
#include <iostream>
#include "Format.h"

namespace CLI
{
	using namespace Utilities;

	template <typename T>
	class Point
	{
	public:
		Point(void);
		Point(T x, T y);
		Point(const Point<T>& Other);
		Point<T>& operator=(const Point<T>& Other);
		Property<T> X;
		Property<T> Y;
		Property<int> Id;

		template<typename U>
		friend std::ostream& operator<< (std::ostream& out, const Point<U>& Other);
	

		virtual ~Point(void);
	private:
		

	};
	template<typename U>
	std::ostream& operator<<(std::ostream& out, const Point<U>& Other)
	{
		Formatter::Format<U> f(3);
		out << "Point: "<<Other.Id()<<" =(" << f(Other.X()) << ", " << f(Other.Y()) << ")";
		return out;
	}
}


template<typename T>
CLI::Point<T>::Point(void)
{
	X = 0;
	Y = 0;
}
template<typename T>
CLI::Point<T>::Point(T x, T y)
	:X(x), Y(y)
{
	
}

template<typename T>
CLI::Point<T>::Point(const Point<T>& Other)
{
	X = Other.X();
	Y = Other.Y();
	Id = Other.Id();
}

template<typename T>
CLI::Point<T>& CLI::Point<T>::operator=(const Point<T>& Other)
{
	
	X = Other.X();
	Y = Other.Y();
	Id = Other.Id();
	return *this;
}



template<typename T>
CLI::Point<T>::~Point(void)
{// cleanup code.
}

#endif