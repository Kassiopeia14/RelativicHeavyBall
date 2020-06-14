#include "pythonOutput.h"

PythonOutput::PythonOutput(DataPoints& _dataPoints):
	dataPoints_(_dataPoints),
	xValues_(),
	yValues_(),
	zValues_()
{
}

PythonOutput::~PythonOutput()
{
}

PythonOutput& PythonOutput::operator<<(int _value)
{
	return *this;
}

PythonOutput& PythonOutput::operator<<(std::vector<double> _value)
{
	xValues_.push_back(_value[0]);
	yValues_.push_back(_value[1]);

	return *this;
}

PythonOutput& PythonOutput::operator<<(double _value)
{
	zValues_.push_back(_value);

	return *this;
}

PythonOutput& PythonOutput::operator<<(Special _special)
{
	return *this;
}

void PythonOutput::setDataPoints()
{
	const size_t pointCount = xValues_.size();

	dataPoints_.pointCount = pointCount;
	dataPoints_.xValues = new double[pointCount];
	dataPoints_.yValues = new double[pointCount];
	dataPoints_.zValues = new double[pointCount];

	int i = 0;
	for (auto xValuesItem = xValues_.begin(); xValuesItem != xValues_.end(); xValuesItem++, i++)
	{
		dataPoints_.xValues[i] = *xValuesItem;
	}

	i = 0;
	for (auto yValuesItem = yValues_.begin(); yValuesItem != yValues_.end(); yValuesItem++, i++)
	{
		dataPoints_.yValues[i] = *yValuesItem;
	}
	
	i = 0;
	for (auto zValuesItem = zValues_.begin(); zValuesItem != zValues_.end(); zValuesItem++, i++)
	{
		dataPoints_.zValues[i] = *zValuesItem;
	}
}