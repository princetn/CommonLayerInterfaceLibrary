/*
* This is a Polyline Class utility used to provide area calculation.
* Author: Amir Gasmi <argasmi@gmail.com>
* Date: 1/10/2022
*/
#ifndef __LAYER__
#define __LAYER__
#include <vector>
#include <iterator>
#include "Polyline.h"
#include "Property.h"

namespace CLI
{
	using namespace std;
	
	using namespace Utilities;

	template<typename T>
	class Layer
	{
	public:
		Layer(void);
		Layer(const Layer<T>& Other);
		const Layer<T>& operator= (const Layer<T>& Other);
		virtual ~Layer(void) {
			InnerPolys->clear();
			OuterPolys->clear();
		};

		Property<vector<Polyline<T>>> InnerPolys;
		Property<vector<Polyline<T>>> OuterPolys;
		Property<T> Z;
		Property<T> Thickness;
		Property<int> Index;

	private:
		

	};
	
	
}

#endif