/*
* This is a Parser utility used for parsing Common Layer Interface (CLI)files.
*  CLI description is provided here: https://www.hmilch.net/downloads/cli_format.html
* Author: Amir Gasmi <argasmi@gmail.com>
* Date: 1/10/2022
*/

#ifndef __PARSER__
#define __PARSER__
#include <string>
#include <fstream>
#include "Geometry.h"

namespace CLI
{
	template <typename T>
	class Parser
	{
	public:
		typedef enum {ASCII, BINARY}FTYPE;
		typedef enum {BIG, LITTLE}ENDIAN;
		static void ReadHeader(ifstream data, int& position, FTYPE& ftype);
		static void ReadBodyASCII(ifstream data, const int& position);
		static void ReadBodyBinary(ifstream data, const int& position);
		static Geometry<T> ImportCliFile(std::string filename);


	private:


	protected:
		Parser(void);

	};

	template<typename T>
	static void Parser<T>::ReadHeader(ifstream data, int& position, FTYPE& ftype)
	{// ToDo: Implement header reader.
	}

	template<typename T>
	void Parser<T>::ReadBodyASCII(ifstream data, const int& position)
	{// ToDo: Implement ASCII body reader.
	}

	template<typename T>
	void Parser<T>::ReadBodyBinary(ifstream data, const int& position)
	{// ToDo: Implement Binary body reader.
	}

	template<typename T>
	CLI::Geometry<T> Parser<T>::ImportCliFile(std::string filename)
	{ // ToDo: Finish implementing the Geometry importer from CLI file.
		Geometry<T> geom;
		ifstream data(filename, ios::in);
		ReadHeader(data, auto position, auto ftype);
		if (ftype == FTYPE::ASCII)
		{
			ReadBodyASCII(data, position);
		}
		else if (ftype == FTYPE::BINARY)
		{
			ReadBodyBinary(data, position);
		}


		return geom;
	}

	template<typename T>
	Parser<T>::Parser(void)
	{
	}

}





#endif