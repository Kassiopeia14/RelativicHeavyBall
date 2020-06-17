#define  MATHLIBRARY_EXPORTS 

#include "pythonDLL.h"

const double pi = 3.141592653589793238462643383279502884;

std::random_device rd;

std::ranlux48_base e2(rd());

std::list<std::vector<double>> generatePoints(const double x0, const double y0, const double sigmaX, const double sigmaY, const size_t _count)
{
	std::list<std::vector<double>> points;

	std::uniform_real_distribution<> dist(0, 1);

	for (int i = 0; i < _count; i++)
	{
		const double
			u = dist(e2),
			v = dist(e2);

		const double
			l = sqrt(-2 * log(u)),
			c = cos(pi * v / 2),
			s = sqrt(1 - c * c),
			x = (rand() % 2 == 0 ? 1 : -1) * l * c,
			y = (rand() % 2 == 0 ? 1 : -1) * l * s;

		points.push_back({ x0 + sigmaX * x, y0 + sigmaY * y });
	}

	return points;
}

LogisticRegressionTarget lrTarget;

PythonOutput::DataPoints dataPoints;

PythonMultyOutput::DataPoints multyDataPoints;

LogisticRegressionData logisticRegressionData;

MATHLIBRARY_API double pythonNormTarget(double x, double y)
{
	std::vector<double> coordinates = { x, y };

	return NormTarget::target(coordinates);
}

MATHLIBRARY_API double pythonWashtubTarget(double x, double y)
{
	std::vector<double> coordinates = { x, y };

	return WashtubTarget::target(coordinates);
}

MATHLIBRARY_API double pythonQuadraticFormTarget(double x, double y)
{
	std::vector<double> coordinates = { x, y };

	Matrix formMatrix(2, 2);
	formMatrix(0, 0) = 1; 	formMatrix(1, 0) = 0;
	formMatrix(0, 1) = 2; 	formMatrix(1, 1) = 3;

	QuadraticForm quadraticForm(formMatrix);

	return quadraticForm.target(coordinates);
}

MATHLIBRARY_API double logisticRegressionTarget(double x, double y)
{
	std::vector<double> coordinates = { 0, x, y };

	return lrTarget.target(coordinates);
}

MATHLIBRARY_API LogisticRegressionData* getLogisticRegressionData()
{
	return &logisticRegressionData;
}

MATHLIBRARY_API PythonOutput::DataPoints* returnResult(
	double _xStart, 
	double _yStart, 
	double _xSpeedStart, 
	double _ySpeedStart,
	const size_t _stepLimit,
	const double _targetAccuracy,
	const double _param,
	const double _lightSpeed,
	const bool _useGradientHessian,
	const bool _useHavyBallHessian,
	const double _h)
{
	lrTarget.setRegularization(0.01);

	PythonOutput pythonOutput(dataPoints);

	WashtubTarget washtubTarget;

	HeavyBall<WashtubTarget> heavyBall(washtubTarget, _stepLimit, _targetAccuracy, _param, _useHavyBallHessian);

	RungeKutta<HeavyBall<WashtubTarget>, PythonOutput> rungeKutta(heavyBall, pythonOutput, _h);

	std::vector<double> initialData{ _xStart, _yStart, _xSpeedStart, _ySpeedStart };

	std::vector<double> result = rungeKutta.solve(initialData);

	pythonOutput.setDataPoints();

	return &dataPoints;
}

PythonMultyOutput::DataPoints* normMulty(
	double _xStart,
	double _yStart,
	double _xSpeedStart,
	double _ySpeedStart,
	const size_t _stepLimit,
	const double _targetAccuracy,
	const double _param,
	const double _lightSpeed,
	const bool _useGradientHessian,
	const bool _useHavyBallHessian,
	const double _h)
{
	PythonMultyOutput pythonMultyOutput(multyDataPoints, 4);

	NormTarget normTarget;
	std::vector<double> initialData{ _xStart, _yStart, _xSpeedStart, _ySpeedStart };

	pythonMultyOutput.setCurrentLine(0);
	FastGradientDescent<NormTarget> fastGradientDescent(normTarget, _stepLimit, _targetAccuracy, _param, _useGradientHessian);
	RungeKutta<FastGradientDescent<NormTarget>, PythonMultyOutput> rungeKutta0(fastGradientDescent, pythonMultyOutput, _h);
	rungeKutta0.solve(initialData);

	pythonMultyOutput.setCurrentLine(1);
	HeavyBall<NormTarget> heavyBall(normTarget, _stepLimit, _targetAccuracy, _param, _useHavyBallHessian);
	RungeKutta<HeavyBall<NormTarget>, PythonMultyOutput> rungeKutta1(heavyBall, pythonMultyOutput, _h);
	rungeKutta1.solve(initialData);

	pythonMultyOutput.setCurrentLine(2);
	RelativicHeavyBall<NormTarget> relativicHeavyBall(normTarget, _stepLimit, _targetAccuracy, _param, _lightSpeed, _useHavyBallHessian);
	RungeKutta<RelativicHeavyBall<NormTarget>, PythonMultyOutput> rungeKutta2(relativicHeavyBall, pythonMultyOutput, _h);
	rungeKutta2.solve(initialData);

	pythonMultyOutput.setCurrentLine(3);
	PseudoRelativicHeavyBall<NormTarget> pseudoRelativicHeavyBall(normTarget, _stepLimit, _targetAccuracy, _param, _lightSpeed, _useHavyBallHessian);
	RungeKutta<PseudoRelativicHeavyBall<NormTarget>, PythonMultyOutput> rungeKutta3(pseudoRelativicHeavyBall, pythonMultyOutput, _h);
	rungeKutta3.solve(initialData);

	pythonMultyOutput.setDataPoints();

	return &multyDataPoints;
}

PythonMultyOutput::DataPoints* washtubMulty(
	double _xStart,
	double _yStart,
	double _xSpeedStart,
	double _ySpeedStart,
	const size_t _stepLimit,
	const double _targetAccuracy,
	const double _param,
	const double _lightSpeed,
	const bool _useGradientHessian,
	const bool _useHavyBallHessian,
	const double _h)
{
	PythonMultyOutput pythonMultyOutput(multyDataPoints, 4);

	WashtubTarget washtubTarget;
	std::vector<double> initialData{ _xStart, _yStart, _xSpeedStart, _ySpeedStart };

	pythonMultyOutput.setCurrentLine(0);
	FastGradientDescent<WashtubTarget> fastGradientDescent(washtubTarget, _stepLimit, _targetAccuracy, _param, _useGradientHessian);
	RungeKutta<FastGradientDescent<WashtubTarget>, PythonMultyOutput> rungeKutta0(fastGradientDescent, pythonMultyOutput, _h);
	rungeKutta0.solve(initialData);

	pythonMultyOutput.setCurrentLine(1);
	HeavyBall<WashtubTarget> heavyBall(washtubTarget, _stepLimit, _targetAccuracy, _param, _useHavyBallHessian);
	RungeKutta<HeavyBall<WashtubTarget>, PythonMultyOutput> rungeKutta1(heavyBall, pythonMultyOutput, _h);
	rungeKutta1.solve(initialData);

	pythonMultyOutput.setCurrentLine(2);
	RelativicHeavyBall<WashtubTarget> relativicHeavyBall(washtubTarget, _stepLimit, _targetAccuracy, _param, _lightSpeed, _useHavyBallHessian);
	RungeKutta<RelativicHeavyBall<WashtubTarget>, PythonMultyOutput> rungeKutta2(relativicHeavyBall, pythonMultyOutput, _h);
	rungeKutta2.solve(initialData);

	pythonMultyOutput.setCurrentLine(3);
	PseudoRelativicHeavyBall<WashtubTarget> pseudoRelativicHeavyBall(washtubTarget, _stepLimit, _targetAccuracy, _param, _lightSpeed, _useHavyBallHessian);
	RungeKutta<PseudoRelativicHeavyBall<WashtubTarget>, PythonMultyOutput> rungeKutta3(pseudoRelativicHeavyBall, pythonMultyOutput, _h);
	rungeKutta3.solve(initialData);
	
	pythonMultyOutput.setDataPoints();

	return &multyDataPoints;
}

PythonMultyOutput::DataPoints* quadraticFormMulty(
	double _xStart,
	double _yStart,
	double _xSpeedStart,
	double _ySpeedStart,
	const size_t _stepLimit,
	const double _targetAccuracy,
	const double _param,
	const double _lightSpeed,
	const bool _useGradientHessian,
	const bool _useHavyBallHessian,
	const double _h)
{
	PythonMultyOutput pythonMultyOutput(multyDataPoints, 4);

	Matrix formMatrix(2, 2);
	formMatrix(0, 0) = 1; 	formMatrix(1, 0) = 0;
	formMatrix(0, 1) = 2; 	formMatrix(1, 1) = 3;

	QuadraticForm quadraticForm(formMatrix);
	std::vector<double> initialData{ _xStart, _yStart, _xSpeedStart, _ySpeedStart };

	pythonMultyOutput.setCurrentLine(0);
	FastGradientDescent<QuadraticForm> fastGradientDescent(quadraticForm, _stepLimit, _targetAccuracy, _param, _useGradientHessian);
	RungeKutta<FastGradientDescent<QuadraticForm>, PythonMultyOutput> rungeKutta0(fastGradientDescent, pythonMultyOutput, _h);
	rungeKutta0.solve(initialData);

	pythonMultyOutput.setCurrentLine(1);
	HeavyBall<QuadraticForm> heavyBall(quadraticForm, _stepLimit, _targetAccuracy, _param, _useHavyBallHessian);
	RungeKutta<HeavyBall<QuadraticForm>, PythonMultyOutput> rungeKutta1(heavyBall, pythonMultyOutput, _h);
	rungeKutta1.solve(initialData);

	pythonMultyOutput.setCurrentLine(2);
	RelativicHeavyBall<QuadraticForm> relativicHeavyBall(quadraticForm, _stepLimit, _targetAccuracy, _param, _lightSpeed, _useHavyBallHessian);
	RungeKutta<RelativicHeavyBall<QuadraticForm>, PythonMultyOutput> rungeKutta2(relativicHeavyBall, pythonMultyOutput, _h);
	rungeKutta2.solve(initialData);

	pythonMultyOutput.setCurrentLine(3);
	PseudoRelativicHeavyBall<QuadraticForm> pseudoRelativicHeavyBall(quadraticForm, _stepLimit, _targetAccuracy, _param, _lightSpeed, _useHavyBallHessian);
	RungeKutta<PseudoRelativicHeavyBall<QuadraticForm>, PythonMultyOutput> rungeKutta3(pseudoRelativicHeavyBall, pythonMultyOutput, _h);
	rungeKutta3.solve(initialData);
	
	pythonMultyOutput.setDataPoints();

	return &multyDataPoints;
}

PythonMultyOutput::DataPoints* logisticRegressionMulty(
	double _xStart,
	double _yStart,
	double _xSpeedStart,
	double _ySpeedStart,
	const size_t _stepLimit,
	const double _targetAccuracy,
	const double _param,
	const double _lightSpeed,
	const bool _useGradientHessian,
	const bool _useHavyBallHessian,
	const double _h)
{
	std::list<std::vector<double>>
		negativePoints(generatePoints(3.0, 3.0, 1.0, 1.0, 500)),
		positivePoints(generatePoints(6.0, 4.0, 5.0, 1.0, 500));

	/*
	negativePoints.push_back({ 0.0, 5.0 });
	negativePoints.push_back({ 1.0, 4.0 });
	negativePoints.push_back({ 2.0, 3.0 });
	negativePoints.push_back({ 3.0, 2.0 });
	negativePoints.push_back({ 4.0, 1.0 });

	positivePoints.push_back({ 0.0, 4.0 });
	positivePoints.push_back({ 1.0, 3.0 });
	positivePoints.push_back({ 2.0, 2.0 });
	positivePoints.push_back({ 3.0, 1.0 });
	positivePoints.push_back({ 4.0, 0.0 });*/

	/*negativePoints.push_back({ 1.0, 4.0 });
	negativePoints.push_back({ 2.0, 5.0 });
	negativePoints.push_back({ 3.0, 6.0 });
	negativePoints.push_back({ 4.0, 7.0 });

	positivePoints.push_back({ 2.0, 3.0 });
	positivePoints.push_back({ 3.0, 4.0 });
	positivePoints.push_back({ 4.0, 5.0 });
	positivePoints.push_back({ 5.0, 6.0 });
	positivePoints.push_back({ 6.0, 7.0 });*/
	/*
	negativePoints.push_back({ 1.0, 4.0 });
	negativePoints.push_back({ 2.0, 5.0 });
	negativePoints.push_back({ 3.0, 6.0 });
	negativePoints.push_back({ 4.0, 7.0 });

	positivePoints.push_back({ 1.0, 7.0 });
	positivePoints.push_back({ 4.0, 3.0 });
	positivePoints.push_back({ 5.0, 2.0 });
	positivePoints.push_back({ 6.0, 1.0 });
	positivePoints.push_back({ 7.0, 0.0 });

	negativePoints.push_back({ 1.0, 4.0 });
	negativePoints.push_back({ 2.0, 5.0 });
	negativePoints.push_back({ 3.0, 6.0 });
	negativePoints.push_back({ 4.0, 7.0 });
	negativePoints.push_back({ 7.0, 8.0 });
	negativePoints.push_back({ 8.0, 9.0 });
	negativePoints.push_back({ 9.0, 10.0 });
	negativePoints.push_back({ 10.0, 11.0 });

	positivePoints.push_back({ 2.0, 3.0 });
	positivePoints.push_back({ 3.0, 4.0 });
	positivePoints.push_back({ 4.0, 5.0 });
	positivePoints.push_back({ 5.0, 6.0 });
	positivePoints.push_back({ 6.0, 7.0 });
	*/

	lrTarget.setPoints(negativePoints, positivePoints);

	const int methodCount = 4;
	PythonMultyOutput pythonMultyOutput(multyDataPoints, methodCount);

	lrTarget.setPointsData(logisticRegressionData);
	logisticRegressionData.lineCount = methodCount;
	logisticRegressionData.lineAParameters = new double[methodCount];
	logisticRegressionData.lineBParameters = new double[methodCount];
	logisticRegressionData.lineCParameters = new double[methodCount];

	std::vector<double> initialData{ 0, _xStart, _yStart, 0, _xSpeedStart, _ySpeedStart };

	pythonMultyOutput.setCurrentLine(0);
	FastGradientDescent<LogisticRegressionTarget> fastGradientDescent(lrTarget, _stepLimit, _targetAccuracy, _param, _useGradientHessian);
	RungeKutta<FastGradientDescent<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta0(fastGradientDescent, pythonMultyOutput, _h);
	std::vector<double> result0 = rungeKutta0.solve(initialData);
	logisticRegressionData.lineAParameters[0] = result0[1];
	logisticRegressionData.lineBParameters[0] = result0[2];
	logisticRegressionData.lineCParameters[0] = result0[0];

	pythonMultyOutput.setCurrentLine(1);
	HeavyBall<LogisticRegressionTarget> heavyBall(lrTarget, _stepLimit, _targetAccuracy, _param, _useHavyBallHessian);
	RungeKutta<HeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta1(heavyBall, pythonMultyOutput, _h);
	std::vector<double> result1 = rungeKutta1.solve(initialData);
	logisticRegressionData.lineAParameters[1] = result1[1];
	logisticRegressionData.lineBParameters[1] = result1[2];
	logisticRegressionData.lineCParameters[1] = result1[0];

	pythonMultyOutput.setCurrentLine(2);
	PseudoRelativicHeavyBall<LogisticRegressionTarget> pseudoRelativicHeavyBall(lrTarget, _stepLimit, _targetAccuracy, _param, _lightSpeed, _useHavyBallHessian);
	RungeKutta<PseudoRelativicHeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta2(pseudoRelativicHeavyBall, pythonMultyOutput, _h);
	std::vector<double> result2 = rungeKutta2.solve(initialData);
	logisticRegressionData.lineAParameters[2] = result2[1];
	logisticRegressionData.lineBParameters[2] = result2[2];
	logisticRegressionData.lineCParameters[2] = result2[0];

	pythonMultyOutput.setCurrentLine(3);
	RelativicHeavyBall<LogisticRegressionTarget> relativicHeavyBall(lrTarget, _stepLimit, _targetAccuracy, _param, _lightSpeed, _useHavyBallHessian);
	RungeKutta<RelativicHeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta3(relativicHeavyBall, pythonMultyOutput, _h);
	std::vector<double> result3 = rungeKutta3.solve(initialData);
	logisticRegressionData.lineAParameters[3] = result3[1];
	logisticRegressionData.lineBParameters[3] = result3[2];
	logisticRegressionData.lineCParameters[3] = result3[0];

	pythonMultyOutput.setDataPoints();

	return &multyDataPoints;

}
