#include <iostream>
using namespace std;

double convert(double value);

int main()
{
	double cTemp;
	cout << "Please enter a Celsius value: ";
	cin >> cTemp;
	cout << cTemp << " degrees celcius is " << convert(cTemp) << " degrees Fahrenheit.\n";
	return 0;
}

double convert(double tmp)
{
	return 1.8 * tmp + 32.0;
}
