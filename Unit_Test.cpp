#include "Trigonometric_Functions/Trigonometric_Functions.h"
#include <exception>
#include <iostream>

using namespace math_lib;
using exception = std::exception;
using std::endl;
using std::cin;
using std::cout;

struct Unit_Test_Exception : public exception
{
	Unit_Test_Exception(const char* str)
		: exception(str)
	{
	}
};

void Check(bool b)
{
	if (!b)
		throw Unit_Test_Exception("Test is false");
}

void HandleException(const char* str)
{
	cout << str;
	cout << "Press n to continue, press another key to break";
	char ch;
	cin >> ch;
	if (ch != '\n')
		throw;
}

void Tests()
{
	math_lib::set_error(0.0001);

	const double eps = 0.01;

	Check(math_lib::abs(math_lib::sin(0.0) - 0.0) < eps);
	Check(math_lib::abs(math_lib::sin(1.57) - 1.0) < eps);
	Check(math_lib::abs(math_lib::sin(3.14) - 0.0) < eps);
	Check(math_lib::abs(math_lib::sin(-1.57) - (-1.0)) < eps);
	Check(math_lib::abs(math_lib::sin(-3.14) - 0.0) < eps);
}

void Unit_Test()
{
	try
	{
		Tests();
	}
	catch (Unit_Test_Exception excep)
	{
		HandleException("Unit_Test_Exception");
	}
	catch (exception excep)
	{
		HandleException(excep.what());
	}
	catch (...)
	{
		HandleException("Unknown exception");
	}
}