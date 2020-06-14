#include <windows.h>
#include <iostream>
#include "../modOutput/pythonOutput.h"
#include "../modOutput/pythonMultyOutput.h"
#include "../modTargets/logisticRegressionTarget.h"
#include "../modLogisticRegression/logisticRegressionClassifier.h"

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

typedef PythonMultyOutput::DataPoints* (*WashtubMultyFunction)(double xStart, double yStart, double vXStart, double vYStart, int stepLimit, double accuracy, double a, double h, double c);

void testWashtubMultyPythonDLL()
{
    HINSTANCE hModule = NULL;
    hModule = ::LoadLibrary(L"testPythonDLL.dll");
    if (hModule != NULL)
    {
        WashtubMultyFunction washtubMultyFunction = (WashtubMultyFunction)GetProcAddress(hModule, "washtubMulty");

        PythonMultyOutput::DataPoints* dataPoints = (*washtubMultyFunction)(4, 3, 0, 0, 1000, 0.0001, 0.1, 0.1, 20);

        for (int i = 0; i < dataPoints->pointCounts[0]; i++)
        {
            std::cout << i << ": " << dataPoints->xValues[i] << ", " << dataPoints->yValues[i] << " " << dataPoints->zValues[i] << std::endl;
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

typedef PythonMultyOutput::DataPoints* (*LogisticRegressionGalaxiesMultyFunction)(double xStart, double yStart, double vXStart, double vYStart, int stepLimit, double accuracy, double a, double h, double c);
typedef LogisticRegressionData* (*GetLogisticRegressionDataFunction)();

void testLogisticRegressionGalaxiesMultyPythonDLL()
{
    HINSTANCE hModule = NULL;
    hModule = ::LoadLibrary(L"testPythonDLL.dll");
    if (hModule != NULL)
    {
        LogisticRegressionGalaxiesMultyFunction logisticRegressionMultyFunction = (LogisticRegressionGalaxiesMultyFunction)GetProcAddress(hModule, "logisticRegressionGalaxiesMulty");
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


void main()
{
    testLogisticRegressionGalaxiesMultyPythonDLL();
}