#pragma once

#include <vector>
#include "common.h"
#include "../modMatrix/matrix.h"

template<class Target>
class NesterovGradientDescent
{
public:

	NesterovGradientDescent(
		Target& _target,
		const size_t _stepLimit,
		const double _normAccuracy) :
		target_(_target),
		stepLimit_(_stepLimit),
		normAccuracy_(_normAccuracy)
	{
	}

	~NesterovGradientDescent()
	{
	}

	double result(const double _time, std::vector<double> _data) const
	{
		const size_t dimension = _data.size() / 2;

		std::vector<double>	coordinates(_data.begin(), _data.begin() + dimension);

		return target_.target(coordinates);
	}

	double target(std::vector<double> _coordinates) const
	{
		return target_.target(_coordinates);
	}

	std::vector<double> targetGradient(std::vector<double> _coordinates) const
	{
		return target_.gradient(_coordinates);
	}

	std::vector<double> calculateF(double _time, std::vector<double> _data) const
	{
		const size_t dimension = _data.size() / 2;

		std::vector<double>
			coordinates(_data.begin(), _data.begin() + dimension),
			velocities(_data.begin() + dimension, _data.end()),
			gradient(targetGradient(coordinates)),
			result(_data.size());

		Matrix targetGessian = target_.gessian(coordinates);

		std::vector<double> transformedGradient = targetGessian * gradient;

		const double dotProduct = transformedGradient * gradient;

		const double
			gradientNorm = norm(gradient),
			stepSize = gradientNorm * gradientNorm / dotProduct;

		auto resultItem = result.begin();
		auto gradientItem = gradient.begin();

		for (auto coordinatesItem = coordinates.begin(); coordinatesItem != coordinates.end(); coordinatesItem++, gradientItem++, resultItem++)
		{
			*resultItem -= stepSize * *gradientItem;
		}

		for (auto velocityItem = velocities.begin(); velocityItem != velocities.end(); velocityItem++, resultItem++)
		{
			*resultItem = 0;
		}

		return result;
	}

	bool stopCondition(size_t _stepNumber, std::vector<double> _newData, std::vector<double> _oldData) const
	{
		if (_stepNumber > stepLimit_)
		{
			return true;
		}

		const size_t dimension = _newData.size() / 2;

		std::vector<double>	coordinates(_newData.begin(), _newData.begin() + dimension);

		const double coordinatesNorm = norm(coordinates);

		return (coordinatesNorm < normAccuracy_);
	}

private:
	Target& target_;

	const size_t stepLimit_;

	const double normAccuracy_;
};