#include "common.h"

double norm(std::vector<double> _arguments)
{
	double sum = 0;

	for (auto argumentsItem = _arguments.begin(); argumentsItem != _arguments.end(); argumentsItem++)
	{
		sum += *argumentsItem * *argumentsItem;
	}

	return sqrt(sum);
}