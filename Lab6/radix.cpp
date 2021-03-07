#include <bits/stdc++.h>

using namespace std;

int maxElemLength(const vector<int>& v);
int GetDigit(int number, int k);
vector<queue<int> > ItemsToQueues(const vector<int>& L, int k);
vector<int> QueuesToArray(vector<queue<int> >& QA, int numVals);
void RadixSort(vector<int>& L, int numDigits);
void PrintVector(const vector<int>& L);

int main()
{
    vector<int> v{380,95,345,382,260,100,492};
    int numDigits = maxElemLength(v);
    PrintVector(v);
    RadixSort(v,numDigits);
    PrintVector(v);
    return 0;
}

//find the length of the longest element in the 
int maxElemLength(const vector<int>& v)
{
    int maxLength = 0;
    string elem;
    for(int i = 0; i < v.size(); i++)
    {
        elem = to_string(v[i]);
        if(elem.length() > maxLength)
            maxLength = elem.length();
    }
    return maxLength;
}

//gets a specific digit of a number
int GetDigit(int number, int k)
{
    for(int i = 0; i < k; i++)
    {
        number /= 10;
    }
    return number % 10;
}

//puts items of a vector into "buckets" (queues)
vector<queue<int> > ItemsToQueues(const vector<int>& L, int k)
{
    vector<queue<int> > QA(10);
    for(int i = 0; i < L.size(); i++)
    {
        QA[GetDigit(L[i],k)].push(L[i]);
    }
    return QA;
}

//put queues back into the vector
vector<int> QueuesToArray(vector<queue<int> >& QA, int numVals)
{
    vector<int> L(numVals);
    int n = 0;
    for(int i = 0; i < QA.size(); i++)
    {
        int QSize = QA[i].size();
        for(int j = 0; j < QSize; j++)
        {
            L[n++] = QA[i].front();
            QA[i].pop();
        }
    }
    return L;
}

//sort a vector using a radix sort
void RadixSort(vector<int>& L, int numDigits)
{
    vector<queue<int> > QA(10);
    for(int k = 0; k < numDigits; k++)
    {
        QA = ItemsToQueues(L,k);
        L = QueuesToArray(QA,L.size());
    }
}

//print out a vector
void PrintVector(const vector<int>& L)
{
    for(int i = 0; i < L.size(); i++)
    {
        cout << "[" << i << "]"<< L[i] << endl;
    }
    cout << "-----------------------------" << endl;
}