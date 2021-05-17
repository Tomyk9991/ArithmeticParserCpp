#include "../include/Compiler.h"



#include <algorithm>
#include <complex>
#include <stdexcept>

Compiler::Compiler(std::string&& sourceCode)
{
	init_compiler(std::move(sourceCode));
}

Compiler::Compiler(const Compiler& other)
{
	this->sourceCode = other.sourceCode;
	this->ch = other.ch;
	this->pos = other.pos;
	this->syntaxTree = nullptr;
}

Compiler::~Compiler()
{
	if (this->syntaxTree != nullptr)
		delete this->syntaxTree;
}

double Compiler::evaluate()
{
	if (this->sourceCode.compare("") != 0)
	{
		return this->parse()->evaluate();
	}

	throw std::invalid_argument("Source code must not be empty");
}

double Compiler::evaluate(std::string&& sourceCode)
{
	init_compiler(std::move(sourceCode));
	return this->parse()->evaluate();
}

Expression* Compiler::get_syntax_tree()
{
	return this->syntaxTree;
}

void Compiler::init_compiler(std::string&& sourceCode)
{
	this->sourceCode = std::move(sourceCode);
}

void Compiler::next_char()
{
	ch = ++pos < this->sourceCode.length() ? this->sourceCode[pos] : -1;
}

bool Compiler::eat(int charToEat)
{
	while (ch == ' ') next_char();
	if (ch == charToEat)
	{
		next_char();
		return true;
	}

	return false;
}

Expression* Compiler::parse()
{
	std::replace(this->sourceCode.begin(), this->sourceCode.end(), '.', ',');
	next_char();

	this->syntaxTree = parse_expression();
	if (pos < this->sourceCode.length())
		throw std::invalid_argument("Unexpected: " + '\"' + static_cast<char>(ch) + '\"');

	return this->syntaxTree;
}

Expression* Compiler::parse_expression()
{
	Expression* x = parse_term();
	while (true)
	{
		if (eat('+')) x = x->add(parse_term());
		else if (eat('-')) x = x->sub(parse_term());
		else return x;
	}
}

Expression* Compiler::parse_term()
{
	Expression* x = parse_factor();
	while (true)
	{
		if (eat('*')) x = x->mul(parse_term());
		else if (eat('/')) x = x->div(parse_term());
		else return x;
	}
}

Expression* Compiler::parse_factor()
{
	Expression* x;
	if (eat('+'))
	{
		x = parse_term();
		return x;
	}

	if (eat('-'))
	{
		x = parse_factor();
		x->value *= -1;
		return x;
	}

	int startPos = this->pos;
	if (eat('('))
	{
		x = parse_expression();
		if (!eat(')'))
		{
			throw std::invalid_argument("Expected: " + '\"' + ')' + '\"');
		}
	}
	else if (ch >= '0' && ch <= '9' || ch == '.')
	{
		while (ch >= '0' && ch <= '9' || ch == ',' || ch == '.') next_char();
		x = new Expression(std::stod(this->sourceCode.substr(startPos, this->pos - startPos)));
	}
	else if (ch >= 'a' && ch <= 'z')
	{
		while (ch >= 'a' && ch <= 'z') next_char();
		std::string func = this->sourceCode.substr(startPos, this->pos - startPos);
		x = parse_factor();


		if (func.compare("sqrt") == 0)
		{
			x = new Expression("Sqrt", x, std::sqrt(x->evaluate()));
		}
		else if (func.compare("sin") == 0)
		{
			x = new Expression("Sqrt", x, std::sin(x->evaluate()));
		}
		else if (func.compare("cos") == 0)
		{
			x = new Expression("Sqrt", x, std::cos(x->evaluate()));
		}
		else if (func.compare("tan") == 0)
		{
			x = new Expression("Sqrt", x, std::tan(x->evaluate()));
		}
		else
		{
			throw std::invalid_argument("Unknown function" + func);
		}
	}
	else
	{
		throw std::invalid_argument("Unexpected: " + '\"' + static_cast<char>(ch) + '\"');
	}

	if (eat('^'))
	{
		x = x->pow(parse_factor());
	}

	return x;
}
