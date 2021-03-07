#include <bits/stdc++.h>
#include "graph.h"
#include "queue.h"

using namespace std;

struct vert
{
    string name;
    bool mark = false;
    bool reachable = false;
    int  dist = INT_MAX;
    string prev = "N/A";
};

ifstream openFile(string fileName);
int addVertices(string fileName, Graph<string>& dGraph, vector<vert>& vertices);
void createGraph(string fileName, Graph<string>& dGraph);
void printMenu(vector<vert>& vertices,int numVertices);
void printRow(vector<vert>& vertices, int index);
int findLowest(vector<vert>& vertices, int numVertices);
int indexOf(vector<vert>& vertices, int numVertices, string name);
string getStart(vector<vert>& vertices, int numVertices);
void findPaths(vector<vert>& vertices, int numVertices, Graph<string>& dGraph);
void shellsort( vector<vert> & vertices );
int onPath(vector<vert>& vertices, string start,Graph<string>& dGraph);

int main(int argc, char **argv)
{
    //declare graph
    Graph<string> dGraph(50);
    vector<vert> vertices;

    //get the number of vertices in the graph from input file, add vertices to graph and vector of vert structs
    int numVertices = addVertices(argv[1],dGraph,vertices);

    //sort vector
    shellsort(vertices);

    //build graph
    createGraph(argv[1],dGraph);

    //clear screen
    system("clear");

    //print menu
    printMenu(vertices,numVertices);

    //do dijkstra's
    findPaths(vertices,numVertices,dGraph);

    return 0;
}

//attempt to open input file from command line
ifstream openFile(string fileName)
{
    //try to open a file
    try
    {
        ifstream inputFile;
        inputFile.open(fileName);
        if(inputFile.good())
            return inputFile;
        else
            throw runtime_error("File Not Found");
    }
    //if it fails tell the user the file doesn't exist
    catch(exception e)
    {
        cout << "file " << fileName << " does not exist." << endl;
        exit(1);
    }
}

//count and add vertices to graph
int addVertices(string fileName, Graph<string>& dGraph, vector<vert>& vertices)
{
    //open the inputfile that holds vertices
    ifstream inputFile = openFile(fileName);
    //declare variables for function
    vert v;
    int numVertices = 0;
    string vertex;
    map<string,int> vertexMap;
    //loop through input file
    while(inputFile)
    {
        //get the first item from each line here
        getline(inputFile,vertex,';');
        //if the line isnt empty proceed with the rest of the function
        if(vertex != "")
        {
            //if the vertex hasn't already been counted (in the map) count it and add it to a map
            if(vertexMap.find(vertex) == vertexMap.end())
            {
                v.name = vertex;
                vertices.push_back(v);
                dGraph.AddVertex(vertex);
                numVertices++;
                vertexMap[vertex] = 0;
            }
            //get second vertex on line
            getline(inputFile,vertex,';');
            //if the vertex hasn't already been counted (in the map) count it and add it to a map
            if(vertexMap.find(vertex) == vertexMap.end())
            {
                v.name = vertex;
                vertices.push_back(v);
                dGraph.AddVertex(vertex);
                numVertices++;
                vertexMap[vertex] = 0;
            }
            //move past weight
            getline(inputFile,vertex);
        }
    }
    return numVertices;
}

//build graph based on input file
void createGraph(string fileName, Graph<string>& dGraph)
{
    ifstream inputFile = openFile(fileName);
    string v1, v2, w;
    int weight;
    while(inputFile)
    {
        getline(inputFile,v1,';');
        getline(inputFile,v2,';');
        getline(inputFile,w);
        //convert weight to inst with stringStream
        stringstream weightStream(w);
        weightStream >> weight;
        //add edge to graph
        dGraph.AddEdge(v1,v2,weight);
    }
}

//print beginning menu
void printMenu(vector<vert>& vertices,int numVertices)
{
    cout << "\t\t\t\t^^^^^^^^^^^^^ Dijkstra's Algorithm ^^^^^^^^^^^^^" << endl;
    cout << "\t\t\t\tA weighted Graph has been built for these " << numVertices << " cities: " << endl;
    for(int i = 0; i < numVertices; i++)
    {
        cout << setw(30) << vertices[i].name;
        if((i+1) % 3 == 0)  //if three items have been printed do a new line
            cout << endl;
    }
    cout << endl;
}

//print a row of summary table
void printRow(vector<vert>& vertices, int index)
{
    cout << "\t" << setw(30) << vertices[index].name << setw(15) << vertices[index].dist << setw(15) << vertices[index].prev << endl;
}

//print a row of summary table of vertex is unreachable from the start
void printRowNotOnPath(vector<vert>& vertices, int index)
{
    cout << "\t" << setw(30) << vertices[index].name << setw(15) << "NOT ON PATH" << setw(15) << vertices[index].prev << endl;
}

//find element with lowest distance in the vertex array
int findLowest(vector<vert>& vertices, int numVertices)
{
    int min  = INT_MAX;
    int minIndex;
    for(int i = 0; i < numVertices; i++)
    {
        if(!vertices[i].mark && vertices[i].dist < min)
        {
            min = vertices[i].dist;
            minIndex = i;
        }
    }
    return minIndex;
}

//find index of a specific vertex in array
int indexOf(vector<vert>& vertices, int numVertices, string name)
{
    for(int i = 0; i < numVertices; i++)
    {
        if(vertices[i].name == name)
            return i;
    }
    return -1;
}

//get start of algorithm
string getStart(vector<vert>& vertices, int numVertices)
{
    string start = "";
    cout << "\t\tEnter starting vertex: ";
    cin >> start;
    int index = indexOf(vertices,numVertices,start);
    while(index == -1)
    {
        cout << "\t\tstarting location does not exist ..." << endl;
        cout << "\t\tEnter new starting vertex: ";
        cin >> start;
        index = indexOf(vertices,numVertices,start);
    }
    cout << "\t\t----------------------------------------------------------------------------" << endl;
    cout << "\t" << setw(30) <<"Vertex" << setw(15) << "Distance" << setw(15) << "Previous" << endl;
    vertices[index].dist = 0;
    printRow(vertices,index);
    vertices[index].mark = true;
    return vertices[index].name;
}

//do dijkstras algorithm
void findPaths(vector<vert>& vertices, int numVertices, Graph<string>& dGraph)
{
    //declare varaibles for function
    int markedCount;
    int index;
    int lowestI;
    int startDist;
    Queue<string> adjVertices(50);
    Queue<string> adjCheck(50);  
    
    //get starting point of algorithm
    string start = getStart(vertices,numVertices);

    //see how many vertices aren't reachable from start
    markedCount = onPath(vertices,start,dGraph);

    //keep going while all places haven't been marked
    while(markedCount < numVertices)
    {
        //get connected vertices from graph
        dGraph.GetToVertices(start,adjVertices);
        //make sure this vertex has any adjacent vertices
        if(!adjVertices.isEmpty())
        {
            //loop through queue containing vertices
            while(!adjVertices.isEmpty())
            {
                //get the distance it took to get to the starting value
                startDist = vertices[indexOf(vertices,numVertices,start)].dist;
                //get the index in your array of the first vertex in the Queue
                index = indexOf(vertices,numVertices,adjVertices.getFront());
                //if the current distance to get to that vertex is greater than the distance it takes to get
                //there from the current start then update that vertex's distance and previous
                if(vertices[index].dist > (startDist + dGraph.WeightIs(start,vertices[index].name)))
                {
                    vertices[index].dist = startDist + dGraph.WeightIs(start,vertices[index].name);
                    vertices[index].prev = start;
                }
                //dequeue that vertex from the queue
                adjVertices.dequeue();
            }
            //get the lowest distance vertex, mark it, and print it
            lowestI = findLowest(vertices,numVertices);
            vertices[lowestI].mark = true;
            start = vertices[lowestI].name;
            printRow(vertices,lowestI);
            markedCount++;
        }
        else
        {
            //if there aren't any adjacent vertices move the start to another vertex
            int newStart = indexOf(vertices,numVertices,start);
            if(newStart < numVertices-1)
                start = vertices[++newStart].name;
            else
                start = vertices[--newStart].name;
        }
    }
    for(int i = 0; i < numVertices; i++)
    {
        if(!vertices[i].reachable)
            printRowNotOnPath(vertices,i);
    }
}

//sort vector of vertices using shellSort
void shellsort( vector<vert> & vertices )
{
    for( int gap = vertices.size( ) / 2; gap > 0; gap /= 2 )
        for( int i = gap; i < vertices.size( ); i++ )
        {              
            vert tmp = vertices[ i ];
            int j = i;             
            for( ; j >= gap && tmp.name < vertices[ j - gap ].name; j -= gap )                     
                vertices[ j ] = vertices[ j - gap ];              
            vertices[ j ] = tmp;           
        }
}

//check how many nodes can be reached from a starting node using DFS and return that number
int onPath(vector<vert>& vertices, string start, Graph<string>& dGraph)
{
    //declare variables for function
    int offPath = 1;
    Queue<string> adjQ(50);
    stack<vert> vertStack;
    //push start vertice and set it to reachable
    vertStack.push(vertices[indexOf(vertices,vertices.size(),start)]);
    vertices[indexOf(vertices,vertices.size(),start)].reachable = true;
    //while the stack isn't empty continue to find reachable vertices
    while(!vertStack.empty())
    {
        //get adjacent vertices from current top of the stack and then pop from stack
        dGraph.GetToVertices(vertStack.top().name,adjQ);
        vertStack.pop();
        //while the Queue isnt empty mark vertices as reachable if they aren't already marked
        while(!adjQ.isEmpty())
        {
            if(!vertices[indexOf(vertices,vertices.size(),adjQ.getFront())].reachable)
            {
                vertStack.push(vertices[indexOf(vertices,vertices.size(),adjQ.getFront())]);
                vertices[indexOf(vertices,vertices.size(),adjQ.getFront())].reachable = true;
            }
            adjQ.dequeue();
        }
    }
    //count how many vertices aren't marked as reachable
    for(int i = 0; i < vertices.size(); i++)
    {
        if(!vertices[i].reachable)
            offPath++;
    }
    return offPath;
}