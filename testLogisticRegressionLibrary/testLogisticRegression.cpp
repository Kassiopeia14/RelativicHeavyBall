#define  MATHLIBRARY_EXPORTS 

#include "testLogisticRegression.h"

#include <random>

const int methodCount = 4;
LogisticRegressionClassifier logisticRegressionClassifier(methodCount);

MATHLIBRARY_API LogisticRegressionData* getLogisticRegressionData()
{
	return &(logisticRegressionClassifier.getLogisticRegressionData());
}

MATHLIBRARY_API PythonMultyOutput::DataPoints* logisticRegressionMulty(
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
	double _h)
{
	logisticRegressionClassifier.generateDistributions(_negativeX0, _negativeY0, _negativeSigmaX, _negativeSigmaY, _negativeCount, _positiveX0, _positiveY0, _positiveSigmaX, _positiveSigmaY, _positiveCount);
	logisticRegressionClassifier.setRegularization(_regularization);

	PythonMultyOutput::DataPoints &multyDataPoints = logisticRegressionClassifier.getMultyDataPoints();
	PythonMultyOutput pythonMultyOutput(multyDataPoints, methodCount);
	
	LogisticRegressionTarget& logisticRegressionTarget = logisticRegressionClassifier.getTarget();
	LogisticRegressionData& logisticRegressionData = logisticRegressionClassifier.getLogisticRegressionData();

	std::vector<double> initialData{ 0, _xStart, _yStart, 0, _xSpeedStart, _ySpeedStart };

	pythonMultyOutput.setCurrentLine(0);
	FastGradientDescent<LogisticRegressionTarget> fastGradientDescent(logisticRegressionTarget, _stepLimit, _targetAccuracy, _param, _useGradientHessian);
	RungeKutta<FastGradientDescent<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta0(fastGradientDescent, pythonMultyOutput, _h);
	std::vector<double> result0 = rungeKutta0.solve(initialData);
	logisticRegressionData.lineAParameters[0] = result0[1];
	logisticRegressionData.lineBParameters[0] = result0[2];
	logisticRegressionData.lineCParameters[0] = result0[0];

	pythonMultyOutput.setCurrentLine(1);
	HeavyBall<LogisticRegressionTarget> heavyBall(logisticRegressionTarget, _stepLimit, _targetAccuracy, _param, _useHavyBallHessian);
	RungeKutta<HeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta1(heavyBall, pythonMultyOutput, _h);
	std::vector<double> result1 = rungeKutta1.solve(initialData);
	logisticRegressionData.lineAParameters[1] = result1[1];
	logisticRegressionData.lineBParameters[1] = result1[2];
	logisticRegressionData.lineCParameters[1] = result1[0];

	pythonMultyOutput.setCurrentLine(2);
	PseudoRelativicHeavyBall<LogisticRegressionTarget> pseudoRelativicHeavyBall(logisticRegressionTarget, _stepLimit, _targetAccuracy, _param, _lightSpeed, _useHavyBallHessian);
	RungeKutta<PseudoRelativicHeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta2(pseudoRelativicHeavyBall, pythonMultyOutput, _h);
	std::vector<double> result2 = rungeKutta2.solve(initialData);
	logisticRegressionData.lineAParameters[2] = result2[1];
	logisticRegressionData.lineBParameters[2] = result2[2];
	logisticRegressionData.lineCParameters[2] = result2[0];

	pythonMultyOutput.setCurrentLine(3);
	RelativicHeavyBall<LogisticRegressionTarget> relativicHeavyBall(logisticRegressionTarget, _stepLimit, _targetAccuracy, _param, _lightSpeed, _useHavyBallHessian);
	RungeKutta<RelativicHeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta3(relativicHeavyBall, pythonMultyOutput, _h);
	std::vector<double> result3 = rungeKutta3.solve(initialData);
	logisticRegressionData.lineAParameters[3] = result3[1];
	logisticRegressionData.lineBParameters[3] = result3[2];
	logisticRegressionData.lineCParameters[3] = result3[0];

	pythonMultyOutput.setDataPoints();

	return &multyDataPoints;

}