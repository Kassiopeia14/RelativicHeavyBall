#include "consoleOutput.h"

ConsoleOutput::ConsoleOutput()
{
}

ConsoleOutput::~ConsoleOutput()
{
}

ConsoleOutput& ConsoleOutput::operator<<(int _value)
{
	std::cout << _value << ": ";

	return *this;
}

ConsoleOutput& ConsoleOutput::operator<<(std::vector<double> _value)
{
	for (auto valueItem = _value.begin(); valueItem != _value.end(); valueItem++)
	{
		std::cout << *valueItem << ", ";
	}

	return *this;
}

ConsoleOutput& ConsoleOutput::operator<<(double _value)
{
	std::cout << _value;

	return *this;
}

ConsoleOutput& ConsoleOutput::operator<<(Special _special)
{
	switch (_special)
	{
	case Special::Endl:
		std::cout << std::endl;
		break;
	default:
		break;
	}

	return *this;
}
