#include <iostream>
#include <map>
#include <fstream>
#include <cstring>

using namespace std;

void createMap(map<string,int>& charMap,ifstream& inputFile);
void unZipFile(map<string,int>& charMap,ifstream& inputFile, ofstream& outputFile);

int main(int argc, char **argv)
{
    //declare variables
    ifstream inputFile;
    ofstream outputFile;
    map<string,int> charMap;

    //open input and output files
    string inFileName = argv[1];
    inputFile.open(inFileName);
    string outFileName = inFileName.substr(0,inFileName.find("."));
    outputFile.open(outFileName);

    //create map from input file
    createMap(charMap,inputFile);

    //unzip the file and output contents
    unZipFile(charMap,inputFile,outputFile);

    cout << "File Successfully Inflated Back To Original." << endl;
    return 0;
}

//function to create a map based on text input
void createMap(map<string,int>& charMap,ifstream& inputFile)
{
    //declare variables for the number of input lines and mapping items
    int numChars, asciiCode;
    string encoding;
    //get the number of input lines from file
    inputFile >> numChars;
    //loop through input and create a map
    for(int i = 0; i < numChars; i++)
    {
        inputFile >> asciiCode;
        inputFile >> encoding;
        charMap[encoding] = asciiCode;
    }
}

//function to parse through a compressed string and unzip it based on a map we generated
void unZipFile(map<string,int>& charMap,ifstream& inputFile, ofstream& outputFile)
{
    //declare variables for encoded string and map key
    string encodedString, charString;
    //get encoded string from input file
    inputFile >> encodedString;
    //loop through encoded string from input and decode it, printing to output file
    for(int j = 0; j < encodedString.length(); j++)
    {
        //add chars to the map key char by char from input string
        charString += encodedString[j];
        //if the current map key exists in the map then print out the decoded value and empty the map key
        if(charMap.find(charString) != charMap.end())
        {
            outputFile << char(charMap[charString]);
            charString = "";
        }
    }
}