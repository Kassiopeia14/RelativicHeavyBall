#include "normTarget.h"

double NormTarget::target(std::vector<double> _coordinates)
{
	double result = 0;

	result = _coordinates[0] * _coordinates[0] + 10 * _coordinates[1] * _coordinates[1];
	
	/*
	for (auto coordinateItem = _coordinates.begin(); coordinateItem != _coordinates.end(); coordinateItem++)
	{
		result += *coordinateItem * *coordinateItem;
	}
	*/
	return result;
}

std::vector<double> NormTarget::gradient(std::vector<double> _coordinates)
{
	std::vector<double> result(_coordinates.size());

	result[0] = _coordinates[0];
	result[1] = 20 * _coordinates[1];

	/*
	auto coordinateItem = _coordinates.begin();

	for (auto resultItem = result.begin(); resultItem != result.end(); resultItem++, coordinateItem++)
	{
		*resultItem = 2 * *coordinateItem;
	}
	*/
	return result;
}

Matrix NormTarget::gessian(std::vector<double> _coordinates)
{
	const size_t dimention = _coordinates.size();
	Matrix result(dimention, dimention);

	for (int i = 0; i < dimention; i++)
		for (int j = 0; j < dimention; j++)
		{
			result(i, j) = (i == j ? 2 : 0);
		}
	
	return result;
}
