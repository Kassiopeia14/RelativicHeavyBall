#pragma once

#include "LogisticRegressionClassifier.h"

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

extern "C" MATHLIBRARY_API LogisticRegressionData * getLogisticRegressionData();

extern "C" MATHLIBRARY_API PythonMultyOutput::DataPoints * logisticRegressionMulty(
	double _negativeX0,
	double _negativeY0,
	double _negativeSigmaX,
	double _negativeSigmaY,
	int _negativeCount,
	double _positiveX0,
	double _positiveY0,
	double _positiveSigmaX,
	double _positiveSigmaY,
	int _positiveCount,
	double _regularization,
	double _xStart,
	double _yStart,
	double _xSpeedStart,
	double _ySpeedStart,
	int _stepLimit,
	double _targetAccuracy,
	double _param,
	double _lightSpeed,
	bool _useGradientHessian,
	bool _useHavyBallHessian,
	double _h);