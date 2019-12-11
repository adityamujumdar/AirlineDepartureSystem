// @author Aditya Mujumdar
// Description: This class defines a directed graph

#include "CityList.h"

using namespace std;

class Graph
{
private:
	int numOfNode;   //number of nodes in the graph
	int time;   //a global timer used to find each node dTime,fTime
	CityList* adjacentList; //a linked list of LinkedList

public:
	Graph(int numOfNode, CityList* adjacentList);
	void destructor();

	void printGraph();
	void DFS();
	void DFS_Visit(Node *node);
	void printDFSResult();
};

//***************************************************************
//Constructor
Graph::Graph(int numOfNode, CityList* adjacentList)
{
	this->adjacentList = adjacentList;
	this->numOfNode = numOfNode;
	this->time = 0;
}

//*******************************************************************
//Destructor. We explicitly defines it as a function, in order to be
//able to call it from other functions, to make sure memory is released.
void Graph::destructor()
{
	delete adjacentList;
}

//*******************************************************************
//This function prints the graph. The graph is represented by adjacency
//list. It will print the adjacency list.
void Graph::printGraph()
{
	adjacentList->CityListDisplay();
}

//*******************************************************************
//This function performs the DFS on the graph. Note: the DFS starts
//from the first node in adjacency list
void Graph::DFS()
{
	Node* iteratorPtr = adjacentList->getHead();
	while (iteratorPtr != NULL)
	{
		iteratorPtr->color = "WHITE";
		iteratorPtr->pi = "none";
		iteratorPtr = iteratorPtr->next;
	}
	iteratorPtr = adjacentList->getHead();
	while (iteratorPtr != NULL)
	{
		if (iteratorPtr->color == "WHITE") {
			DFS_Visit(iteratorPtr);
		}
		iteratorPtr = iteratorPtr->next;
	}
}

//*******************************************************************
//This function performs the DFS-Visit from the parameterized node
void Graph::DFS_Visit(Node* node)
{
	Node* deptCityIter;
	// white vertex time set
	this->time += 1;
	node->dTime = time;
	node->color = "GRAY";
	//get the arrival cities reference
	ArrCity *iteratorPtr = node->arrCityList->getHead();
	//explore edge(node,deptCityIter)
	while (iteratorPtr != NULL) {
		// set to searched node in city list
		deptCityIter = adjacentList->CityListSearch(iteratorPtr->arrCity);
		if (deptCityIter->color == "WHITE") {
			deptCityIter->pi = node->depCity;
			DFS_Visit(deptCityIter);
		}
		iteratorPtr = iteratorPtr->next;
	}
	//blacken node
	node->color = "BLACK";
	time += 1;
	node->fTime = time;
}

//**************************************************************
//This function prints the parent, dTime & fTime info. of
//each node after DFS.
void Graph::printDFSResult()
{
	//start iterating with head
	Node *goThrough = adjacentList->getHead();
	cout << left;
	cout << setw(15) << "City Name" << setw(10) << "Parent"
		<< setw(10) << "dTime" << setw(10) << "fTime" << endl;

	cout << setw(15) << "=========" << setw(10) << "======"
		<< setw(10) << "=====" << setw(10) << "=====" << endl;

	//iterate through the list and print all the nodes and their information
	while (goThrough != NULL) {
		cout << setw(15) << goThrough->depCity << setw(10)
			<< goThrough->pi << setw(10) << goThrough->dTime
			<< setw(10) << goThrough->fTime << "\n";



		goThrough = goThrough->next;
	}
}
