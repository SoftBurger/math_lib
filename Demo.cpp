#include "Trigonometric_Functions/Trigonometric_Functions.h"
#include <iostream>

using namespace std;

void Demo()
{
	cout << "*************************************\n";
	cout << "          Demo: function sin         \n";
	cout << "*************************************\n";
	cout << endl;
	//cout << "Input degree of last member: ";  unsigned n;  cin >> n;  math_lib::set_num_terms(n);  cout << endl;
	math_lib::set_error(0.0001);

	while (true)
	{
		double x;
		cout << "x = ";  cin >> x;
		cout << "sin(" << x << ") = " << math_lib::sin(x) << endl;
		cout << endl;
		char ch;
		cout << "Continue (yes-y, no-another): ";  cin >> ch;
		if (ch != 'y')
			break;
		cout << endl;
	}
}