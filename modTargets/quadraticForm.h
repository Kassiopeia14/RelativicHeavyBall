#pragma once

#include <vector>
#include "../modMatrix/matrix.h"

class QuadraticForm
{
public:

	QuadraticForm(Matrix _formMatrix);
	~QuadraticForm();

	double target(std::vector<double> _coordinates);
	
	std::vector<double> gradient(std::vector<double> _coordinates);

	Matrix gessian(std::vector<double> _coordinates);

private:

	Matrix formMatrix_;
};