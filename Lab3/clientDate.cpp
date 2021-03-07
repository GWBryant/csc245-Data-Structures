
#include <iostream>
#include "date.h"
using namespace std;

int main()
{

	Date date1 (9,2,2002,13,00,00,"Labor Day");
	Date date2 (9,6,2002,13,00,00,"First Friday");
	Date date3;

	cout << "Date1 = \t" << date1 << endl;
	cout << "Date2 = \t" << date2 << endl;
	cout << "Date3 = \t" << date3 << endl;

	date3 = date2;          

	cout << "Date3 = \t" << date3 << endl << endl;

	if (date1 < date2)
		cout << "Date1 Is Less Than Date2." << endl;
	else if (date1 == date2)
		cout << "Date1 Is Equal To Date2." << endl;
        return 0;
}
