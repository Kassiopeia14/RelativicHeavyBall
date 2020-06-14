#pragma once

#include <vector>

class TestF
{
public:

	TestF();
	~TestF();

	double result(const double _time, std::vector<double> _x) const;

	std::vector<double> calculateF(const double _time, std::vector<double> _x) const;

	bool stopCondition(size_t _stepNumber, std::vector<double> _newData, std::vector<double> _oldData) const;

private:

	double F(const double _t, const double _x) const;
	double exactSolution(const double _t) const;
};

