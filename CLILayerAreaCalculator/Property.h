/*
*  Property utility to help tidy the implementation 
*  Author: Amir Gasmi <argasmi@gmail.com>
*  Date: 1/11/2022.
*/
#ifndef __PROPERTY__
#define __PROPERTY__


namespace Utilities
{
	template <typename T>
	class Property
	{
	public:
		virtual ~Property(void) = default;
		virtual T& operator= (const T& v) { return value = v; }
		virtual const T& operator() (void) const { return value; }
		virtual explicit operator const T& () const { return value; }
		virtual T* operator->() { return &value; }
		virtual const T* operator->() const { return &value; }

	protected:
		T value;


	};

	template<typename T>
	class ReadOnlyProperty
	{
	public:
		virtual ~ReadOnlyProperty(void) = default;
		virtual T& operator() (void) const { return value; }


	protected:
		T value;
	};

}

#endif
