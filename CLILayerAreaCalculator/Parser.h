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
		static Header<T>& ReadHeader(ifstream& data, unsigned int& position);
		static Geometry<T>& ReadBodyASCII(ifstream& data, const unsigned int& position, const Header<T>& header, bool zerolayer=false);
		static Geometry<T>& ReadBodyBinary(ifstream& data, const unsigned int& position, const Header<T>& header, bool zerolayer = false);
		static Geometry<T>& ImportCliFile(std::string filename);
		static vector<string>& split(const string& s, const string& delimiter);
		static void getCommandLine(ifstream& data, string& line);
		static void RemoveComment(string& line);
		static void trimLine(string& line);

	private:
		


	protected:
		

	};

	template<typename T>
	Header<T>& Parser<T>::ReadHeader(ifstream& data, unsigned int& position)
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
		
		while (!data.eof())
		{
			getCommandLine(data, line);
			trimLine(line);
			if (line.find("HEADERSTART") != string::npos)
				continue;
			if (line.find("HEADEREND") != string::npos)
				break;
			if(line.find("ASCII") != string::npos)
				header->Ftype = Header<T>::FTYPE::ASCII;
			if(line.find("BINARY") != string::npos)
				header->Ftype = Header<T>::FTYPE::BINARY;
			if (line.find("UNITS") != string::npos)
			{
				auto res = split(line, "/");
				header->Units = (T)stod(res.back());
			}
			if (line.find("VERSION") != string::npos)
			{
				auto res = split(line, "/");
				header->Version = stoi(res.back());
			}
			if (line.find("LABEL") != string::npos)
			{
				auto res = split(line, "/");
				auto s = res.back();
				auto res2 = split(s, ",");
				header->Label = pair<unsigned int, string>(stoul(res2.front()), res2.back());
			}
			if (line.find("DATE") != string::npos)
			{
				auto res = split(line, "/");
				header->Date = stoul(res.back());
			}
			if (line.find("LAYERS") != string::npos)
			{
				auto res = split(line, "/");
				header->Layers = stoul(res.back());
			}
			if (line.find("ALIGN") != string::npos)
			{
				
				header->Align = true;
			}
			if (line.find("DIMENSION") != string::npos)
			{
				auto res = split(line, "/");
				auto s = res.back();
				auto res1 = split(s, ",");
				for (auto val : res1)
				{
					header->Dimension->push_back((T)stod(val));
				}
			}
			
		}
		position = data.tellg();
		cout << "data position "<<data.tellg() <<" position= " << position<< endl;
		

		

		return *header;
	}

	template<typename T>
	Geometry<T>& Parser<T>::ReadBodyASCII(ifstream& data, const unsigned int& position, const Header<T>& header, bool zerolayer)
	{// ToDo: Need to replace getline with a custom function for reading command lines and trim out any extras.
		Point<T> pt;
		Polyline<T> poly;
		Layer<T> layer;
		Geometry<T>* geom = new Geometry<T>();
		string s = "HEADEREND";
		data.seekg(position); // 2 is for carriage & feedline (\r\n)

		cout << "The data has been positioned just after headerend: " << data.tellg() << endl;

		string line;
		unsigned int idx = 0;
		unsigned int idpt = 0;
		// zero layer:
		layer.Thickness = 0;
		layer.Index = 0;
		layer.Z = 0;
		if (zerolayer)
		{
			geom->Layers->push_back(layer);
			idx = 1;
		}

		while (!data.eof())
		{
			getCommandLine(data, line);
			trimLine(line);
			if (line.find("GEOMETRYSTART") != string::npos)
				continue;
			if (line.find("GEOMETRYEND") != string::npos)
				break;
			if (line.find("LAYER") != string::npos)
			{
				layer.InnerContours->clear();
				layer.OuterContours->clear();
				layer.Hatches->clear();

				auto res = split(line, "/");
				layer.Index = idx;
				idx++;
				layer.Z = header.Units() * (T)stod(res.back());
				geom->Layers->push_back(layer);
			}
			if (line.find("POLYLINE") != string::npos)
			{
				poly.Points->clear();
				auto res = split(line, "/");
				auto res1 = split(res.back(), ",");
				// Polyline processing.
				poly.Id = stoul(res1[0]);
				auto dir = stoul(res1[1]);
				auto n = stoul(res1[2]);
				for (unsigned int i = 0; i < (n-1); i++) // skipping the last point assuming it is equal to first.
				{
					pt.X = (T) stod(res1[3 + 2*i]) * header.Units();
					pt.Y = (T)stod(res1[4 + 2*i]) * header.Units();
					pt.Id = idpt;
					idpt++;
					poly.Points->push_back(pt);
				}

				if (dir == 0)
				{
					layer.InnerContours->push_back(poly);
				}
				else if (dir == 1)
				{
					layer.OuterContours->push_back(poly);
				}
				else if (dir == 2)
				{
					// not a solid line. Do nothing for now.
					// assuming this should be only for hatches?
					continue;
				}



				// need to do this in case a layer doesn't have any polylines.
				geom->Layers->pop_back();
				geom->Layers->push_back(layer);				
			}
			if (line.find("HATCHES") != string::npos)
			{// TODO: Hatches are not processed properly. This needs to be fixed.
				poly.Points->clear();
				auto res = split(line, "/");
				auto res1 = split(res.back(), ",");
				// Polyline processing.
				poly.Id = stoul(res1[0]);
				//auto dir = stoul(res1[1]);
				auto n = stoul(res1[2]);
				for (unsigned int i = 0; i < (n - 1); i++) // skipping the last point assuming it is equal to first.
				{
					pt.X = (T)stod(res1[3 + 2*i]) * header.Units();
					pt.Y = (T)stod(res1[4 + 2*i]) * header.Units();
					pt.Id = idpt;
					idpt++;
					poly.Points->push_back(pt);
				}
				layer.Hatches->push_back(poly);

				

				// need to do this in case a layer doesn't have any polylines.
				geom->Layers->pop_back();
				geom->Layers->push_back(layer);
			}

		}


		auto layer0 = geom->Layers->begin();
		int i = 0;
		for (auto it = geom->Layers->begin(); it != geom ->Layers->end(); it++)
		{
			if (i == 0)
			{
				i = 1;
				continue;
			}
			it->Thickness = it->Z() - layer0->Z();
			layer0 = it;

		}

		return *geom;
	}

	template<typename T>
	Geometry<T>& Parser<T>::ReadBodyBinary(ifstream& data, const unsigned int& position, const Header<T>& header, bool zerolayer)
	{// ToDo: Implement Binary body reader.
		Point<T> pt;
		Polyline<T> poly;
		Layer<T> layer;
		Geometry<T>* geom = new Geometry<T>();
		
		
		unsigned int idx = 0;
		unsigned int idpt = 0;
		// zero layer:
		layer.Thickness = 0;
		layer.Index = 0;
		layer.Z = 0;
		if (zerolayer)
		{
			geom->Layers->push_back(layer);
			idx = 1;
		}
	
		data.seekg(position);
		cout << "The binary data has been positioned just after HEADEREND: " << data.tellg() << endl;

		unsigned char* CI = new unsigned char[2];
		unsigned char* fourbytes = new unsigned char[4];
		unsigned char* twobytes = new unsigned char[2];
		float f;
		unsigned short ui;
		int si;
		auto pos = data.tellg();
		data.seekg(0, ios::end);
		auto size = data.tellg();
		data.seekg((int)pos+3);

		while (data.tellg() < size)
		{
			data.read((char*)CI, 2);
			memcpy(&ui, CI, sizeof(ui));
			if (ui == 127) // Start Layer (long)
			{
				layer.InnerContours->clear();
				layer.OuterContours->clear();
				layer.Hatches->clear();
				data.read((char*)fourbytes, 4);
				memcpy(&f, fourbytes, sizeof(f));
				layer.Z = (T)f * header.Units();
				layer.Index = idx;
				idx++;
				geom->Layers->push_back(layer);
			}
			else if (ui == 128) // Start Layer (short)
			{
				layer.InnerContours->clear();
				layer.OuterContours->clear();
				layer.Hatches->clear();
				data.read((char*)twobytes, 2);
				memcpy(&ui, twobytes, sizeof(ui));
				layer.Z = (T)ui * header.Units();
				layer.Index = idx;
				idx++;
				geom->Layers->push_back(layer);
			}
			else if (ui == 129) // Start Poly (short)
			{
				poly.Points->clear();
				data.read((char*)twobytes, 2);
				memcpy(&ui, twobytes, sizeof(ui));
				poly.Id = ui;
				data.read((char*)twobytes, 2);
				memcpy(&ui, twobytes, sizeof(ui));
				auto dir = ui;
				data.read((char*)twobytes, 2);
				memcpy(&ui, twobytes, sizeof(ui));
				auto n = ui;

				for (unsigned short i = 0; i < (n - 1); i++) // skipping the last point assuming it is equal to first.
				{
					data.read((char*)twobytes, 2);
					memcpy(&ui, twobytes, sizeof(ui));
					pt.X = (T)ui * header.Units();
					data.read((char*)twobytes, 2);
					memcpy(&ui, twobytes, sizeof(ui));
					pt.Y = (T)ui * header.Units();
					pt.Id = idpt;
					idpt++;
					poly.Points->push_back(pt);
				}
				// reading the extra cooridnates:
				data.read((char*)twobytes, 2);
				data.read((char*)twobytes, 2);

				





				if (dir == 0)
				{
					layer.InnerContours->push_back(poly);
				}
				else if (dir == 1)
				{
					layer.OuterContours->push_back(poly);
				}
				else if (dir == 2)
				{
					// not a solid line. Do nothing for now.
					// assuming this should be only for hatches?
					continue;
				}


				
				// need to do this in case a layer doesn't have any polylines.
				geom->Layers->pop_back();
				geom->Layers->push_back(layer);
			}
			else if (ui == 130) // Start Poly (long)
			{
				poly.Points->clear();
				data.read((char*)fourbytes, 4);
				memcpy(&si, fourbytes, sizeof(si));
				poly.Id = si;
				data.read((char*)fourbytes, 4);
				memcpy(&si, fourbytes, sizeof(si));
				auto dir = si;
				data.read((char*)fourbytes, 4);
				memcpy(&si, fourbytes, sizeof(si));
				auto n = si;

				for (int i = 0; i < (n - 1); i++) // skipping the last point assuming it is equal to first.
				{
					data.read((char*)fourbytes, 4);
					memcpy(&f, fourbytes, sizeof(f));
					pt.X = (T)f * header.Units();
					data.read((char*)fourbytes, 4);
					memcpy(&f, fourbytes, sizeof(f));
					pt.Y = (T)f * header.Units();
					pt.Id = idpt;
					idpt++;
					poly.Points->push_back(pt);
				}
				// reading the extra cooridnates:
				data.read((char*)fourbytes, 4);
				data.read((char*)fourbytes, 4);
				







				if (dir == 0)
				{
					layer.InnerContours->push_back(poly);
				}
				else if (dir == 1)
				{
					layer.OuterContours->push_back(poly);
				}
				else if (dir == 2)
				{
					// not a solid line. Do nothing for now.
					// assuming this should be only for hatches?
					continue;
				}



				// need to do this in case a layer doesn't have any polylines.
				geom->Layers->pop_back();
				geom->Layers->push_back(layer);
			}
			else if (ui == 131) // Start Hatches (short)
			{
				poly.Points->clear();
				data.read((char*)twobytes, 2);
				memcpy(&ui, twobytes, sizeof(ui));
				poly.Id = ui;
				data.read((char*)twobytes, 2);
				memcpy(&ui, twobytes, sizeof(ui));
				auto n = ui;

				for (unsigned short i = 0; i < n; i++) 
				{
					poly.Points->clear();
					data.read((char*)twobytes, 2);
					memcpy(&ui, twobytes, sizeof(ui));
					pt.X = (T)ui * header.Units();
					data.read((char*)twobytes, 2);
					memcpy(&ui, twobytes, sizeof(ui));
					pt.Y = (T)ui * header.Units();
					pt.Id = idpt;
					idpt++;
					poly.Points->push_back(pt);
					data.read((char*)twobytes, 2);
					memcpy(&ui, twobytes, sizeof(ui));
					pt.X = (T)ui * header.Units();
					data.read((char*)twobytes, 2);
					memcpy(&ui, twobytes, sizeof(ui));
					pt.Y = (T)ui * header.Units();
					pt.Id = idpt;
					idpt++;
					poly.Points->push_back(pt);
					layer.Hatches->push_back(poly);
				}






				// need to do this in case a layer doesn't have any polylines.
				geom->Layers->pop_back();
				geom->Layers->push_back(layer);
			}
			else if (ui == 132) // Start Hatches (long)
			{
				poly.Points->clear();
				data.read((char*)fourbytes, 4);
				memcpy(&si, fourbytes, sizeof(si));
				poly.Id = si;
				data.read((char*)fourbytes, 4);
				memcpy(&si, fourbytes, sizeof(si));
				auto n = si;

				for (int i = 0; i < n; i++)
				{
					poly.Points->clear();
					data.read((char*)fourbytes, 4);
					memcpy(&f, fourbytes, sizeof(f));
					pt.X = (T)f * header.Units();
					data.read((char*)fourbytes, 4);
					memcpy(&f, fourbytes, sizeof(f));
					pt.Y = (T)f * header.Units();
					pt.Id = idpt;
					idpt++;
					poly.Points->push_back(pt);
					data.read((char*)fourbytes, 4);
					memcpy(&f, fourbytes, sizeof(f));
					pt.X = (T)f * header.Units();
					data.read((char*)fourbytes, 4);
					memcpy(&f, fourbytes, sizeof(f));
					pt.Y = (T)f * header.Units();
					pt.Id = idpt;
					idpt++;
					poly.Points->push_back(pt);
					layer.Hatches->push_back(poly);
				}






				// need to do this in case a layer doesn't have any polylines.
				geom->Layers->pop_back();
				geom->Layers->push_back(layer);
			}
			

		}
		auto layer0 = geom->Layers->begin();
		int i = 0;
		for (auto it = geom->Layers->begin(); it != geom->Layers->end(); it++)
		{
			if (i == 0)
			{
				i = 1;
				continue;
			}
			it->Thickness = it->Z() - layer0->Z();
			layer0 = it;

		}


		return *geom;
	}

	template<typename T>
	Geometry<T>& Parser<T>::ImportCliFile(std::string filename)
	{ 
		Geometry<T>* geom = new Geometry<T>();
		ifstream data(filename, ios::in);
		unsigned int position;
		auto header = ReadHeader(data, position);
		if (header.Ftype() == Header<T>::FTYPE::ASCII)
		{
			*geom = ReadBodyASCII(data, position, header);
			data.close();
		}
		else if (header.Ftype() == Header<T>::FTYPE::BINARY)
		{ // TODO: Need to handle the case of 32bit alignment.
			data.close();
			ifstream data1(filename, ios::in|ios::binary);
			*geom = ReadBodyBinary(data1, position, header);
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

	template<typename T>
	void Parser<T>::getCommandLine(ifstream& data, string& line)
	{
		line.clear();

		char* s = new char[1];
		unsigned int start = 0, _end = 0;
		bool first = false, second = false;
		auto pos = (int)data.tellg();
		data.seekg(0, ios::end);
		auto size = (int)data.tellg();
		data.seekg(pos);
		while (data.tellg() < (size))
		{
			data.read(s, 1);
			if (first && second)
			{
				line.push_back(s[0]);
			}
			if (s[0] == '$' && !first)
			{
				first = true;
			}
			else if (s[0] == '$' && !second)
			{
				second = true;
				start = data.tellg();
			}
			else if (s[0] == '$' || (line.find("HEADEREND")!= string::npos))
			{
				break;
			}
			
		}
		if((line.find("HEADEREND") == string::npos ) && line.size() != 0)
			line.pop_back();
		_end = data.tellg();
		if((data.tellg()<(size-3)))
			data.seekg(_end - 3);

	}

	template<typename T>
	void Parser<T>::RemoveComment(string& line)
	{// TODO: Need to implement a method for finding & removing comment from command line.
	}

	template<typename T>
	void Parser<T>::trimLine(string& line)
	{
		string s;
		for (int i = 0; i < line.size(); i++)
		{
			if (isalpha(line[i]) || isdigit(line[i]) || (line[i] == '/') || (line[i] == ',') || (line[i] == '.'))
			{
				s.push_back(line[i]);
			}
		}
		line = s;
	}

	

}





#endif