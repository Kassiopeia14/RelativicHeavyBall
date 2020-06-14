#pragma once

#include <vector>
#include <list>
#include "../modMatrix/matrix.h"

struct LogisticRegressionData
{
	int negativePointCount;
	double* negativePointXValues;
	double* negativePointYValues;

	int positivePointCount;
	double* positivePointXValues;
	double* positivePointYValues;

	int lineCount;
	double* lineAParameters;
	double* lineBParameters;
	double* lineCParameters;
};

class LogisticRegressionClassifier
{
public:
	LogisticRegressionClassifier(
		std::list<std::vector<double>> _negativePoints,
		std::list<std::vector<double>> _positivePoints);

	~LogisticRegressionClassifier();

	void setPointsData(LogisticRegressionData& _data);

private:

	std::vector<std::vector<double>>
		negativePoints_,
		positivePoints_;

	static std::vector<std::vector<double>> createPointsVector(std::list<std::vector<double>> _points);

};


