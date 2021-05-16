#include "../include/Expression.h"

#include <algorithm>

#include "../include/Operation.h"

#include <complex>
#include <iomanip>
#include <vector>

Expression::Expression()
{
	this->lhs = nullptr;
	this->rhs = nullptr;
	this->op = NOOP;
	this->value = std::numeric_limits<double>::infinity();
}

Expression::Expression(const Expression& other)
{
	this->value = other.evaluate();
}

Expression::Expression(double val)
{
	this->lhs = nullptr;
	this->rhs = nullptr;
	this->value = val;
}

Expression::Expression(const std::string&& func, Expression* lhs, double value)
{
	this->func = func;
	this->lhs = lhs;
	this->rhs = nullptr;
	this->value = value;
}

Expression::Expression(Expression* lhs, Operation op, Expression* rhs, double value)
{
	this->lhs = lhs;
	this->op = op;
	this->rhs = rhs;

	this->value = value;
}

Expression::~Expression()
{
	delete this->rhs;
	delete this->lhs;
}

Expression* Expression::add(Expression* other) const
{
	return new Expression(const_cast<Expression*>(this), ADD, other, this->value + other->evaluate());
}

Expression* Expression::sub(Expression* other) const
{
	return new  Expression(const_cast<Expression*>(this), SUB, other, this->value - other->evaluate());
}

Expression* Expression::mul(Expression* other) const
{
	return new  Expression(const_cast<Expression*>(this), MUL, other, this->value * other->evaluate());
}

Expression* Expression::div(Expression* other) const
{
	const double value2 = other->evaluate();

	if (value2 == 0.0)
		throw std::overflow_error("Divide by zero is not allowed");

	return new Expression(const_cast<Expression*>(this), DIV, other, this->value / value2);
}

Expression* Expression::pow(Expression* other) const
{
	return new Expression(const_cast<Expression*>(this), POW, other, std::pow(this->value, other->evaluate()));
}

std::string Expression::tree_view(std::string& indent, bool last)
{
	std::stringstream ss;
	if (last)
	{
		ss << "└─";
		indent += "  ";
	}
	else
	{
		ss << "├─";
		indent += "| ";
	}

	std::string inner = this->to_inner_string();
	ss << inner << '\n';

	std::vector<Expression*> children;

	if (this->lhs != nullptr) children.push_back(this->lhs);
	if (this->rhs != nullptr) children.push_back(this->rhs);

	for (int i = 0; i < children.size(); i++)
	{
		ss << children[i]->tree_view(indent, i == 1);
	}

	return ss.str();
}

std::string Expression::to_inner_string()
{
	std::ostringstream ss;
	ss << std::fixed;
	ss << std::setprecision(2);
	ss << this->value;

	if (!this->func.empty())
	{
		std::transform(this->func.begin(), this->func.end(), this->func.begin(), ::toupper);
		return (std::fmod(this->value, 1) == 0 ? std::to_string(this->value) : ss.str()) + ", " + this->func;
	}

	std::string lhs = this->lhs == nullptr ? "NULL" : this->lhs->to_string();
	std::string rhs = this->rhs == nullptr ? "NULL" : this->rhs->to_string();

	constexpr double inf = std::numeric_limits<double>::infinity();

	if (this->value != inf && this->lhs == nullptr && this->rhs == nullptr)
		return std::fmod(this->value, 1) == 0 ? std::to_string(this->value) : ss.str();

	if (this->op != NOOP && this->lhs == nullptr && this->rhs == nullptr)
		return operation_to_string(op);

	return (lhs + " " + operation_to_string(op) + " " + rhs);
}

std::string Expression::to_string()
{
	std::ostringstream ss;
	ss << std::fixed;
	ss << std::setprecision(2);
	ss << this->value;

	std::string lhs = this->lhs == nullptr ? "NULL" : this->lhs->to_string();
	std::string rhs = this->rhs == nullptr ? "NULL" : this->rhs->to_string();

	constexpr double inf = std::numeric_limits<double>::infinity();

	if (this->value != inf && this->lhs == nullptr && this->rhs == nullptr)
		return std::fmod(this->value, 1) == 0 ? std::to_string(this->value) : ss.str();

	if (this->op != NOOP && this->lhs == nullptr && this->rhs == nullptr)
		return operation_to_string(op);

	return lhs + " " + operation_to_string(op) + " " + rhs;
}


double Expression::evaluate() const
{
	return value;
}
