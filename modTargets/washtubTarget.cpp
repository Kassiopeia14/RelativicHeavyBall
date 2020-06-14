#include "washtubTarget.h"

double WashtubTarget::target(std::vector<double> _coordinates)
{
	double result = 0;

	for (auto coordinateItem = _coordinates.begin(); coordinateItem != _coordinates.end(); coordinateItem++)
	{
		result += *coordinateItem * *coordinateItem * *coordinateItem * *coordinateItem;
	}

	return result;
}

std::vector<double> WashtubTarget::gradient(std::vector<double> _coordinates)
{
	std::vector<double> result(_coordinates.size());

	auto coordinateItem = _coordinates.begin();

	for (auto resultItem = result.begin(); resultItem != result.end(); resultItem++, coordinateItem++)
	{
		*resultItem = 4 * *coordinateItem * *coordinateItem * *coordinateItem;
	}

	return result;
}

Matrix WashtubTarget::gessian(std::vector<double> _coordinates)
{
	const size_t dimention = _coordinates.size();
	Matrix result(dimention, dimention);

	for (int i = 0; i < dimention; i++)
		for (int j = 0; j < dimention; j++)
		{
			result(i, j) = (i == j ? 12 * _coordinates[i] * _coordinates[i] : 0);
		}

	return result;
}
