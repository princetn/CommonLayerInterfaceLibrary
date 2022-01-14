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
	
	//cout<< "PID: "<<std::this_thread::get_id() << endl;
	string path = R"(D:\MyDownloads\CLI-Candidate-Kit-04-06-21\CLI\box_cli_ascii.cli)";

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



	auto geometry = Parser<float>::ImportCliFile(path);

	geometry.LayerInfo();

	


	

	try 
	{
		checkarguments(argc);
	}
	catch(invalid_argument& e)
	{
		cerr << e.what() << endl;
		return -1;
	}


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
