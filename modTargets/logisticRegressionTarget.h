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

class LogisticRegressionTarget
{	
public:

	LogisticRegressionTarget();
	~LogisticRegressionTarget();
	
	void setPoints(
		std::list<std::vector<double>> _negativePoints,
		std::list<std::vector<double>> _positivePoints);

	void setRegularization(const double _regularization);

	double target(std::vector<double> _coordinates);

	std::vector<double> gradient(std::vector<double> _coordinates);

	Matrix gessian(std::vector<double> _coordinates);

	void setPointsData(LogisticRegressionData& _data);

private:

	double regularization_;

	std::list<std::vector<double>> 
		negativePoints_,
		positivePoints_;

	static void addPoints(
		std::list<std::vector<double>>& _destination,
		std::list<std::vector<double>> _points);

};