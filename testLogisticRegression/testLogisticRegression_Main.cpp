#include "../modRungeKutta/rungeKutta.h"
#include "../modOptimizationMethods/heavyBall.h"
#include "../modOutput/consoleOutput.h"
#include "../modTargets/LogisticRegressionTarget.h"

int main()
{
	std::list<std::vector<double>>
		negativePoints,
		positivePoints;
	/*
	negativePoints.push_back({ 1.0, 0.0 });
	negativePoints.push_back({ 2.0, 1.0 });
	negativePoints.push_back({ 3.0, 2.0 });
	negativePoints.push_back({ 4.0, 3.0 });
	negativePoints.push_back({ 5.0, 4.0 });
	
	positivePoints.push_back({ 0.0, 1.0 });
	positivePoints.push_back({ 1.0, 2.0 });
	positivePoints.push_back({ 2.0, 3.0 });
	positivePoints.push_back({ 3.0, 4.0 });
	positivePoints.push_back({ 4.0, 5.0 });
	*/

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

	HeavyBall<LogisticRegressionTarget> heavyBall(logisticRegressionTarget, 1000000, 0.00001, 0.1);
	ConsoleOutput consoleOutput;

	RungeKutta<HeavyBall<LogisticRegressionTarget>, ConsoleOutput> rungeKutta(heavyBall, consoleOutput, 0.1);

	//std::vector<double> initialData{0, 0, 0, 0, 0, 0 };

	std::vector<double> initialData{ 0.0, 0.0, 0.0, 0, 0, 0 };

	std::vector<double> result = rungeKutta.solve(initialData);

	return 0;
}