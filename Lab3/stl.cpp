#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

void initialize(vector<int> &v);

void print(vector<int> &v);

void reverse(vector<int> &v);

int main()
{
	stack<string> s1, s2;
	s1.push("Hello there");
	s2.push("General Kenobi");
	
	if(s1 == s2)
		cout << "s1 == s2" << endl;
	if(s1 < s2)
		cout << "s1 < s2" << endl;
	if(s1 > s2)
		cout << "s1 > s2" << endl;

	vector<int> v;

	initialize(v);

	print(v);

	reverse(v);

	print(v);

	sort(v.begin(),v.end());
	
	print(v); 
}

void initialize(vector<int> &v)
{
	int x;
	for(int i = 0; i < 5; i++)
	{	
		cin >> x;
		v.push_back(x);
	}
}

void print(vector<int> &v)
{
	for(int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}

void reverse(vector<int> &v)
{
	vector<int> b;
	for(int i = v.size()-1; i >= 0 ; i--)
	{
		b.push_back(v[i]);
	}	
	v = b;
}
