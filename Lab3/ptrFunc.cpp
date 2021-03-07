#include <iostream>
#include <cstring>

using namespace std;

bool valueEquals(double *ptr1, double *ptr2);

bool memoryEquals(double *ptr1, double *ptr2);

int main()
{
	double data = 8.0;

	double *ptr1 = &data;
	double *ptr2 = &data;

	cout << "value equals "  << valueEquals(ptr1,ptr2) << endl;
	cout << "memory location equals " << memoryEquals(ptr1,ptr2) << endl;
	return 0;
}

bool valueEquals(double *ptr1, double *ptr2)
{
	return (*ptr1 == *ptr2);
}

bool memoryEquals(double *ptr1, double *ptr2)
{
	return (ptr1 == ptr2);
}
