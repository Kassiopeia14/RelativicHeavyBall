#include "../modRungeKutta/rungeKutta.h"
#include "../modOptimizationMethods/heavyBall.h"
#include "../modOutput/consoleOutput.h"
#include "../modTargets/normTarget.h"

int main()
{
	NormTarget normTarget;
	HeavyBall<NormTarget> heavyBall(normTarget, 10000, 0.0001, 10, true);
	ConsoleOutput consoleOutput;

	RungeKutta<HeavyBall<NormTarget>, ConsoleOutput> rungeKutta(heavyBall, consoleOutput, 0.01);

	std::vector<double> initialData{ 1, 1, 0, 0 };

	std::vector<double> result = rungeKutta.solve(initialData);

	return 0;
}