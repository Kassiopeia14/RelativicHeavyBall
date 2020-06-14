#include "logisticRegressionTarget.h"

LogisticRegressionTarget::LogisticRegressionTarget():
	negativePoints_(),
	positivePoints_(),
	regularization_(0)
{
}

LogisticRegressionTarget::~LogisticRegressionTarget()
{
}

void LogisticRegressionTarget::setPoints(
	std::list<std::vector<double>> _negativePoints,
	std::list<std::vector<double>> _positivePoints)
{
	addPoints(negativePoints_, _negativePoints);
	addPoints(positivePoints_, _positivePoints);
}

void LogisticRegressionTarget::setRegularization(const double _regularization)
{
	regularization_ = _regularization;
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

void LogisticRegressionTarget::addPoints(
	std::list<std::vector<double>> &_destination, 
	std::list<std::vector<double>> _points)
{
	const size_t pointDimention = _points.begin()->size();
		
	for (auto sourcePointItem = _points.begin(); sourcePointItem != _points.end(); sourcePointItem++)
	{
		std::vector<double> newPoint(pointDimention + 1);

		auto coordinateItem = newPoint.begin();

		*coordinateItem = -1;
		coordinateItem++;

		for (auto sourceCoordinateItem = sourcePointItem->begin(); sourceCoordinateItem != sourcePointItem->end(); coordinateItem++, sourceCoordinateItem++)
		{
			*coordinateItem = *sourceCoordinateItem;
		}

		_destination.push_back(newPoint);
	}
}

void LogisticRegressionTarget::setPointsData(LogisticRegressionData& _data)
{
	const int negativePointCount = negativePoints_.size();
	_data.negativePointCount = negativePointCount;
	_data.negativePointXValues = new double[negativePointCount];
	_data.negativePointYValues = new double[negativePointCount];

	const int positivePointCount = positivePoints_.size();
	_data.positivePointCount = positivePointCount;
	_data.positivePointXValues = new double[positivePointCount];
	_data.positivePointYValues = new double[positivePointCount];

	int i = 0;
	for (auto pointItem = negativePoints_.begin(); pointItem != negativePoints_.end(); pointItem++, i++)
	{
		_data.negativePointXValues[i] = (*pointItem)[1];
		_data.negativePointYValues[i] = (*pointItem)[2];
	}

	i = 0;
	for (auto pointItem = positivePoints_.begin(); pointItem != positivePoints_.end(); pointItem++, i++)
	{
		_data.positivePointXValues[i] = (*pointItem)[1];
		_data.positivePointYValues[i] = (*pointItem)[2];
	}
}