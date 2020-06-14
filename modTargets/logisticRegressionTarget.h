#pragma once

#include <vector>
#include <list>
#include "../modMatrix/matrix.h"

class LogisticRegressionTarget
{	
public:

	LogisticRegressionTarget(
		std::list<std::vector<double>> _negativePoints,
		std::list<std::vector<double>> _positivePoints,
		const double _regularization);
	~LogisticRegressionTarget();

	double target(std::vector<double> _coordinates);

	std::vector<double> gradient(std::vector<double> _coordinates);

	Matrix gessian(std::vector<double> _coordinates);

private:

	const double regularization_;

	std::vector<std::vector<double>> 
		negativePoints_,
		positivePoints_;

	static std::vector<std::vector<double>> createPointsVector(std::list<std::vector<double>> _points);

};