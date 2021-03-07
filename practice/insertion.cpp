#include <iostream>
#include <vector>

using namespace std;

void inSort(vector<int> & vec);

int main()
{
    vector<int> vec;
    vec.push_back(8);
    vec.push_back(3);
    vec.push_back(78);
    vec.push_back(9);
    vec.push_back(23);
    //for(int i = 0; i < vec.size(); i++)
      //  cout << vec[i] << " ";
    //cout << endl;
    inSort(vec);
    //for(int i = 0; i < vec.size(); i++)
      //  cout << vec[i] << " ";
    //cout << endl;
    return 0;
}

void inSort(vector<int> & vec)
{
    for(int p = 1; p < vec.size(); p++)
    {
        int tmp = vec[p];

        int j;
        for(int j = p; j > 0 && tmp < vec[j-1]; j--)
            vec[j] = vec[j-1];
        vec[j] = tmp;
    }
}