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
#include "Header.h"

namespace CLI
{
	using namespace std;

	template <typename T>
	class Parser
	{
	public:
		//typedef enum { ASCII, BINARY }FTYPE;
		//typedef enum { BIG, LITTLE }ENDIAN;
		Parser(void) = delete;
		static Header<T>& ReadHeader(ifstream& data, int& position);
		static Geometry<T>& ReadBodyASCII(ifstream& data, const int& position);
		static Geometry<T>& ReadBodyBinary(ifstream& data, const int& position);
		static Geometry<T>& ImportCliFile(std::string filename);
		static vector<string>& split(const string& s, const string& delimiter);

	private:
		


	protected:
		

	};

	template<typename T>
	Header<T>& Parser<T>::ReadHeader(ifstream& data, int& position)
	{// ToDo: Implement header reader.
		//fstream data(path, ios::in);
		Header<T>* header = new Header<T>();

		if (!data.is_open())
		{
			cout << " Coud not open the file!" << endl;
			return *header;
		}
		string line;
		header->Align = false;
		
		while (getline(data, line))
		{
			if (line.find("$$HEADERSTART") != string::npos)
				continue;
			if (line.find("$$HEADEREND") != string::npos)
				break;
			if(line.find("$$ASCII") != string::npos)
				header->Ftype = Header<T>::FTYPE::ASCII;
			if(line.find("$$BINARY") != string::npos)
				header->Ftype = Header<T>::FTYPE::BINARY;
			if (line.find("$$UNITS") != string::npos)
			{
				auto res = split(line, "/");
				header->Units = (T)stod(res.back());
			}
			if (line.find("$$VERSION") != string::npos)
			{
				auto res = split(line, "/");
				header->Version = stoi(res.back());
			}
			if (line.find("$$LABEL") != string::npos)
			{
				auto res = split(line, "/");
				auto s = res.back();
				auto res2 = split(s, ",");
				header->Label = pair<unsigned int, string>(stoul(res2.front()), res2.back());
			}
			if (line.find("$$DATE") != string::npos)
			{
				auto res = split(line, "/");
				header->Date = stoul(res.back());
			}
			if (line.find("$$LAYERS") != string::npos)
			{
				auto res = split(line, "/");
				header->Layers = stoul(res.back());
			}
			if (line.find("$$ALIGN") != string::npos)
			{
				
				header->Align = true;
			}
			if (line.find("$$DIMENSION") != string::npos)
			{
				auto res = split(line, "/");
				auto s = res.back();
				auto res1 = split(s, ",");
				for (auto val : res1)
				{
					header->Dimension->push_back((T)stod(val));
				}
			}
			position = data.tellg();
		}
		cout << "data position "<<data.tellg() <<" position= " << position<< endl;
		

		

		return *header;
	}

	template<typename T>
	Geometry<T>& Parser<T>::ReadBodyASCII(ifstream& data, const int& position)
	{// ToDo: Implement ASCII body reader.
		Geometry<T>* geom = new Geometry<T>();
		string s = "$$HEADEREND";
		data.seekg(position + s.length()+2);
		cout << "The data has been positioned just after headerend: " << data.tellg() << endl;


		return *geom;
	}

	template<typename T>
	Geometry<T>& Parser<T>::ReadBodyBinary(ifstream& data, const int& position)
	{// ToDo: Implement Binary body reader.
		Geometry<T>* geom = new Geometry<T>();
		string s = "$$HEADEREND";
		data.seekg(position + s.length());
		cout << "The data has been positioned just after headerend: " << data.tellg() << endl;



		return *geom;
	}

	template<typename T>
	Geometry<T>& Parser<T>::ImportCliFile(std::string filename)
	{ 
		Geometry<T>* geom = new Geometry<T>();
		ifstream data(filename, ios::in);
		int position;
		auto header = ReadHeader(data, position);
		if (header.Ftype() == Header<T>::FTYPE::ASCII)
		{
			*geom = ReadBodyASCII(data, position);
			data.close();
		}
		else if (header.Ftype() == Header<T>::FTYPE::BINARY)
		{ // TODO: Need to handle the case of 32bit alignment.
			data.close();
			ifstream data1(filename, ios::in|ios::binary);
			*geom = ReadBodyBinary(data1, position);
		}


		return *geom;
	}

	template<typename T>
	vector<string>& Parser<T>::split(const string& s, const string& delimiter)
	{
		string st = s;
		vector<string>* res = new vector<string>();

		size_t pos = 0;
		string token;

		while ((pos = st.find(delimiter))!= string::npos)
		{
			token = st.substr(0, pos);
			res->push_back(token);
			st.erase(0, pos + delimiter.length());
		}
		res->push_back(st);

		return *res;
	}

	

}





#endif