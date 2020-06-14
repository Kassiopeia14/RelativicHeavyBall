#include "../modRungeKutta/rungeKutta.h"
#include "../modTestF/testF.h"
#include "../modOutput/consoleOutput.h"

int main()
{
	TestF testF;
	ConsoleOutput consoleOutput;

	RungeKutta<TestF, ConsoleOutput> rungeKutta(testF, consoleOutput, 0.1);

	std::vector<double> initialData{ 0.0 };

	std::vector<double> result = rungeKutta.solve(initialData); 

	return 0;
}