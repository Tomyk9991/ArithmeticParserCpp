#pragma once
#include <string>

#include "Expression.h"

class Compiler
{
public:
	Compiler(const std::string&& sourceCode);
	Compiler(const Compiler& other);
	~Compiler();

public:
	double evaluate();
	double evaluate(const std::string& sourceCode);

public:
	Expression* get_syntax_tree();

private:
	void init_compiler(const std::string&& sourceCode);

private:
	void next_char();
	bool eat(int charToEat);
	Expression* parse();
	Expression* parse_expression();
	Expression* parse_term();
	Expression* parse_factor();
private:
	std::string sourceCode;
	int pos = -1;
	int ch = -1;
	Expression* syntaxTree;
};
