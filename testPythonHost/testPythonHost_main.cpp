#include <windows.h>
#include <iostream>
#include "../modOutput/pythonOutput.h"
#include "../modOutput/pythonMultyOutput.h"
#include "../modTargets/logisticRegressionTarget.h"

using namespace std;

typedef PythonOutput::DataPoints* (*ReturnResultFunction)(double xStart, double yStart, double vXStart, double vYStart, int stepLimit, double accuracy, double a, double h, double c);

void testPythonDLL()
{
    HINSTANCE hModule = NULL;
    hModule = ::LoadLibrary(L"testPythonDLL.dll");
    if (hModule != NULL)
    {
        ReturnResultFunction returnResultFunction = (ReturnResultFunction)GetProcAddress(hModule, "returnResult");

        PythonOutput::DataPoints* dataPoints = (*returnResultFunction)(4, 3, 0, 0, 1000, 0.0001, 0.1, 0.01, 20);

        for (int i = 0; i < dataPoints->pointCount; i++)
        {
            std::cout << i << ": " << dataPoints->xValues[i] << ", " << dataPoints->yValues[i] << " " << dataPoints->zValues[i] << std::endl;
        }

        ::FreeLibrary(hModule);
    }
    else cout << "error load Dll" << endl;
}

typedef PythonMultyOutput::DataPoints* (*WashtubMultyFunction)(
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
    const double _h);

void testWashtubMultyPythonDLL()
{
    HINSTANCE hModule = NULL;
    hModule = ::LoadLibrary(L"testPythonDLL.dll");
    if (hModule != NULL)
    {
        WashtubMultyFunction washtubMultyFunction = (WashtubMultyFunction)GetProcAddress(hModule, "washtubMulty");

        PythonMultyOutput::DataPoints* dataPoints = (*washtubMultyFunction)(1, 0.5, 0, 0, 10000, 0.0001, 0.9, 0.5, true, true, 0.01);

        for (int k = 0; k < dataPoints->lineCount; k++)
        {
            for (int i = 0; i < dataPoints->pointCounts[k]; i++)
            {
                std::cout << i << ": " << dataPoints->xValues[i] << ", " << dataPoints->yValues[i] << " " << dataPoints->zValues[i] << std::endl;
            }
        }
        
        for (int k = 0; k < dataPoints->lineCount; k++)
        {
            std::cout << "line " << k << ", " << dataPoints->pointCounts[k] << " points" << std::endl;
        }
        ::FreeLibrary(hModule);
    }
    else cout << "error load Dll" << endl;
}

typedef PythonMultyOutput::DataPoints* (*QuadraticFormMultyFunction)(double xStart, double yStart, double vXStart, double vYStart, int stepLimit, double accuracy, double a, double h, double c);

void testQuadraticFormMultyPythonDLL()
{
    HINSTANCE hModule = NULL;
    hModule = ::LoadLibrary(L"testPythonDLL.dll");
    if (hModule != NULL)
    {
        QuadraticFormMultyFunction quadraticFormMultyFunction = (QuadraticFormMultyFunction)GetProcAddress(hModule, "quadraticFormMulty");

        PythonMultyOutput::DataPoints* dataPoints = (*quadraticFormMultyFunction)(4, 3, 0, 0, 1000, 0.0001, 0.1, 0.1, 20);

        for (int i = 0; i < dataPoints->pointCounts[0]; i++)
        {
            std::cout << i << ": " << dataPoints->xValues[i] << ", " << dataPoints->yValues[i] << " " << dataPoints->zValues[i] << std::endl;
        }

        ::FreeLibrary(hModule);
    }
    else cout << "error load Dll" << endl;
}

typedef PythonMultyOutput::DataPoints* (*LogisticRegressionMultyFunction)(double xStart, double yStart, double vXStart, double vYStart, int stepLimit, double accuracy, double a, double h, double c);
typedef LogisticRegressionData* (*GetLogisticRegressionDataFunction)();

void testLogisticRegressionMultyPythonDLL()
{
    HINSTANCE hModule = NULL;
    hModule = ::LoadLibrary(L"testPythonDLL.dll");
    if (hModule != NULL)
    {
        LogisticRegressionMultyFunction logisticRegressionMultyFunction = (LogisticRegressionMultyFunction)GetProcAddress(hModule, "logisticRegressionMulty");
        GetLogisticRegressionDataFunction getLogisticRegressionDataFunction = (GetLogisticRegressionDataFunction)GetProcAddress(hModule, "getLogisticRegressionData");
        
        PythonMultyOutput::DataPoints* dataPoints = (*logisticRegressionMultyFunction)(4, 3, 0, 0, 1000, 0.0001, 0.1, 0.1, 20);

        for (int i = 0; i < dataPoints->pointCounts[0]; i++)
        {
            std::cout << i << ": " << dataPoints->xValues[i] << ", " << dataPoints->yValues[i] << " " << dataPoints->zValues[i] << std::endl;
        }

        LogisticRegressionData* logisticRegressionData = (*getLogisticRegressionDataFunction)();

        ::FreeLibrary(hModule);
    }
    else cout << "error load Dll" << endl;
}

typedef PythonMultyOutput::DataPoints* (*LogisticRegressionMultyFunctionNew)(
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
    bool _useHessian,
    double _h);
typedef LogisticRegressionData* (*GetLogisticRegressionDataFunction)();

void testLogisticRegressionMultyPythonDLLNew()
{
    HINSTANCE hModule = NULL;
    hModule = ::LoadLibrary(L"testLogisticRegressionLibrary.dll");
    if (hModule != NULL)
    {
        LogisticRegressionMultyFunctionNew logisticRegressionMultyFunction = (LogisticRegressionMultyFunctionNew)GetProcAddress(hModule, "logisticRegressionMulty");
        GetLogisticRegressionDataFunction getLogisticRegressionDataFunction = (GetLogisticRegressionDataFunction)GetProcAddress(hModule, "getLogisticRegressionData");

        double _negativeX0 = 3.0;
        double _negativeY0 = 3.0;
        double _negativeSigmaX = 1.0;
        double _negativeSigmaY = 1.0;
        int _negativeCount = 100;
        double _positiveX0 = 6.0;
        double _positiveY0 = 5.0;
        double _positiveSigmaX = 1.0;
        double _positiveSigmaY = 1.0;
        int _positiveCount = 100;
        double _regularization = 0.01;
        double _xStart = 0;
        double _yStart = 0;
        double _xSpeedStart = 0;
        double _ySpeedStart = 0;
        int _stepLimit = 1000;
        double _targetAccuracy = 0.0001;
        double _param = 1.0;
        double _lightSpeed = 10.0;
        bool _useHessian = true;
        double _h = 0.01;

        PythonMultyOutput::DataPoints* dataPoints = (*logisticRegressionMultyFunction)(
            _negativeX0, _negativeY0, _negativeSigmaX, _negativeSigmaY, _negativeCount,
            _positiveX0, _positiveY0, _positiveSigmaX, _positiveSigmaY, _positiveCount,
            _regularization,
            _xStart, _yStart, _xSpeedStart, _ySpeedStart,
            _stepLimit, _targetAccuracy, _param, _lightSpeed,
            _useHessian,
            _h);

        for (int i = 0; i < dataPoints->pointCounts[0]; i++)
        {
            std::cout << i << ": " << dataPoints->xValues[i] << ", " << dataPoints->yValues[i] << " " << dataPoints->zValues[i] << std::endl;
        }

        LogisticRegressionData* logisticRegressionData = (*getLogisticRegressionDataFunction)();

        ::FreeLibrary(hModule);
    }
    else cout << "error load Dll" << endl;
}


int main()
{
    testWashtubMultyPythonDLL();

    return 0;
}