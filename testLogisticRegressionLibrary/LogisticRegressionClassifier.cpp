#include "LogisticRegressionClassifier.h"

LogisticRegressionClassifier::LogisticRegressionClassifier(const size_t _methodCount) :
	rd_(),
	e2_(rd_()),
	negativePoints_(),
	positivePoints_(),
	logisticRegressionTarget_(),
	multyDataPoints_(),
	logisticRegressionData_()
{	
	logisticRegressionData_.lineCount = _methodCount;
	logisticRegressionData_.lineAParameters = new double[_methodCount];
	logisticRegressionData_.lineBParameters = new double[_methodCount];
	logisticRegressionData_.lineCParameters = new double[_methodCount]; 
}

LogisticRegressionClassifier::~LogisticRegressionClassifier()
{
}

void LogisticRegressionClassifier::setRegularization(const double _regularization)
{
	logisticRegressionTarget_.setRegularization(_regularization);
}

void LogisticRegressionClassifier::generateDistributions(
	const double _negativeX0,
	const double _negativeY0,
	const double _negativeSigmaX,
	const double _negativeSigmaY,
	const size_t _negativeCount,
	const double _positiveX0,
	const double _positiveY0,
	const double _positiveSigmaX,
	const double _positiveSigmaY,
	const size_t _positiveCount)
{
	generatePoints(negativePoints_, _negativeX0, _negativeY0, _negativeSigmaX, _negativeSigmaY, _negativeCount);
	generatePoints(positivePoints_, _positiveX0, _positiveY0, _positiveSigmaX, _positiveSigmaY, _positiveCount);
	logisticRegressionTarget_.setPoints(negativePoints_, positivePoints_);
	logisticRegressionTarget_.setPointsData(logisticRegressionData_);
}

LogisticRegressionData& LogisticRegressionClassifier::getLogisticRegressionData()
{
	return logisticRegressionData_;
}

PythonMultyOutput::DataPoints& LogisticRegressionClassifier::getMultyDataPoints()
{
	return multyDataPoints_;
}

LogisticRegressionTarget& LogisticRegressionClassifier::getTarget()
{
	return logisticRegressionTarget_;
}

void LogisticRegressionClassifier::generatePoints(std::list<std::vector<double>> &pointList, const double x0, const double y0, const double sigmaX, const double sigmaY, const size_t _count)
{
	std::uniform_real_distribution<> dist(0, 1);

	for (int i = 0; i < _count; i++)
	{
		const double
			u = dist(e2_),
			v = dist(e2_);

		const double
			l = sqrt(-2 * log(u)),
			c = cos(pi * v / 2),
			s = sqrt(1 - c * c),
			x = (rand() % 2 == 0 ? 1 : -1) * l * c,
			y = (rand() % 2 == 0 ? 1 : -1) * l * s;

		pointList.push_back({ x0 + sigmaX * x, y0 + sigmaY * y });
	}

}