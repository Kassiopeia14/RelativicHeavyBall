#include "logisticRegressionTarget.h"

LogisticRegressionTarget::LogisticRegressionTarget(
	std::list<std::vector<double>> _negativePoints,
	std::list<std::vector<double>> _positivePoints,
	const double _regularization):
	regularization_(_regularization),
	negativePoints_(createPointsVector(_negativePoints)),
	positivePoints_(createPointsVector(_positivePoints))
{
}

LogisticRegressionTarget::~LogisticRegressionTarget()
{
}

double LogisticRegressionTarget::target(std::vector<double> _coordinates)
{
	double result = regularization_ * (_coordinates * _coordinates) / 2;

	for (auto pointItem = negativePoints_.begin(); pointItem != negativePoints_.end(); pointItem++)
	{
		const double
			dotProduct = _coordinates * *pointItem,
			sign = -1,
			signedDotProduct = sign * dotProduct;

		result += log(1 + exp(-signedDotProduct));
	}

	for (auto pointItem = positivePoints_.begin(); pointItem != positivePoints_.end(); pointItem++)
	{
		const double
			dotProduct = _coordinates * *pointItem,
			sign = 1,
			signedDotProduct = sign * dotProduct;

		result += log(1 + exp(-signedDotProduct));
	}

	return result;
}

std::vector<double> LogisticRegressionTarget::gradient(std::vector<double> _coordinates)
{
	std::vector<double> result(_coordinates.size());

	for (int i = 0; i < _coordinates.size(); i++)
	{
		result[i] = regularization_ * _coordinates[i];

		for (auto pointItem = negativePoints_.begin(); pointItem != negativePoints_.end(); pointItem++)
		{
			const double
				dotProduct = _coordinates * *pointItem,
				sign = -1,
				signedDotProduct = sign * dotProduct;

			result[i] += - sign * (*pointItem)[i] / (1 + exp(signedDotProduct));
		}

		for (auto pointItem = positivePoints_.begin(); pointItem != positivePoints_.end(); pointItem++)
		{
			const double
				dotProduct = _coordinates * *pointItem,
				sign = 1,
				signedDotProduct = sign * dotProduct;

			result[i] += - sign * (*pointItem)[i] / (1 + exp(signedDotProduct));
		}
	}

	return result;
}

Matrix LogisticRegressionTarget::gessian(std::vector<double> _coordinates)
{
	Matrix result(_coordinates.size(), _coordinates.size());

	for (int i = 0; i < _coordinates.size(); i++)
	{
		for (int j = 0; j < _coordinates.size(); j++)
		{
			result(i, j) = regularization_ * (i == j ? 1 : 0);

			for (auto pointItem = negativePoints_.begin(); pointItem != negativePoints_.end(); pointItem++)
			{
				const double
					dotProduct = _coordinates * *pointItem,
					sign = -1,
					signedDotProduct = sign * dotProduct;

				result(i, j) += (*pointItem)[i] * (*pointItem)[j] / ((1 + exp(signedDotProduct)) * (1 + exp(signedDotProduct)));
			}

			for (auto pointItem = positivePoints_.begin(); pointItem != positivePoints_.end(); pointItem++)
			{
				const double
					dotProduct = _coordinates * *pointItem,
					sign = 1,
					signedDotProduct = sign * dotProduct;

				result(i, j) += (*pointItem)[i] * (*pointItem)[j] / ((1 + exp(signedDotProduct)) * (1 + exp(signedDotProduct)));
			}
		}
	}

	return result;
}

std::vector<std::vector<double>> LogisticRegressionTarget::createPointsVector(std::list<std::vector<double>> _points)
{
	const size_t pointDimention = _points.begin()->size();

	std::vector<size_t> pointDimentions(_points.size());

	for (auto dimentionItem = pointDimentions.begin(); dimentionItem != pointDimentions.end(); dimentionItem++)
	{
		*dimentionItem = pointDimention + 1;
	}

	std::vector<std::vector<double>> result(pointDimentions.begin(), pointDimentions.end());

	auto pointItem = result.begin();
	for (auto sourcePointItem = _points.begin(); sourcePointItem != _points.end(); pointItem++, sourcePointItem++)
	{
		auto coordinateItem = pointItem->begin();

		*coordinateItem = -1;
		coordinateItem++;

		for (auto sourceCoordinateItem = sourcePointItem->begin(); sourceCoordinateItem != sourcePointItem->end(); coordinateItem++, sourceCoordinateItem++)
		{
			*coordinateItem = *sourceCoordinateItem;
		}
	}

	return result;
}