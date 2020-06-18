#include "pythonMultyOutput.h"

PythonMultyOutput::PythonMultyOutput(DataPoints& _dataPoints, const size_t _lineCount) :
	dataPoints_(_dataPoints),
	lineCount_(_lineCount),
	currentLine_(0),
	xValuesLists_(lineCount_),
	yValuesLists_(lineCount_),
	zValuesLists_(lineCount_)
{
}

PythonMultyOutput::~PythonMultyOutput()
{
}

void PythonMultyOutput::setCurrentLine(const size_t _lineNumber)
{
	currentLine_ = _lineNumber;
}

PythonMultyOutput& PythonMultyOutput::operator<<(int _value)
{
	return *this;
}

PythonMultyOutput& PythonMultyOutput::operator<<(std::vector<double> _value)
{
	xValuesLists_[currentLine_].push_back(_value[0]);
	yValuesLists_[currentLine_].push_back(_value[1]);

	return *this;
}

PythonMultyOutput& PythonMultyOutput::operator<<(double _value)
{
	zValuesLists_[currentLine_].push_back(_value);

	return *this;
}

PythonMultyOutput& PythonMultyOutput::operator<<(Special _special)
{
	return *this;
}

void PythonMultyOutput::setDataPoints()
{
	int maxCount = 0;

	for (int n = 0; n < lineCount_; n++)
	{
		if (maxCount < xValuesLists_[n].size())
		{
			maxCount = xValuesLists_[n].size();
		}		
	}

	dataPoints_.allDataPointsCount = maxCount * lineCount_;

	dataPoints_.pointCounts = new int[lineCount_];
	dataPoints_.xValues = new double[dataPoints_.allDataPointsCount];
	dataPoints_.yValues = new double[dataPoints_.allDataPointsCount];
	dataPoints_.zValues = new double[dataPoints_.allDataPointsCount];

	dataPoints_.lineCount = lineCount_;
	
	int i = 0;
	for (int n = 0; n < lineCount_; n++)
	{
		const size_t pointCount = xValuesLists_[n].size();

		dataPoints_.pointCounts[n] = pointCount;

		auto xValuesItem = xValuesLists_[n].begin();
		auto yValuesItem = yValuesLists_[n].begin();
		auto zValuesItem = zValuesLists_[n].begin();

		for (; xValuesItem != xValuesLists_[n].end(); xValuesItem++, yValuesItem++, zValuesItem++, i++)
		{
			dataPoints_.xValues[i] = *xValuesItem;
			dataPoints_.yValues[i] = *yValuesItem;
			dataPoints_.zValues[i] = *zValuesItem;
		}		
	}
}