/*
* This is a Layer Class utility used to provide area calculation.
* Author: Amir Gasmi <argasmi@gmail.com>
* Date: 1/10/2022
*/

#ifndef __LAYER__
#define __LAYER__
#include <vector>
#include <iterator>
#include "Polyline.h"
#include "Property.h"
#include "Format.h"


namespace CLI
{
	using namespace std;
	
	using namespace Utilities;

	template<typename T>
	class Layer
	{ // TODO: Will need to add some checking logic for Contour polylines not to intersect.
	public:
		Layer(void) = default;
		Layer(const Layer<T>& Other);
		const Layer<T>& operator= (const Layer<T>& Other);
		virtual ~Layer(void) {
			InnerContours->clear();
			OuterContours->clear();
			Hatches->clear();
		};
		T getLayerArea(void) const;
		template<typename U>
		friend std::ostream& operator<< (std::ostream& out, const Layer<U>& Other);

		Property<vector<Polyline<T>>> InnerContours;
		Property<vector<Polyline<T>>> OuterContours;
		Property<vector<Polyline<T>>> Hatches;
		Property<T> Z;
		Property<T> Thickness;
		Property<int> Index;

	private:
		

	};
	
	
	template<typename T>
	Layer<T>::Layer(const Layer<T>& Other)
	{
		this->Hatches = Other.Hatches();
		this->Index = Other.Index();
		this->InnerContours = Other.InnerContours();
		this->OuterContours = Other.OuterContours();
		this->Thickness = Other.Thickness();
		this->Z = Other.Z();
	}

	template<typename T>
	const Layer<T>& Layer<T>::operator=(const Layer<T>& Other)
	{
		this->Hatches = Other.Hatches();
		this->Index = Other.Index();
		this->InnerContours = Other.InnerContours();
		this->OuterContours = Other.OuterContours();
		this->Thickness = Other.Thickness();
		this->Z = Other.Z();

		return *this;
	}

	template<typename T>
	T Layer<T>::getLayerArea(void) const
	{
		T result = (T) 0;
		//result += OuterContour->getArea();
		for (auto it = OuterContours->cbegin(); it != OuterContours().cend(); it++)
		{
			result += it->getArea();
		}
		for (auto it = InnerContours->cbegin(); it != InnerContours->cend(); it++)
		{
			result -= it->getArea();
		}

		return result;
	}

	template<typename U>
	std::ostream& operator<<(std::ostream& out, const Layer<U>& Other)
	{
		Formatter::Format<float> f(3);
		out << "Layer index:";
		out.width(5);
		out << std::right << Other.Index() << ", Layer height:";
		out.width(8);
		out << std::right << f(Other.Z()) << ", Layer part area:";
		out.width(11);
		out << std::right << f(Other.getLayerArea());

		return out;
	}

}

#endif