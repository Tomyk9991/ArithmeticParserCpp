
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdio>
#include "Windows.h"

#include "Compiler/include/Compiler.h"

#pragma execution_character_set("utf-8")

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(65001);

	using namespace std::chrono_literals;
	//std::string source = "((4 - 2^3 + 1) * -sqrt(3*3+4*4)) / 2";
	std::string source = "2 + 3";

	Compiler c = Compiler(std::move(source));
	std::cout << c.evaluate() << std::endl;

	std::this_thread::sleep_for(5ms);
	std::string indent;
	std::string treeView = c.get_syntax_tree()->tree_view(indent, true);

	std::cout << treeView;

	system("pause");
	return 0;
}
