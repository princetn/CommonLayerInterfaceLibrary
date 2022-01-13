/*
* This is a the header data structure corresponding to Common Layer Interface files.
* Author: Amir Gasmi <argasmi@gmail.com>
* Date: 1/12/2022
*/

#ifndef __HEADER__
#define __HEADER__
#include "Property.h"
#include <string>
#include <vector>

namespace CLI
{
	using namespace Utilities;
	using namespace std;

	template<typename T>
	class Header
	{
	public:
		typedef enum { ASCII, BINARY }FTYPE;
		typedef enum { BIG, LITTLE }ENDIAN;
		Header(void) = default;
		Header(const Header<T>& Other);
		const Header<T>& operator= (const Header<T>& Other);
		virtual ~Header(void);

		Property<FTYPE> Ftype;
		Property<T> Units;
		Property<unsigned int> Version;
		Property<pair<unsigned int,string>> Label;
		Property<unsigned int> Date;
		Property<vector<T>> Dimension;
		Property<unsigned int> Layers;
		Property<bool> Align;


		




	private:

	protected:

	};
	template<typename T>
	Header<T>::Header(const Header<T>& Other)
	{
		Ftype = Other.Ftype();
		Units = Other.Units();
		Version = Other.Version();
		Label = Other.Label();
		Date = Other.Date();
		Dimension = Other.Dimension();
		Layers = Other.Layers;
		Align = Other.Align;
	}
	template<typename T>
	const Header<T>& Header<T>::operator=(const Header<T>& Other)
	{
		Ftype = Other.Ftype();
		Units = Other.Units();
		Version = Other.Version();
		Label = Other.Label();
		Date = Other.Date();
		Dimension = Other.Dimension();
		Layers = Other.Layers;
		Align = Other.Align;

		return *this;
	}
	template<typename T>
	Header<T>::~Header(void)
	{
		Dimension->clear();
	}
}

#endif
