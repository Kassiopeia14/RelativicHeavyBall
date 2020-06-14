#pragma once
#include <vector>
#include <iostream>

class ConsoleOutput
{
public:

	enum class Special
	{
		Endl
	};

	ConsoleOutput();
	~ConsoleOutput();

	ConsoleOutput& operator <<(int _value);
	ConsoleOutput& operator <<(std::vector<double> _value);
	ConsoleOutput& operator <<(double _value);
	ConsoleOutput& operator <<(Special _special);


private:

};