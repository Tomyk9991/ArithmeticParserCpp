#pragma once
#include <string>

#include "Operation.h"

class Expression
{
public:
	Expression();
	Expression(const Expression& other);
	Expression(double val);
	Expression(std::string&& func, Expression* lhs, double value);
	Expression(Expression* lhs, Operation op, Expression* rhs, double value);
	~Expression();
public:
	double evaluate() const;
	Expression* add(Expression* other) const;
	Expression* sub(Expression* other) const;
	Expression* mul(Expression* other) const;
	Expression* div(Expression* other) const;
	Expression* pow(Expression* other) const;
	std::string tree_view(std::string& indent, bool last = true);
private:

	std::string to_inner_string();
	std::string to_string();

public:
	double value = std::numeric_limits<double>::infinity();
private:
	std::string func;

	Expression* lhs = nullptr;
	Expression* rhs = nullptr;
	Operation op = NOOP;
};