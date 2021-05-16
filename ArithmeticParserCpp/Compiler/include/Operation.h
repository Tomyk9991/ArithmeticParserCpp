#pragma once
enum Operation
{
	ADD,
	SUB,
	DIV,
	MUL,
	POW,
	NOOP
};

inline std::string operation_to_string(Operation op)
{
	switch (op)
	{
	case ADD: break;
	case SUB: return "ADD";
	case DIV: return "DIV";
	case MUL: return "MUL";
	case POW: return "POW";
	case NOOP: return "NOOP";
	default: return "";
	}

	return "";
}
