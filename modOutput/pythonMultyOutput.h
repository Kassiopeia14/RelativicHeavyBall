#pragma once
#include <vector>
#include <list>

class PythonMultyOutput
{
public:

	enum class Special
	{
		Endl
	};

	struct DataPoints
	{
		int lineCount;
		int allDataPointsCount;
		int* pointCounts;
		double* xValues;
		double* yValues;
		double* zValues;
	};

	PythonMultyOutput(DataPoints& _dataPoints, const size_t _lineCount);
	~PythonMultyOutput();

	void setCurrentLine(const size_t _lineNumber);

	PythonMultyOutput& operator <<(int _value);
	PythonMultyOutput& operator <<(std::vector<double> _value);
	PythonMultyOutput& operator <<(double _value);
	PythonMultyOutput& operator <<(Special _special);

	void setDataPoints();

private:

	DataPoints& dataPoints_;

	const size_t lineCount_;
	size_t currentLine_;

	std::vector<std::list<double>>
		xValuesLists_,
		yValuesLists_,
		zValuesLists_;
};