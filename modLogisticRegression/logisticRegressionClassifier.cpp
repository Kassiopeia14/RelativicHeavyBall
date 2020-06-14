#include "logisticRegressionClassifier.h"

LogisticRegressionClassifier::LogisticRegressionClassifier(
	std::list<std::vector<double>> _negativePoints, 
	std::list<std::vector<double>> _positivePoints):
	negativePoints_(createPointsVector(_negativePoints)),
	positivePoints_(createPointsVector(_positivePoints))
{
}

LogisticRegressionClassifier::~LogisticRegressionClassifier()
{
}

void LogisticRegressionClassifier::setPointsData(LogisticRegressionData& _data)
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

std::vector<std::vector<double>> LogisticRegressionClassifier::createPointsVector(std::list<std::vector<double>> _points)
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