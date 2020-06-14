#pragma once

#include <vector>
#include "../modMatrix/matrix.h"

class NormTarget
{
public:

	static double target(std::vector<double> _coordinates);

	static std::vector<double> gradient(std::vector<double> _coordinates);

	static Matrix gessian(std::vector<double> _coordinates);

private:
};