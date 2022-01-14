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
int ParseArguments(int argc, char** argv);

string copyright_msg = R"(CLI library  Copyright (C) 2022  Amir Gasmi <argasmi@gmail.com>.
This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.)";

//TODO: Need to provide conditions for use.
// Add an option to output to file calculation.
// Add support for output directory.
int main(int argc, char** argv)
{
	
	//cout<< "PID: "<<std::this_thread::get_id() << endl;
	string path = R"(D:\MyDownloads\CLI-Candidate-Kit-04-06-21\CLI\box_cli_ascii.cli)";
	

	
	

	try 
	{
		auto v = ParseArguments(argc, argv);
		if (v == -1)
		{
			checkarguments(argc);
		}
		else if (v == 2)
		{
			path = argv[2];
			auto geometry = Parser<float>::ImportCliFile(path);

			geometry.LayerInfo();
		}
		else
		{
			
			return -1;
		}
	}
	catch(exception& e)
	{
		cerr << e.what() << endl;
		return -1;
	}


	return 0;
}

void checkarguments(int argc)
{
	throw invalid_argument(R"(Error: The number of arguments is invalid!)");
}

int ParseArguments(int argc, char** argv)
{
	string help_options = R"(
This program parses Common Layer Interface files in ascii & binary formats. 
Produces a Geometry data structure and displays area calculation of each layer.
To run the program type: CLILayerAreaCalculator.exe <options> <arguments>
options:
-help: to display this menu.
-path <path/to/cli/file>	to display area calculations on console.
-dir <path/to/cli/directory/containing/cli/files	 [to be added]..
-out <path/to/output/directory/	 [to be added].
-show c	 display copyright conditions. [to be added].
-show w displays copyright Warranty.
)";
	
	if (argc == 2)
	{
		if (strcmp(argv[1], "-help") == 0)
		{
			cout << help_options << endl;
			return 1;
		}
		
		
	}
	else if (argc == 3)
	{
		if (strcmp(argv[1], "-path") == 0)
		{			
			return 2;
		}
		if (strcmp(argv[1], "-dir") == 0)
		{
			
			return 3;
		}
		if (strcmp(argv[1], "-show") == 0)
		{

			return 4;
		}

	}
	else if (argc == 4)
	{
		if ((strcmp(argv[1], "-path")==0) && (strcmp(argv[3], "-out") == 0))
		{
			
			return 5;
		}
		if ((strcmp(argv[1], "-dir") == 0) && (strcmp(argv[3], "-out") == 0))
		{

			return 6;
		}

	}
	else
	{
		cout << copyright_msg << endl;
		cout << "\nType: CLILayerAreaCalculator.exe -help to display options" << endl;
		return -1;

	}
	
}
