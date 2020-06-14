#pragma once
#include <vector>
#include <list>

class PythonOutput
{
public:

	enum class Special
	{
		Endl
	};

	struct DataPoints
	{
		int pointCount;
		double* xValues;
		double* yValues;
		double* zValues;
	};

	PythonOutput(DataPoints &_dataPoints);
	~PythonOutput();

	PythonOutput& operator <<(int _value);
	PythonOutput& operator <<(std::vector<double> _value);
	PythonOutput& operator <<(double _value);
	PythonOutput& operator <<(Special _special);

	void setDataPoints();

private:

	DataPoints& dataPoints_;

	std::list<double> 
		xValues_,
		yValues_,
		zValues_;

};