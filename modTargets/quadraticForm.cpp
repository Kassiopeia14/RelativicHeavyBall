#include "quadraticForm.h"

QuadraticForm::QuadraticForm(Matrix _formMatrix):
	formMatrix_(_formMatrix)
{
}

QuadraticForm::~QuadraticForm()
{
}

double QuadraticForm::target(std::vector<double> _coordinates)
{
	return _coordinates * (formMatrix_ * _coordinates);
}

std::vector<double> QuadraticForm::gradient(std::vector<double> _coordinates)
{
	return 2 * (formMatrix_ *_coordinates);
}

Matrix QuadraticForm::gessian(std::vector<double> _coordinates)
{
	return 2 * formMatrix_;
}
