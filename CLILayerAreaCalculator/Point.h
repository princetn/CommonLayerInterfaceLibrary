/*
* This is a Point Class.
* Author: Amir Gasmi <argasmi@gmail.com>
* Date: 1/10/2022
*/

#ifndef __POINT__
#define __POINT__
#include "Property.h"


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
	

		virtual ~Point(void);
	private:
		

	};
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