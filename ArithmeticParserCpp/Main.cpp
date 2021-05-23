
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "Windows.h"

#include "Compiler/include/Compiler.h"

#pragma execution_character_set("utf-8")
#define N 100000

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(65001);


	double* results = new double[N];

	Compiler c = Compiler("");
	auto start = std::chrono::high_resolution_clock::now();
	
	
	for (int i = 0; i < N; ++i)
	{	
		results[i] = c.evaluate("((4 - 2^3 + 1) * -sqrt(3*3+4*4)) / 2");
	}
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << "s\n";

	

	for (int i = 0; i < N; ++i)
	{
		if(results[i] != 7.5)
		{
			std::cout << "Fehler" << std::endl;
			break;
		}
	}

	delete[] results;

	// std::string indent;
	// std::string treeView = c.get_syntax_tree()->tree_view(indent, true);
	//
	// std::cout << treeView << std::endl;

	return 0;
}
