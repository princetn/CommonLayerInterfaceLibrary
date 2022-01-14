/*
* This is a Polyline Class used to provide a polyline utility.
* Author: Amir Gasmi <argasmi@gmail.com>
* Date: 1/10/2022
*/

#ifndef __POLYLINE__
#define __POLYLINE__

#include <vector>
#include <iterator>
#include "Point.h"
#include <stdexcept>

namespace CLI
{
	using namespace std;


	template<typename T>
	class Polyline
	{
	public:
		Polyline(void);
		Polyline(const Polyline<T>& Other);
		Polyline<T>& operator= (const Polyline<T>& Other);
		
		virtual ~Polyline(void) 
		{
			Points->clear();
		};

		virtual T getArea(void) const;
		 
		Property<vector<Point<T>>> Points;
		Property<unsigned int> Id;
		
	private:
		
	};
	template<typename T>
	Polyline<T>::Polyline(void)
	{
	}
	template<typename T>
	Polyline<T>::Polyline(const Polyline<T>& Other)
	{
		Points = Other.Points();
		Id = Other.Id();
	}
	template<typename T>
	inline Polyline<T>& Polyline<T>::operator=(const Polyline<T>& Other)
	{
		Points = Other.Points();
		Id = Other.Id();
		return *this;
	}
	template<typename T>
	T Polyline<T>::getArea(void) const
	{ // formula is obtained from url: https://en.wikipedia.org/wiki/Shoelace_formula

		T result = (T) 0;
		if (Points->size() < 3)
			throw exception("Please initialize Polyline with a list of points first!");

		for (int i = 0; i < Points->size() -1; i++ )
		{
			auto Pt_i = Points()[i];
			auto Pt_i_1 = Points()[i + 1];
			result += Pt_i.X() * Pt_i_1.Y() - Pt_i_1.X() * Pt_i.Y();
		}
		auto Pt_n = Points->back();
		auto Pt_1 = Points->front();

		result += Pt_n.X() * Pt_1.Y() - Pt_1.X() * Pt_n.Y();
		result = (T)0.5 * abs(result);

		return result;
	}
}

#endif