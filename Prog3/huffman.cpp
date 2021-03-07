#include "huffman.h"
#include <iostream>
using namespace std;

HuffmanTree:: HuffmanTree()
	: numChars(0), built(false) {}

void HuffmanTree:: insert(char ch, int weight) 
{
    HNode newNode = {ch, weight, -1, -1}; 
    built = false;
    nodes.push_back(newNode);
    numChars++;
}

//calls the lookup function, if the returns whether or not the lookup function found the character
bool HuffmanTree:: inTree(char ch) 
{
    return lookUp(ch) != -1;
}

//gets frequency of a character in the huffman tree
int HuffmanTree:: GetFrequency(char ch) 
{
    if(inTree(ch))
        return GetFrequency((int)ch);
    else
        return 0;    
}

//Gets the frequency of a character in the huffman tree, private version
int HuffmanTree:: GetFrequency(int i) 
{
    char ch;
    int charFreqs[255];

   for(int j = 0; j < nodes.size(); j++)
   {
       if(nodes[j].ch == char(i))
       {
           charFreqs[i]+=nodes[j].weight;
       }
   }
    return charFreqs[i];   
}

//returns index of a given character in the vector of HNodes
int HuffmanTree:: lookUp(char ch) 
{
    int pos = 0;
    while(pos < numChars)
    {
        if(nodes[pos].ch == ch)
            return pos;
        pos++;
    }
    return -1;
}

//calls private verson of getCode using lookUp to find index of the char in the vector of HNodes
string HuffmanTree:: GetCode(char ch) 
{
    return GetCode(lookUp(ch));
}

//recursively goes through the tree and returns a encoded version of a character
string HuffmanTree:: GetCode(int i) 
{
    if(nodes[i].parent == -1)
        return "";
    else
        return (GetCode(nodes[i].parent) + (char)(nodes[i].childType+'0'));
}

//prints out the huffman encoding table
void HuffmanTree:: PrintTable() 
{
    int T = 1;
    cout << "------------------------------------" << endl;
    cout << "-----------Encoding table-----------" << endl;
    cout << "------------------------------------" << endl;
    cout << "-INDEX CHAR WEIGHT PARENT CHILDTYPE-" << endl;
    cout << "------------------------------------" << endl;
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i].ch != '\0' && nodes[i].ch != ' ' &&  nodes[i].ch != '\n')
            cout << "-  " << i << "\t" << nodes[i].ch << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t" << nodes[i].childType <<  " -" << endl;
        else if(nodes[i].ch == '\0')
        {
            if(nodes[i].parent != -1)
                cout << "-  " << i << "\t" << "T" << T << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t" << nodes[i].childType <<  " -" << endl;
            else
                cout << "-  " << i << "\t" << "T" << T << "\t" << nodes[i].weight << "\t" << "0" << "\t"  << "N/A-" << endl;
            T++;
        }
        else if(nodes[i].ch == ' ')
            cout << "-  " << i << "\t" << "sp" << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t" << nodes[i].childType <<  " -" << endl;
        else
        {
            cout << "-  " << i << "\t" << "nl" << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t" << nodes[i].childType <<  " -" << endl;
        }
        
    } 
    cout << "------------------------------------" << endl;

}

//returns the number of nodes in the huffman tree
int HuffmanTree:: numNodes() 
{
    return nodes.size();
}

//builds huffman tree from the vector of HNodes
void HuffmanTree:: build() 
{
    int saveNumChars = numChars;
    vector<int> freqArray;
    while(!built)
    {
        int firstLowest = GetLowestFreq(freqArray);
        freqArray.push_back(firstLowest);
        int secondLowest = GetLowestFreq(freqArray);
        freqArray.push_back(secondLowest);

        insert('\0',nodes[firstLowest].weight+nodes[secondLowest].weight);
        nodes[firstLowest].childType = 0;
        nodes[firstLowest].parent = nodes.size()-1;
        nodes[secondLowest].childType = 1;
        nodes[secondLowest].parent = nodes.size()-1;

        if(nodes.size() == (2*saveNumChars-1))
            built = true;
    }
    
}

//gets index of lowest frequency in vector
int HuffmanTree :: GetLowestFreq(vector<int>& freqArray)
{
    int lowWeight = 99999;
    int lowIndex;
    for(int i = 0; i < nodes.size(); i++)
    {
        if((nodes[i].weight < lowWeight) && !InVector(freqArray,i))
        {
            lowIndex = i;
            lowWeight = nodes[i].weight;
        }
    }
    return lowIndex;
}

bool HuffmanTree :: InVector(vector<int>& freqArray, int index)
{
    for(int i = 0; i < freqArray.size(); i++)
    {
        if(index == freqArray[i])
            return true;
    }
    return false;
}