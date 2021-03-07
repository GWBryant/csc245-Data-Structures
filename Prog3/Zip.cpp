#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include "huffman.h"

using namespace std;

void CountLetters (int Letters[], ifstream & inputFile,string& fileContents);
void AddLetters (const int Letters[],HuffmanTree& encodingTree, int& numChars);
void compressFile(const int Letters[], int& numChars, ofstream& outFile,string& fileContents,map<int,string>& charMap,string& encodedString);
void createMap(const int Letters[],HuffmanTree& encodingTree, map<int,string>& charMap);
void exitMessage(string encodedString, string fileContents);
void printHelp();

const int NumLetters = 256;

int main(int argc, char **argv)
{
    //declare variables
    ifstream inputFile;
    ofstream outputFile;
    int letters[NumLetters];
    HuffmanTree encodingTree;
    map<int,string> charMap;
    int numChars = 0;
    string encodedString;
    string fileContents;
    string inFileName;
    string optionalInput = argv[1];

    //check for optional command line input parameters
    if(optionalInput == "--t")
    {
        if(argv[2] != NULL)
            inFileName = argv[2];
        else
        {
            cout << "Invalid input" << endl;
            exit(1);
        }
    }
    else if(optionalInput == "--help")
    {
        printHelp();
        exit(1);
    }
    else if(optionalInput[0] == '-')    //if argv[1] starts with - but isn't --t or --help alert user that its invalid input
    {
        cout << "Invalid input, run with --help for help" << endl;
        exit(1);
    }
    else
        inFileName = optionalInput;

    //open files
    try {   //try to open the files
        inputFile.open(inFileName);
        string outFileName = inFileName + ".zip";
        if(!inputFile.good())
            throw runtime_error("File Not Found");
        else
            outputFile.open(outFileName);
    }   //if you cant open the file print an error message
    catch (exception exc)
    {
        cout << "File " << inFileName << " does not exist." << endl;
        exit(1);
    }

    //count letters in the file
    CountLetters(letters,inputFile,fileContents);

    //add letters to the huffman tree
    AddLetters(letters,encodingTree,numChars);

    //build tree
    encodingTree.build();

    //if theres an optional input param execute the appropriate operation
    if(optionalInput == "--t")
        encodingTree.PrintTable();

    //build map
    createMap(letters,encodingTree,charMap);

    //output data to compressed file
    compressFile(letters,numChars,outputFile,fileContents,charMap,encodedString);

    //output compression ratio
    exitMessage(encodedString,fileContents);

    //close files
    inputFile.close();
    //}
    return 0;
}

//count all of the characters in the input file
void CountLetters(int Letters[], ifstream & inputFile,string& fileContents)
{
    char ch;

	for (char ch = char(0);  ch <= char(126);  ch++)
		Letters[ch] = 0;

	inputFile.get(ch);
    fileContents += ch;
	while (inputFile)
	{
		Letters[ch] += 1;
		inputFile.get(ch);
        fileContents += ch;
	}
}

//method to insert letters into the huffman tree
void AddLetters (const int Letters[],HuffmanTree& encodingTree, int& numChars)
{
	for (char ch = char(0);  ch <= char(126);  ch++)
    {
	  if (Letters[ch] != 0)
      {
	    encodingTree.insert(ch,Letters[ch]);
        numChars++;
      }
    }
}

//method to compress a file and output it to a file
void compressFile(const int Letters[], int& numChars, ofstream& outFile,string& fileContents,map<int,string>& charMap,string& encodedString)
{
    outFile << numChars << endl;
    for (char ch = char(0);  ch <= char(126);  ch++)
	{
        if(Letters[ch] != 0)
        {
            outFile << (int)ch << " " << charMap[ch] << endl;
        }
    }
    for(int i = 0; i < fileContents.length()-1; i++)
    {
        encodedString += charMap[fileContents[i]];
    }
    outFile << encodedString;
}

//method to create a map between characters in the input string and its encoding
void createMap(const int Letters[],HuffmanTree& encodingTree,map<int,string>& charMap)
{
    for(int i = 0; i < 126; i++)
    {
        if(Letters[i] != 0)
        {
            charMap[i] = encodingTree.GetCode(char(i)); 
        }
    }
}

//method to calculate and print compression ratio
void exitMessage(string encodedString, string fileContents)
{
    double compressionRatio = (1 - ((double)encodedString.length()/((double)(fileContents.length()-1) * 8.0))) * 100;
    cout << "File Successfully Compressed To "<< encodedString.length() << " Bits (";
    printf("%.2f",compressionRatio);
    cout << "% Less)." << endl;
}

//method to print help
void printHelp()
{
    cout << "--INPUT FORMAT--" << endl;
    cout << "myZip [--help] [--t] [filename]" << endl << endl;
    cout << "--help: display how to execute code" << endl;
    cout << "--t: display the encoding table when you run the program" << endl;
}