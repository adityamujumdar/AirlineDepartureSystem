// @author Aditya Mujumdar
// Description: this is the main program that reads input from keyboard, it then build the adjacency list and performs the depth first search on the graph.

#include "Graph.h"

using namespace std;

void getCityInfo(string oneLine, string& depCityName, LinkedList* arrCityList);
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& price);

int main()
{
	int count = 0;       //a variable for number of nodes
	string oneLine;
	cin >> count;
	cin.ignore(20, '\n');

	//For each line of the input file, you will need to create a LinkedList
	//for a specific departure city, it represents all its reachable arrival
	//cities info.
	LinkedList** arrCityListArray = new LinkedList*[count];
	int i = 0;
	while (i < count) {
		arrCityListArray[i] = new LinkedList();
		i += 1;
	}

	//A string array used to store all the departure city names
	string depCityArray[100];
	CityList* adjacentList = new CityList();
	for (int i = 0; i < count; i++)
	{
		getline(cin, oneLine);
		LinkedList *list = new LinkedList();
		getCityInfo(oneLine, depCityArray[i], list);
		adjacentList->CityListInsert(depCityArray[i], list);
	}

	//create a Graph object by using its constructor
	Graph *object = new Graph(count, adjacentList);

	//print the graph's adjacent list
	cout << "Adjacency List\n" << endl;
	object->printGraph();
	//Do depth first search on above graph
	object->DFS();
	//print the depth first search result
	cout << "\nDepth First Search Result\n" << endl;
	object->printDFSResult();
}

//****************************************************************
//This function from one line, extracts the departure city info.,
//it also extracts each arrival cities info., it then updates the
//parameterized arrCityList accordingly
void getCityInfo(string oneLine, string& depCityName, LinkedList* arrCityList)
{
	string delimiter = ",";
	int pos = 0;
	pos = oneLine.find(delimiter);
	string token = oneLine.substr(0, pos);
	depCityName = token;
	oneLine.erase(0, pos + delimiter.length());

	string oneArrCityInfo, cityName;
	double price;

	//continue run as long as not reach
	//to the end of the line
	while (oneLine.find(delimiter) != -1) {

		pos = oneLine.find(delimiter);
		oneArrCityInfo = oneLine.substr(0, pos);


		// update new arrival city and price
		getArrCityInfo(oneArrCityInfo, cityName, price);
		// add new arrival city name with price
		arrCityList->addArrCity(cityName, price);

		//process the next section
		oneLine.erase(0, pos + delimiter.length());
	}
}

//****************************************************************
//By giving a string, for example 'Dallas(456.5)', this function
//extract the arrival city name 'Dallas' and air ticket price '456.5'
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& price)
{
	string delimiter1 = "(", delimiter2 = ")";
	int pos = oneArrCityInfo.find(delimiter1);

	arrCityName = oneArrCityInfo.substr(0, pos);
	oneArrCityInfo.erase(0, pos + delimiter1.length());
	//use delimiter 2 for price end
	int pos_b = oneArrCityInfo.find(delimiter2);
	price = stod(oneArrCityInfo.substr(0, pos_b));


}

