/*
* Main entry point.
* Author: Amir Gasmi <argasmi@gmail.com>
* Date: 1/10/2022
*/

#include "Polyline.h"
#include "Parser.h"
#include <iostream>
#include <stdexcept>
#include "Point.h"
#include <thread>

using namespace std;
using namespace CLI;
void checkarguments(int argc);
void ParseArguments(char** argc);

string copyright_msg = R"(CLI library  Copyright (C) 2022  Amir Gasmi.
This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.)";

int main(int argc, char** argv)
{
	Layer<float> layer;
	cout << copyright_msg << endl;
	cout<< "PID: "<<std::this_thread::get_id() << endl;
	string path = R"(D:\MyDownloads\CLI-Candidate-Kit-04-06-21\CLI\VulcanFormsSamplePartA.cli)";

	/*
	ifstream data;
	data.open(path, ios::in);
	string line;
	auto pos = (int)data.tellg();
	data.seekg(0, ios::end);
	auto size = (int)data.tellg();
	data.seekg(pos);
	while(data.tellg() < size)
	{
		Parser<float>::getCommandLine(data, line);
		Parser<float>::trimLine(line);
		cout<<line<<endl;
		
	}
	data.close();
	
	*/


	cout << path << endl;
	Point<float> ptf;
	ptf.X = 0.600;
	ptf.Y = 73.323;
	cout << ptf << endl;
	Property<float> f ;
	f = 20;
	Property<Point<float>> pt;
	pt = ptf;
	Polyline<float> poly;
	Point<float> ptf1;
	// layer 1;
	ptf1.X = 0;
	ptf1.Y = 0;
	poly.Points->push_back(ptf1);
	ptf1.X = 0;
	ptf1.Y = 10;
	poly.Points->push_back(ptf1);
	ptf1.X = 10;
	ptf1.Y = 10;
	poly.Points->push_back(ptf1);
	ptf1.X = 10;
	ptf1.Y = 0;
	poly.Points->push_back(ptf1);
	layer.OuterContours->push_back(poly); // outerContour.
	layer.Index = 1;
	poly.Points->clear();
	ptf1.X = 2.5;
	ptf1.Y = 2.5;
	poly.Points->push_back(ptf1);
	ptf1.X = 2.5;
	ptf1.Y = 7.5;
	poly.Points->push_back(ptf1);
	ptf1.X = 7.5;
	ptf1.Y = 7.5;
	poly.Points->push_back(ptf1);
	ptf1.X = 7.5;
	ptf1.Y = 2.5;
	poly.Points->push_back(ptf1);
	layer.InnerContours->push_back(poly); // innerContour.

	Geometry<float>* geom = new Geometry<float>();



	cout << layer << endl;
	cout << "============> Geometry info: " << endl;
	geom->Layers->push_back(layer);
	geom->Layers->push_back(layer);
	geom->Layers->push_back(layer);
	geom->LayerInfo();
	

	cout << "The area of the triangle is: " << poly.getArea() << endl;
	auto geometry = Parser<float>::ImportCliFile(path);

	geometry.LayerInfo();

	


	cout << "ptf= (" << ptf.X() << ", " << ptf.Y() << ")" << endl;
	cout << "pt->X()= " << pt->X() << " pt->Y() " << pt->Y() << endl;

	try 
	{
		checkarguments(argc);
	}
	catch(invalid_argument& e)
	{
		cerr << e.what() << endl;
		return -1;
	}


	cout << "number of arguments: " << argc << endl;
	for (int i = 0; i < argc; i++)
		cout << "argv[" << i << "]: " << argv[0] << endl;
	return 0;
}

void checkarguments(int argc)
{
	if(argc != 3)
		throw invalid_argument(R"(
Error: The number of arguments is invalid!
proper call is: program.exe -path path/to/cli/file)");

}

void ParseArguments(char** argc)
{
}
