#pragma once

#include <random>
#include <list>

#include "../modOutput/consoleOutput.h"
#include "../modOutput/pythonOutput.h"
#include "../modOutput/pythonMultyOutput.h"
#include "../modRungeKutta/rungeKutta.h"
#include "../modOptimizationMethods/heavyBall.h"
#include "../modOptimizationMethods/pseudoRelativicHeavyBall.h"
#include "../modOptimizationMethods/relativicHeavyBall.h"
#include "../modOptimizationMethods/gradientDescent.h"
#include "../modOptimizationMethods/fastGradientDescent.h"
#include "../modTargets/normTarget.h"
#include "../modTargets/washtubTarget.h"
#include "../modTargets/quadraticForm.h"
#include "../modTargets/logisticRegressionTarget.h"

class LogisticRegressionClassifier
{
public:
	LogisticRegressionClassifier(const size_t _methodCount);
	~LogisticRegressionClassifier();

	void generateDistributions(
		const double _negativeX0,
		const double _negativeY0,
		const double _negativeSigmaX,
		const double _negativeSigmaY,
		const size_t _negativeCount,
		const double _positiveX0,
		const double _positiveY0,
		const double _positiveSigmaX,
		const double _positiveSigmaY,
		const size_t _positiveCount);

	void setRegularization(const double _regularization);

	LogisticRegressionData& getLogisticRegressionData();
	PythonMultyOutput::DataPoints& getMultyDataPoints();
	LogisticRegressionTarget& getTarget();

private:

	const double pi = 3.141592653589793238462643383279502884;

	std::random_device rd_;

	std::ranlux48_base e2_;

	std::list<std::vector<double>>
		negativePoints_,
		positivePoints_;

	LogisticRegressionTarget logisticRegressionTarget_;
		
	PythonMultyOutput::DataPoints multyDataPoints_;

	LogisticRegressionData logisticRegressionData_;

	void generatePoints(std::list<std::vector<double>> &pointList, const double x0, const double y0, const double sigmaX, const double sigmaY, const size_t _count);
};

