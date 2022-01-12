/*
* This is a Parser utility used for parsing Common Layer Interface files.
* Author: Amir Gasmi <argasmi@gmail.com>
* Date: 1/11/2022
*/


#ifndef __GEOMETRY__
#define __GEOMETRY__
#include "Layer.h"
#include "Property.h"

namespace CLI
{
	using namespace Utilities;

	template <typename T>
	class Geometry
	{
	public:
		Geometry();
		Geometry(const Geometry& Other);
		Geometry<T>& operator =(const Geometry& Other);
		virtual ~Geometry()
		{
			Layers->clear();
		};

		Property<vector<Layer<T>>> Layers;



	private:

	protected:

	};
	template<typename T>
	Geometry<T>::Geometry()
	{
	}
	template<typename T>
	 Geometry<T>::Geometry(const Geometry& Other)
	{
		 Layers = Other.Layers();

		
	}
	template<typename T>
	Geometry<T>& Geometry<T>::operator=(const Geometry& Other)
	{
		// TODO: insert return statement here
		this->Layers = Other.Layers();


		return *this;
	}
}







#endif