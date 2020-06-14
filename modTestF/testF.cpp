#include "testF.h"

/*

http://kontromat.ru/?page_id=5362

x' = F(t,x) = t^2 * (3x + exp(t^3))

t_n		x_n			k1_n		k2_n		k3_n		k4_n		x(t_n) for comparison

0		0			0			0,0025		0,002501	0,010018	0
0,1		0,000334	0,01002		0,022632	0,022675	0,040633	0,000334
0,2		0,002688	0,040644	0,064369	0,064592	0,094933	0,002688
0,3		0,009246	0,09496		0,133009	0,133709	0,181431	0,009246
0,4		0,022744	0,181492	0,241149	0,242961	0,318567	0,022743
0,5		0,047215	0,318698	0,414566	0,418916	0,543032	0,047215
0,6		0,08936		0,543305	0,703721	0,713888	0,926793	0,089359
0,7		0,161115	0,927332	1,207835	1,231503	1,61371		0,161115
0,8		0,284777	1,614692	2,127454	2,183025	2,901619	0,284779
0,9		0,503732	2,903203	3,884036	4,016816	5,434521	0,503741
1		0,906055	 	 	 	 	 								0,906094

*/


TestF::TestF()
{
}

TestF::~TestF()
{
}

double TestF::result(const double _time, std::vector<double> _x) const
{
	return exactSolution(_time);
}

std::vector<double> TestF::calculateF(double _time, std::vector<double> _x) const
{
	double
		t = _time,
		x = _x[0];

	std::vector<double> result(1);

	result[0] = F(t, x);

	return result;
}

bool TestF::stopCondition(size_t _stepNumber, std::vector<double> _newData, std::vector<double> _oldData) const
{
	return (_stepNumber > 10);
}

double TestF::F(const double _t, const double _x) const
{
	return _t * _t * (3 * _x + exp(_t * _t * _t));
}

double TestF::exactSolution(const double _t) const
{
	return _t * _t * _t * exp(_t * _t * _t) / 3;
}