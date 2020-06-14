#define MATHLIBRARY_EXPORTS

#include "pythonDLL.h"

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

	std::list<std::vector<double>>
		negativePoints,
		positivePoints;

	negativePoints.push_back({ 0.0, 5.0 });
	negativePoints.push_back({ 1.0, 4.0 });
	negativePoints.push_back({ 2.0, 3.0 });
	negativePoints.push_back({ 3.0, 2.0 });
	negativePoints.push_back({ 4.0, 1.0 });

	positivePoints.push_back({ 0.0, 4.0 });
	positivePoints.push_back({ 1.0, 3.0 });
	positivePoints.push_back({ 2.0, 2.0 });
	positivePoints.push_back({ 3.0, 1.0 });
	positivePoints.push_back({ 4.0, 0.0 });

	LogisticRegressionTarget logisticRegressionTarget(negativePoints, positivePoints, 0.01);

	return logisticRegressionTarget.target(coordinates);
}

MATHLIBRARY_API LogisticRegressionData* getLogisticRegressionData()
{
	return &logisticRegressionData;
}

MATHLIBRARY_API PythonOutput::DataPoints* returnResult(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c)
{
	PythonOutput pythonOutput(dataPoints);

	WashtubTarget washtubTarget;

	HeavyBall<WashtubTarget> heavyBall(washtubTarget, stepLimit, accuracy, a);

	RungeKutta<HeavyBall<WashtubTarget>, PythonOutput> rungeKutta(heavyBall, pythonOutput, h);

	std::vector<double> initialData{ xStart, yStart, xVelocityStart, yVelocityStart };

	std::vector<double> result = rungeKutta.solve(initialData);

	pythonOutput.setDataPoints();

	return &dataPoints;
}

MATHLIBRARY_API PythonMultyOutput::DataPoints* normMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c, double aGD)
{
	PythonMultyOutput pythonMultyOutput(multyDataPoints, 4);

	NormTarget normTarget;
	std::vector<double> initialData{ xStart, yStart, xVelocityStart, yVelocityStart };

	pythonMultyOutput.setCurrentLine(0);
	HeavyBall<NormTarget> heavyBall(normTarget, stepLimit, accuracy, a);
	RungeKutta<HeavyBall<NormTarget>, PythonMultyOutput> rungeKutta1(heavyBall, pythonMultyOutput, h);
	rungeKutta1.solve(initialData);

	pythonMultyOutput.setCurrentLine(1);
	GradientDescent<NormTarget> gradientDescent(normTarget, stepLimit, accuracy, aGD);
	RungeKutta<GradientDescent<NormTarget>, PythonMultyOutput> rungeKutta2(gradientDescent, pythonMultyOutput, h);
	rungeKutta2.solve(initialData);

	pythonMultyOutput.setCurrentLine(2);
	PseudoRelativicHeavyBall<NormTarget> pseudoRelativicHeavyBall(normTarget, stepLimit, accuracy, a, c);
	RungeKutta<PseudoRelativicHeavyBall<NormTarget>, PythonMultyOutput> rungeKutta3(pseudoRelativicHeavyBall, pythonMultyOutput, h);
	rungeKutta3.solve(initialData);

	pythonMultyOutput.setCurrentLine(3);
	NesterovGradientDescent<NormTarget> nesterovGradientDescent(normTarget, stepLimit, accuracy);
	RungeKutta<NesterovGradientDescent<NormTarget>, PythonMultyOutput> rungeKutta4(nesterovGradientDescent, pythonMultyOutput, h);
	rungeKutta4.solve(initialData);

	pythonMultyOutput.setDataPoints();

	return &multyDataPoints;
}

MATHLIBRARY_API PythonMultyOutput::DataPoints* washtubMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c, double aGD)
{
	PythonMultyOutput pythonMultyOutput(multyDataPoints, 4);

	WashtubTarget washtubTarget;
	std::vector<double> initialData{ xStart, yStart, xVelocityStart, yVelocityStart };
		
	pythonMultyOutput.setCurrentLine(0);
	HeavyBall<WashtubTarget> heavyBall(washtubTarget, stepLimit, accuracy, a);
	RungeKutta<HeavyBall<WashtubTarget>, PythonMultyOutput> rungeKutta1(heavyBall, pythonMultyOutput, h);
	rungeKutta1.solve(initialData);

	pythonMultyOutput.setCurrentLine(1);
	GradientDescent<WashtubTarget> gradientDescent(washtubTarget, stepLimit, accuracy, aGD);
	RungeKutta<GradientDescent<WashtubTarget>, PythonMultyOutput> rungeKutta2(gradientDescent, pythonMultyOutput, h);
	rungeKutta2.solve(initialData);

	pythonMultyOutput.setCurrentLine(2);
	PseudoRelativicHeavyBall<WashtubTarget> pseudoRelativicHeavyBall(washtubTarget, stepLimit, accuracy, a, c);
	RungeKutta<PseudoRelativicHeavyBall<WashtubTarget>, PythonMultyOutput> rungeKutta3(pseudoRelativicHeavyBall, pythonMultyOutput, h);
	rungeKutta3.solve(initialData);
	
	pythonMultyOutput.setCurrentLine(3);
	NesterovGradientDescent<WashtubTarget> nesterovGradientDescent(washtubTarget, stepLimit, accuracy);
	RungeKutta<NesterovGradientDescent<WashtubTarget>, PythonMultyOutput> rungeKutta4(nesterovGradientDescent, pythonMultyOutput, h);
	rungeKutta4.solve(initialData);

	pythonMultyOutput.setDataPoints();

	return &multyDataPoints;
}

MATHLIBRARY_API PythonMultyOutput::DataPoints* quadraticFormMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c, double aGD)
{
	PythonMultyOutput pythonMultyOutput(multyDataPoints, 4);

	Matrix formMatrix(2, 2);
	formMatrix(0, 0) = 1; 	formMatrix(1, 0) = 0;
	formMatrix(0, 1) = 2; 	formMatrix(1, 1) = 3;

	QuadraticForm quadraticForm(formMatrix);
	std::vector<double> initialData{ xStart, yStart, xVelocityStart, yVelocityStart };

	pythonMultyOutput.setCurrentLine(0);
	HeavyBall<QuadraticForm> heavyBall(quadraticForm, stepLimit, accuracy, a);
	RungeKutta<HeavyBall<QuadraticForm>, PythonMultyOutput> rungeKutta1(heavyBall, pythonMultyOutput, h);
	rungeKutta1.solve(initialData);

	pythonMultyOutput.setCurrentLine(1);
	GradientDescent<QuadraticForm> gradientDescent(quadraticForm, stepLimit, accuracy, aGD);
	RungeKutta<GradientDescent<QuadraticForm>, PythonMultyOutput> rungeKutta2(gradientDescent, pythonMultyOutput, h);
	rungeKutta2.solve(initialData);

	pythonMultyOutput.setCurrentLine(2);
	PseudoRelativicHeavyBall<QuadraticForm> pseudoRelativicHeavyBall(quadraticForm, stepLimit, accuracy, a, c);
	RungeKutta<PseudoRelativicHeavyBall<QuadraticForm>, PythonMultyOutput> rungeKutta3(pseudoRelativicHeavyBall, pythonMultyOutput, h);
	rungeKutta3.solve(initialData);

	pythonMultyOutput.setCurrentLine(3);
	NesterovGradientDescent<QuadraticForm> nesterovGradientDescent(quadraticForm, stepLimit, accuracy);
	RungeKutta<NesterovGradientDescent<QuadraticForm>, PythonMultyOutput> rungeKutta4(nesterovGradientDescent, pythonMultyOutput, h);
	rungeKutta4.solve(initialData);

	pythonMultyOutput.setDataPoints();

	return &multyDataPoints;
}

MATHLIBRARY_API PythonMultyOutput::DataPoints* logisticRegressionDiagonalMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c)
{
	const int methodCount = 4;
	PythonMultyOutput pythonMultyOutput(multyDataPoints, methodCount);

	std::list<std::vector<double>>
		negativePoints,
		positivePoints;
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
	
	negativePoints.push_back({ 1.0, 4.0 });
	negativePoints.push_back({ 2.0, 5.0 });
	negativePoints.push_back({ 3.0, 6.0 });
	negativePoints.push_back({ 4.0, 7.0 });

	positivePoints.push_back({ 1.0, 7.0 });
	positivePoints.push_back({ 4.0, 3.0 });
	positivePoints.push_back({ 5.0, 2.0 });
	positivePoints.push_back({ 6.0, 1.0 });
	positivePoints.push_back({ 7.0, 0.0 });
	
	LogisticRegressionClassifier logisticRegressionClassifier(negativePoints, positivePoints);
	logisticRegressionClassifier.setPointsData(logisticRegressionData);
	logisticRegressionData.lineCount = methodCount;
	logisticRegressionData.lineAParameters = new double[methodCount];
	logisticRegressionData.lineBParameters = new double[methodCount];
	logisticRegressionData.lineCParameters = new double[methodCount];

	LogisticRegressionTarget logisticRegressionTarget(negativePoints, positivePoints, 0.01);

	std::vector<double> initialData{ 0, xStart, yStart, 0, xVelocityStart, yVelocityStart };

	pythonMultyOutput.setCurrentLine(0);
	HeavyBall<LogisticRegressionTarget> heavyBall(logisticRegressionTarget, stepLimit, accuracy, a);
	RungeKutta<HeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta1(heavyBall, pythonMultyOutput, h);
	std::vector<double> result1 = rungeKutta1.solve(initialData);
	logisticRegressionData.lineAParameters[0] = result1[1];
	logisticRegressionData.lineBParameters[0] = result1[2];
	logisticRegressionData.lineCParameters[0] = result1[0];

	pythonMultyOutput.setCurrentLine(1);
	RelativicHeavyBall<LogisticRegressionTarget> relativicHeavyBall(logisticRegressionTarget, stepLimit, accuracy, a, c);
	RungeKutta<RelativicHeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta2(relativicHeavyBall, pythonMultyOutput, h);
	std::vector<double> result2 = rungeKutta2.solve(initialData);
	logisticRegressionData.lineAParameters[1] = result2[1];
	logisticRegressionData.lineBParameters[1] = result2[2];
	logisticRegressionData.lineCParameters[1] = result2[0];

	pythonMultyOutput.setCurrentLine(2);
	PseudoRelativicHeavyBall<LogisticRegressionTarget> pseudoRelativicHeavyBall(logisticRegressionTarget, stepLimit, accuracy, a, c);
	RungeKutta<PseudoRelativicHeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta3(pseudoRelativicHeavyBall, pythonMultyOutput, h);
	std::vector<double> result3 = rungeKutta3.solve(initialData);
	logisticRegressionData.lineAParameters[2] = result3[1];
	logisticRegressionData.lineBParameters[2] = result3[2];
	logisticRegressionData.lineCParameters[2] = result3[0];

	pythonMultyOutput.setCurrentLine(3);
	NesterovGradientDescent<LogisticRegressionTarget> nesterovGradientDescent(logisticRegressionTarget, stepLimit, accuracy);
	RungeKutta<NesterovGradientDescent<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta4(nesterovGradientDescent, pythonMultyOutput, h);
	std::vector<double> result4 = rungeKutta4.solve(initialData);
	logisticRegressionData.lineAParameters[3] = result4[1];
	logisticRegressionData.lineBParameters[3] = result4[2];
	logisticRegressionData.lineCParameters[3] = result4[0];

	pythonMultyOutput.setDataPoints();

	return &multyDataPoints;

}

MATHLIBRARY_API PythonMultyOutput::DataPoints* logisticRegression1WrongMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c, double aGD)
{
	const int methodCount = 4;
	PythonMultyOutput pythonMultyOutput(multyDataPoints, methodCount);

	std::list<std::vector<double>>
		negativePoints,
		positivePoints;
	
	negativePoints.push_back({ 0.0, 5.0 });
	negativePoints.push_back({ 1.0, 4.0 });
	negativePoints.push_back({ 2.0, 3.0 });
	negativePoints.push_back({ 3.0, 2.0 });
	negativePoints.push_back({ 4.0, 1.0 });

	positivePoints.push_back({ 0.0, 4.0 });
	positivePoints.push_back({ 1.0, 3.0 });
	positivePoints.push_back({ 2.0, 2.0 });
	positivePoints.push_back({ 3.0, 1.0 });
	positivePoints.push_back({ 4.0, 0.0 });

	LogisticRegressionClassifier logisticRegressionClassifier(negativePoints, positivePoints);
	logisticRegressionClassifier.setPointsData(logisticRegressionData);
	logisticRegressionData.lineCount = methodCount;
	logisticRegressionData.lineAParameters = new double[methodCount];
	logisticRegressionData.lineBParameters = new double[methodCount];
	logisticRegressionData.lineCParameters = new double[methodCount];

	LogisticRegressionTarget logisticRegressionTarget(negativePoints, positivePoints, 0.01);

	std::vector<double> initialData{ 0, xStart, yStart, 0, xVelocityStart, yVelocityStart };

	pythonMultyOutput.setCurrentLine(0);
	HeavyBall<LogisticRegressionTarget> heavyBall(logisticRegressionTarget, stepLimit, accuracy, a);
	RungeKutta<HeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta1(heavyBall, pythonMultyOutput, h);
	std::vector<double> result1 = rungeKutta1.solve(initialData);
	logisticRegressionData.lineAParameters[0] = result1[1];
	logisticRegressionData.lineBParameters[0] = result1[2];
	logisticRegressionData.lineCParameters[0] = result1[0];

	pythonMultyOutput.setCurrentLine(1);
	GradientDescent<LogisticRegressionTarget> gradientDescent(logisticRegressionTarget, stepLimit, accuracy, aGD);
	RungeKutta<GradientDescent<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta2(gradientDescent, pythonMultyOutput, h);
	std::vector<double> result2 = rungeKutta2.solve(initialData);
	logisticRegressionData.lineAParameters[1] = result2[1];
	logisticRegressionData.lineBParameters[1] = result2[2];
	logisticRegressionData.lineCParameters[1] = result2[0];

	pythonMultyOutput.setCurrentLine(2);
	PseudoRelativicHeavyBall<LogisticRegressionTarget> pseudoRelativicHeavyBall(logisticRegressionTarget, stepLimit, accuracy, a, c);
	RungeKutta<PseudoRelativicHeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta3(pseudoRelativicHeavyBall, pythonMultyOutput, h);
	std::vector<double> result3 = rungeKutta3.solve(initialData);
	logisticRegressionData.lineAParameters[2] = result3[1];
	logisticRegressionData.lineBParameters[2] = result3[2];
	logisticRegressionData.lineCParameters[2] = result3[0];

	pythonMultyOutput.setCurrentLine(3);
	NesterovGradientDescent<LogisticRegressionTarget> nesterovGradientDescent(logisticRegressionTarget, stepLimit, accuracy);
	RungeKutta<NesterovGradientDescent<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta4(nesterovGradientDescent, pythonMultyOutput, h);
	std::vector<double> result4 = rungeKutta4.solve(initialData);
	logisticRegressionData.lineAParameters[3] = result4[1];
	logisticRegressionData.lineBParameters[3] = result4[2];
	logisticRegressionData.lineCParameters[3] = result4[0];

	pythonMultyOutput.setDataPoints();

	return &multyDataPoints;

}

MATHLIBRARY_API PythonMultyOutput::DataPoints* logisticRegressionMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c, double aGD)
{
	const int methodCount = 4;
	PythonMultyOutput pythonMultyOutput(multyDataPoints, methodCount);

	std::list<std::vector<double>>
		negativePoints,
		positivePoints;
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

	negativePoints.push_back({ 1.0, 4.0 });
	negativePoints.push_back({ 2.0, 5.0 });
	negativePoints.push_back({ 3.0, 6.0 });
	negativePoints.push_back({ 4.0, 7.0 });

	positivePoints.push_back({ 1.0, 7.0 });
	positivePoints.push_back({ 4.0, 3.0 });
	positivePoints.push_back({ 5.0, 2.0 });
	positivePoints.push_back({ 6.0, 1.0 });
	positivePoints.push_back({ 7.0, 0.0 });

	LogisticRegressionClassifier logisticRegressionClassifier(negativePoints, positivePoints);
	logisticRegressionClassifier.setPointsData(logisticRegressionData);
	logisticRegressionData.lineCount = methodCount;
	logisticRegressionData.lineAParameters = new double[methodCount];
	logisticRegressionData.lineBParameters = new double[methodCount];
	logisticRegressionData.lineCParameters = new double[methodCount];

	LogisticRegressionTarget logisticRegressionTarget(negativePoints, positivePoints, 0.01);

	std::vector<double> initialData{ 0, xStart, yStart, 0, xVelocityStart, yVelocityStart };

	pythonMultyOutput.setCurrentLine(0);
	HeavyBall<LogisticRegressionTarget> heavyBall(logisticRegressionTarget, stepLimit, accuracy, a);
	RungeKutta<HeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta1(heavyBall, pythonMultyOutput, h);
	std::vector<double> result1 = rungeKutta1.solve(initialData);
	logisticRegressionData.lineAParameters[0] = result1[1];
	logisticRegressionData.lineBParameters[0] = result1[2];
	logisticRegressionData.lineCParameters[0] = result1[0];

	pythonMultyOutput.setCurrentLine(1);
	GradientDescent<LogisticRegressionTarget> gradientDescent(logisticRegressionTarget, stepLimit, accuracy, aGD);
	RungeKutta<GradientDescent<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta2(gradientDescent, pythonMultyOutput, h);
	std::vector<double> result2 = rungeKutta2.solve(initialData);
	logisticRegressionData.lineAParameters[1] = result2[1];
	logisticRegressionData.lineBParameters[1] = result2[2];
	logisticRegressionData.lineCParameters[1] = result2[0];

	pythonMultyOutput.setCurrentLine(2);
	PseudoRelativicHeavyBall<LogisticRegressionTarget> pseudoRelativicHeavyBall(logisticRegressionTarget, stepLimit, accuracy, a, c);
	RungeKutta<PseudoRelativicHeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta3(pseudoRelativicHeavyBall, pythonMultyOutput, h);
	std::vector<double> result3 = rungeKutta3.solve(initialData);
	logisticRegressionData.lineAParameters[2] = result3[1];
	logisticRegressionData.lineBParameters[2] = result3[2];
	logisticRegressionData.lineCParameters[2] = result3[0];

	pythonMultyOutput.setCurrentLine(3);
	NesterovGradientDescent<LogisticRegressionTarget> nesterovGradientDescent(logisticRegressionTarget, stepLimit, accuracy);
	RungeKutta<NesterovGradientDescent<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta4(nesterovGradientDescent, pythonMultyOutput, h);
	std::vector<double> result4 = rungeKutta4.solve(initialData);
	logisticRegressionData.lineAParameters[3] = result4[1];
	logisticRegressionData.lineBParameters[3] = result4[2];
	logisticRegressionData.lineCParameters[3] = result4[0];

	pythonMultyOutput.setDataPoints();

	return &multyDataPoints;

}

double rand(double b, double e)
{
	return b + (rand() % static_cast<unsigned int>((e - b) * 1000)) / 1000.;
}

MATHLIBRARY_API PythonMultyOutput::DataPoints* logisticRegressionGalaxiesMulty(double xStart, double yStart, double xVelocityStart, double yVelocityStart, int stepLimit, double accuracy, double a, double h, double c, double aGD)
{
	const int methodCount = 4;
	PythonMultyOutput pythonMultyOutput(multyDataPoints, methodCount);

	std::list<std::vector<double>>
		negativePoints,
		positivePoints;

	negativePoints.push_back({ rand(0, 6), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 6), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 6), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 6), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 6), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 6), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 6), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 6), rand(-75, 75) });
	negativePoints.push_back({ rand(0, 5), rand(-75, 75) });


	positivePoints.push_back({ rand(4, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(4, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(4, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(4, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(4, 10), rand(-75, 75) });
	positivePoints.push_back({ rand(5, 10), rand(-75, 75) });

	LogisticRegressionClassifier logisticRegressionClassifier(negativePoints, positivePoints);
	logisticRegressionClassifier.setPointsData(logisticRegressionData);
	logisticRegressionData.lineCount = methodCount;
	logisticRegressionData.lineAParameters = new double[methodCount];
	logisticRegressionData.lineBParameters = new double[methodCount];
	logisticRegressionData.lineCParameters = new double[methodCount];

	LogisticRegressionTarget logisticRegressionTarget(negativePoints, positivePoints, 0.01);

	std::vector<double> initialData{ 0, xStart, yStart, 0, xVelocityStart, yVelocityStart };

	pythonMultyOutput.setCurrentLine(0);
	HeavyBall<LogisticRegressionTarget> heavyBall(logisticRegressionTarget, stepLimit, accuracy, a);
	RungeKutta<HeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta1(heavyBall, pythonMultyOutput, h);
	std::vector<double> result1 = rungeKutta1.solve(initialData);
	logisticRegressionData.lineAParameters[0] = result1[1];
	logisticRegressionData.lineBParameters[0] = result1[2];
	logisticRegressionData.lineCParameters[0] = result1[0];

	pythonMultyOutput.setCurrentLine(1);
	GradientDescent<LogisticRegressionTarget> gradientDescent(logisticRegressionTarget, stepLimit, accuracy, aGD);
	RungeKutta<GradientDescent<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta2(gradientDescent, pythonMultyOutput, h);
	std::vector<double> result2 = rungeKutta2.solve(initialData);
	logisticRegressionData.lineAParameters[1] = result2[1];
	logisticRegressionData.lineBParameters[1] = result2[2];
	logisticRegressionData.lineCParameters[1] = result2[0];

	pythonMultyOutput.setCurrentLine(2);
	PseudoRelativicHeavyBall<LogisticRegressionTarget> pseudoRelativicHeavyBall(logisticRegressionTarget, stepLimit, accuracy, a, c);
	RungeKutta<PseudoRelativicHeavyBall<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta3(pseudoRelativicHeavyBall, pythonMultyOutput, h);
	std::vector<double> result3 = rungeKutta3.solve(initialData);
	logisticRegressionData.lineAParameters[2] = result3[1];
	logisticRegressionData.lineBParameters[2] = result3[2];
	logisticRegressionData.lineCParameters[2] = result3[0];

	pythonMultyOutput.setCurrentLine(3);
	NesterovGradientDescent<LogisticRegressionTarget> nesterovGradientDescent(logisticRegressionTarget, stepLimit, accuracy);
	RungeKutta<NesterovGradientDescent<LogisticRegressionTarget>, PythonMultyOutput> rungeKutta4(nesterovGradientDescent, pythonMultyOutput, h);
	std::vector<double> result4 = rungeKutta4.solve(initialData);
	logisticRegressionData.lineAParameters[3] = result4[1];
	logisticRegressionData.lineBParameters[3] = result4[2];
	logisticRegressionData.lineCParameters[3] = result4[0];

	pythonMultyOutput.setDataPoints();

	return &multyDataPoints;

}