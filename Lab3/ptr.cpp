#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

struct RecType
{
	int age;
	float weight;
	char gender;
};

int main()
{
	int num = 5;
	int *intPtr = NULL;
	//intPtr = &num;
	*intPtr *= 10;

	cout << "intPtr points to: \t\t\t";
	cout << *intPtr << endl;
	
	RecType *recPtr = new RecType;
	recPtr -> age = 25;
	recPtr -> weight = 190.0;
	recPtr -> gender = 'M';
	recPtr -> age += 5;

	cout << "Three feilds pointed to by rectPtr: \t";
	cout << recPtr -> age << " " << recPtr -> weight << " " << recPtr -> gender << endl;
	delete recPtr;

	char *strPtr = new char[50];
	char str[]  = "Operating Systems";
	strcpy (strPtr, str);

	cout << "strPtr points to: \t\t\t";
	cout << strPtr << endl;

	int lower = 0;
	for(int i = 0; i < strlen(strPtr); i++)
	{
		if(islower(*(strPtr+i)))
			lower++;
	}
	cout << endl;
	
	cout << "Lower case letters pointed to by strPtr: ";
	cout << lower << endl;

	strPtr += 10;
	
	cout << "Printing strPtr after adding 10: \t";
	cout << strPtr << endl;
	strPtr -= 10;
	
	delete strPtr;
	return 0;
}
