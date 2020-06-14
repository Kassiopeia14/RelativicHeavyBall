#include "matrix.h"

Matrix::Matrix(
	const size_t _columnCount,
	const size_t _rowCount) :
	columnCount_(_columnCount),
	rowCount_(_rowCount),
	elements_(columnCount_* rowCount_)
{
}

Matrix::~Matrix()
{
}

size_t Matrix::getColumnCount() const
{
	return columnCount_;
}

size_t Matrix::getRowCount() const
{
	return rowCount_;
}

double& Matrix::operator() (
	const size_t _column,
	const size_t _row)
{
	return elements_[columnCount_ * _row + _column];
}

double Matrix::operator() (
	const size_t _column,
	const size_t _row) const
{
	return elements_[columnCount_ * _row + _column];
}

std::vector<double> operator* (Matrix _first, std::vector<double> _second)
{
	const int
		rowCount = (const int)_first.getRowCount(),
		productCount = (const int)_first.getColumnCount();

	std::vector<double> result(rowCount);

	for (int j = 0; j < rowCount; j++)
	{
		double sum = 0;
		for (int k = 0; k < productCount; k++)
		{
			sum += _first(k, j) * _second[k];
		}

		result[j] = sum;
	}

	return result;
}

Matrix operator*(double _first, Matrix _second)
{
	const int
		rowCount = (const int)_second.getRowCount(),
		columnCount = (const int)_second.getColumnCount();

	Matrix result(columnCount, rowCount);

	for (int j = 0; j < columnCount; j++)
	{
		for (int k = 0; k < rowCount; k++)
		{
			result(j, k) = _first * _second(j, k);
		}
	}

	return result;
}

double operator*(std::vector<double> _first, std::vector<double> _second)
{
	double result = 0;
	auto secondItem = _second.begin();

	for (auto firstItem = _first.begin(); firstItem != _first.end(); firstItem++, secondItem++)
	{
		result += *firstItem * *secondItem;
	}

	return result;
}

std::vector<double> operator*(double _first, std::vector<double> _second)
{
	std::vector<double> result(_second.size());

	auto resultItem = result.begin();
	for (auto secondItem = _second.begin(); secondItem != _second.end(); secondItem++, resultItem++)
	{
		*resultItem = _first * *secondItem;
	}

	return result;
}
