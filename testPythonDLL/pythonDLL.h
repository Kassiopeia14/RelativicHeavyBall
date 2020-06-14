#pragma once

#include <random>

#include "../modOutput/consoleOutput.h"
#include "../modOutput/pythonOutput.h"
#include "../modOutput/pythonMultyOutput.h"
#include "../modRungeKutta/rungeKutta.h"
#include "../modOptimizationMethods/heavyBall.h"
#include "../modOptimizationMethods/pseudoRelativicHeavyBall.h"
#include "../modOptimizationMethods/relativicHeavyBall.h"
#include "../modOptimizationMethods/gradientDescent.h"
#include "../modOptimizationMethods/fastGradientDescent.h"
#include "../modTargets/normTarget.h"
#include "../modTargets/washtubTarget.h"
#include "../modTargets/quadraticForm.h"
#include "../modTargets/logisticRegressionTarget.h"

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

extern "C" MATHLIBRARY_API double pythonNormTarget(double x, double y);

extern "C" MATHLIBRARY_API double pythonWashtubTarget(double x, double y);

extern "C" MATHLIBRARY_API double pythonQuadraticFormTarget(double x, double y);

extern "C" MATHLIBRARY_API double logisticRegressionTarget(double x, double y);

extern "C" MATHLIBRARY_API LogisticRegressionData* getLogisticRegressionData();

extern "C" MATHLIBRARY_API PythonOutput::DataPoints * returnResult(
	double _xStart,
	double _yStart,
	double _xSpeedStart,
	double _ySpeedStart,
	const size_t _stepLimit,
	const double _targetAccuracy,
	const double _param,
	const double _lightSpeed,
	const bool _useHessian,
	const double _h);

extern "C" MATHLIBRARY_API PythonMultyOutput::DataPoints * normMulty(
	double _xStart,
	double _yStart,
	double _xSpeedStart,
	double _ySpeedStart,
	const size_t _stepLimit,
	const double _targetAccuracy,
	const double _param,
	const double _lightSpeed,
	const bool _useHessian,
	const double _h);

extern "C" MATHLIBRARY_API PythonMultyOutput::DataPoints * washtubMulty(
	double _xStart,
	double _yStart,
	double _xSpeedStart,
	double _ySpeedStart,
	const size_t _stepLimit,
	const double _targetAccuracy,
	const double _param,
	const double _lightSpeed,
	const bool _useHessian,
	const double _h);

extern "C" MATHLIBRARY_API PythonMultyOutput::DataPoints * quadraticFormMulty(
	double _xStart,
	double _yStart,
	double _xSpeedStart,
	double _ySpeedStart,
	const size_t _stepLimit,
	const double _targetAccuracy,
	const double _param,
	const double _lightSpeed,
	const bool _useHessian,
	const double _h);

extern "C" MATHLIBRARY_API PythonMultyOutput::DataPoints * logisticRegressionMulty(
	double _xStart,
	double _yStart,
	double _xSpeedStart,
	double _ySpeedStart,
	const size_t _stepLimit,
	const double _targetAccuracy,
	const double _param,
	const double _lightSpeed,
	const bool _useHessian,
	const double _h);