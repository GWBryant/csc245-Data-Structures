#include <bits/stdc++.h>

using namespace std;

int maxElemLength(const vector<string>& v);
char GetDigit(string word, int k);
vector<queue<string> > ItemsToQueues(const vector<string>& L, int k);
vector<string> QueuesToArray(vector<queue<string> >& QA, int numVals);
void RadixSort(vector<string>& L, int numDigits);
void PrintVector(const vector<string>& L);
void padStrings(vector<string>& L, int numDigits);
void trimStrings(vector<string>& L);

int main()
{
    vector<string> v{"zebra", "apple", "orange", "can", "candy", "a", "top", "pumpkin", "today", "parade"};
    int numDigits = maxElemLength(v);
    PrintVector(v);
    padStrings(v,numDigits);
    RadixSort(v,numDigits);
    trimStrings(v);
    PrintVector(v);
    return 0;
}

//finds the longest string in a vector of strings
int maxElemLength(const vector<string>& v)
{
    int maxLength = 0;
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i].length() > maxLength)
            maxLength = v[i].length();
    }
    return maxLength;
}

//gets a specific character of a string
char GetDigit(string word, int k)
{
    return word[word.length()-k-1];
}

//puts items from vectors into "buckets" (queues)
vector<queue<string> > ItemsToQueues(const vector<string>& L, int k)
{
    vector<queue<string> > QA(128);
    for(int i = 0; i < L.size(); i++)
    {
        QA[GetDigit(L[i],k)].push(L[i]);
    }
    return QA;
}

//put "sorted" strings from queues back into arrays
vector<string> QueuesToArray(vector<queue<string> >& QA, int numVals)
{
    vector<string> L(numVals);
    int n = 0;
    for(int i = 0; i < QA.size(); i++)
    {
        int QSize = QA[i].size();
        for(int j = 0; j < QSize; j++)
        {
            L[n] = (QA[i].front());
            QA[i].pop();
            n++;
        }
    }
    return L;
}

//sort a vector of strings with a radix sort
void RadixSort(vector<string>& L, int numDigits)
{
    vector<queue<string> > QA(128);
    for(int k = 0; k < numDigits; k++)
    {
        QA = ItemsToQueues(L,k);
        L = QueuesToArray(QA,L.size());
    }
}

//print a vector of strings
void PrintVector(const vector<string>& L)
{
    for(int i = 0; i < L.size(); i++)
    {
        cout << "[" << i << "]"<< L[i] << endl;
    }
    cout << "-----------------------------" << endl;
}

//pad strings in so that they are the same lengh as the longest string
void padStrings(vector<string>& L, int numDigits)
{
    for(int i = 0; i < L.size(); i++)
    {
        while(L[i].length() != numDigits)
            L[i] += " ";
    }
}

//trim spaces from strings
void trimStrings(vector<string>& L)
{
   for(int i = 0; i < L.size(); i++)
   {
	L[i] = L[i].substr(0,L[i].find(' ')); 
   }
}
