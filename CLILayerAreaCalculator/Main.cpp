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

using namespace std;
using namespace CLI;
void checkarguments(int argc);



int main(int argc, char** argv)
{
	string path = R"(D:\MyDownloads\CLI-Candidate-Kit-04-06-21\CLI\box_cli_ascii.cli)";
	cout << path << endl;
	Point<float> ptf;
	ptf.X = 10;
	ptf.Y = 2.0;
	Property<float> f ;
	f = 20;
	Property<Point<float>> pt;
	pt = ptf;
	Polyline<float> poly;
	Point<float> ptf1;
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
	cout << "The area of the triangle is: " << poly.getArea() << endl;
	auto geometry = Parser<float>::ImportCliFile(path);



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
		throw invalid_argument("The number of arguments is invalid! \n\
proper call is main.exe path/to/cli/file");

}
