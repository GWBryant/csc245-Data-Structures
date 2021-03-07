#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

template<typename T> void fillQueue(T & pq);
template<typename T> void printQueue(T & pq);

int main()
{
	priority_queue<string> pq;
	fillQueue(pq);
	printQueue(pq);
	return 0;
}

template<typename T> void fillQueue(T & pq)
{
	pq.push("Gabe");
	pq.push("Jacob");
	pq.push("Liz");
	pq.push("Ronald");
	pq.push("Will");
	pq.push("Colton");
	pq.push("Rob");
	pq.push("Andy");
	pq.push("David");
	pq.push("Allen");
}

template<typename T> void printQueue(T & pq)
{
	while(!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}
