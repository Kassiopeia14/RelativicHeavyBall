#pragma once

#include <vector>
#include "common.h"
#include "../modMatrix/matrix.h"

template<class Target>
class PseudoRelativicHeavyBall
{
public:

	PseudoRelativicHeavyBall(
		Target& _target,
		const size_t _stepLimit,
		const double _targetAccuracy,
		const double _param,
		const double _lightSpeed,
		const bool _useHessian) :
		target_(_target),
		stepLimit_(_stepLimit),
		targetAccuracy_(_targetAccuracy),
		param_(_param),
		lightSpeed_(_lightSpeed),
		useHessian_(_useHessian)
	{
	}

	~PseudoRelativicHeavyBall()
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
		
		const double gradientNorm = norm(gradient);

		double stepSize = 1;// 1 / (1 + gradientNorm * gradientNorm);

		if (useHessian_)
		{
			Matrix targetGessian = target_.gessian(coordinates);

			std::vector<double> transformedGradient = targetGessian * gradient;

			const double dotProduct = transformedGradient * gradient;

			stepSize = stepSize * gradientNorm * gradientNorm / dotProduct;
		}

		const double
			speedNorm = norm(velocities),
			beta = speedNorm / lightSpeed_,
			relativicMultuiplier = sqrt(1 / (1 + beta * beta));

		auto resultItem = result.begin();

		for (auto velocityItem = velocities.begin(); velocityItem != velocities.end(); velocityItem++, resultItem++)
		{
			*resultItem = relativicMultuiplier * *velocityItem;
		}

		auto gradientItem = gradient.begin();

		for (auto velocityItem = velocities.begin(); velocityItem != velocities.end(); velocityItem++, gradientItem++, resultItem++)
		{
			*resultItem = -param_ * *velocityItem - stepSize * *gradientItem;
		}

		return result;
	}

	bool stopCondition(size_t _stepNumber, std::vector<double> _newData, std::vector<double> _oldData) const
	{
		if (_stepNumber > stepLimit_)
		{
			return true;
		}
		
		return false;
		
		/*
		const size_t dimension = _newData.size() / 2;

		std::vector<double>	coordinates(_newData.begin(), _newData.begin() + dimension);

		const double targetValue = target_.target(coordinates);

		return (targetValue < targetAccuracy_);
		*/
	}

private:
	Target& target_;

	const size_t stepLimit_;

	const double targetAccuracy_;

	const double param_;

	const double lightSpeed_;

	const bool useHessian_;
};