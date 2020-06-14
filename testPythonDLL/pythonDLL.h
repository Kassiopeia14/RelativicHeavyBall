#pragma once
#include "../modOutput/consoleOutput.h"
#include "../modOutput/pythonOutput.h"
#include "../modOutput/pythonMultyOutput.h"
#include "../modRungeKutta/rungeKutta.h"
#include "../modOptimizationMethods/heavyBall.h"
#include "../modOptimizationMethods/pseudoRelativicHeavyBall.h"
#include "../modOptimizationMethods/relativicHeavyBall.h"
#include "../modOptimizationMethods/gradientDescent.h"
#include "../modOptimizationMethods/nesterovGradientDescent.h"
#include "../modTargets/normTarget.h"
#include "../modTargets/washtubTarget.h"
#include "../modTargets/quadraticForm.h"
#include "../modTargets/logisticRegressionTarget.h"
#include "../modLogisticRegression/logisticRegressionClassifier.h"
#include <cstdlib>

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

extern "C" MATHLIBRARY_API PythonOutput::DataPoints * returnResult(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c);

extern "C" MATHLIBRARY_API PythonMultyOutput::DataPoints * normMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c, double aGD);

extern "C" MATHLIBRARY_API PythonMultyOutput::DataPoints * washtubMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c, double aGD);

extern "C" MATHLIBRARY_API PythonMultyOutput::DataPoints * quadraticFormMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c, double aGD);

extern "C" MATHLIBRARY_API PythonMultyOutput::DataPoints * logisticRegressionDiagonalMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c);

extern "C" MATHLIBRARY_API PythonMultyOutput::DataPoints * logisticRegression1WrongMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c, double aGD);

extern "C" MATHLIBRARY_API PythonMultyOutput::DataPoints * logisticRegressionMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c, double aGD);

extern "C" MATHLIBRARY_API PythonMultyOutput::DataPoints * logisticRegressionGalaxiesMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c, double aGD);