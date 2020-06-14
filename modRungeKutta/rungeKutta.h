#pragma once

#include <vector>
#include <iostream>

template<class MethodF, class Output> 
class RungeKutta
{
public:
	RungeKutta(
		MethodF& _methodF,
		Output& _output,
		const double _h) :
		methodF_(_methodF),
		output_(_output),
		h_(_h)
	{
	}

	~RungeKutta()
	{
	}

	std::vector<double> calculateF(double _time, std::vector<double> _data)
	{
		return methodF_.calculateF(_time, _data);
	}

	bool stopCondition(size_t _stepNumber, std::vector<double> _newData, std::vector<double> _oldData)
	{
		return methodF_.stopCondition(_stepNumber, _newData, _oldData);
	}

	std::vector<double> solve(std::vector<double> _initialData)
	{
		std::vector<double>
			data(_initialData),
			newData(_initialData);

		int stepNumber = 0;

		do
		{
			data = newData;

			/*if(stepNumber % 1000 == 0)*/ output_ << stepNumber << newData << methodF_.result(stepNumber * h_, newData) << Output::Special::Endl;

			newData = step(stepNumber * h_, data);

		} while (!stopCondition(stepNumber++, newData, data));

		output_ << stepNumber << newData << methodF_.result(stepNumber * h_, newData) << Output::Special::Endl;

		return newData;
	}

private:

	MethodF& methodF_;

	Output& output_;

	const double h_;

	std::vector<double> step(double _time, std::vector<double> _initialData)
	{
		std::vector<double>	data(_initialData);

		std::vector<double> k1(calculateF(_time, data));

		auto k1Item = k1.begin();
		auto initialDataItem = _initialData.begin();
		for (auto dataItem = data.begin(); dataItem != data.end(); initialDataItem++, k1Item++, dataItem++)
		{
			*dataItem = *initialDataItem + *k1Item * h_ / 2;
		}

		std::vector<double> k2(calculateF(_time + h_ / 2, data));

		auto k2Item = k2.begin();
		initialDataItem = _initialData.begin();
		for (auto dataItem = data.begin(); dataItem != data.end(); initialDataItem++, k2Item++, dataItem++)
		{
			*dataItem = *initialDataItem + *k2Item * h_ / 2;
		}

		std::vector<double> k3(calculateF(_time + h_ / 2, data));

		auto k3Item = k3.begin();
		initialDataItem = _initialData.begin();
		for (auto dataItem = data.begin(); dataItem != data.end(); initialDataItem++, k3Item++, dataItem++)
		{
			*dataItem = *initialDataItem + *k3Item * h_;
		}

		std::vector<double> k4(calculateF(_time + h_, data));

		k1Item = k1.begin();
		k2Item = k2.begin();
		k3Item = k3.begin();
		auto k4Item = k4.begin();
		initialDataItem = _initialData.begin();
		for (auto dataItem = data.begin(); dataItem != data.end(); initialDataItem++, k1Item++, k2Item++, k3Item++, k4Item++, dataItem++)
		{
			*dataItem = *initialDataItem + h_ * (*k1Item + 2 * *k2Item + 2 * *k3Item + *k4Item) / 6;
		}

		return data;
	}
};