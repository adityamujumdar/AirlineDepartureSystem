// @author Aditya Mujumdar
// Description: this is a linked list of LinkedList used to represent the adjacency list of a graph.

#include "LinkedList.h"

using namespace std;

//Node represents a departure city info. this includes
//the departure city name, its arrival city list and
//other DFS info.
struct Node
{
	string depCity;
	string color, pi;   //pi is the parent
	int dTime, fTime;   //discover & finish time

	LinkedList* arrCityList;
	struct Node* next;
};

class CityList
{
private:
	struct Node* head;

public:
	CityList();
	void destructor();
	Node* getHead();
	bool CityListInsert(string deptCityName, LinkedList* arrCityList);
	bool CityListDelete(string deptCityName);
	Node* CityListSearch(string deptCityName);
	void CityListDisplay();
};

//constructor
CityList::CityList()
{
	head = NULL;
}

//Destructor
void CityList::destructor()
{
	int cityCount = 0;
	Node *iteratorPtr = head;
	while (iteratorPtr != NULL) {
		head = iteratorPtr->next;
		delete iteratorPtr->arrCityList;
		delete iteratorPtr;
		iteratorPtr = head;
		cityCount++;
	}
	head = NULL;
	cout << "The number of deleted departure cities is: " << cityCount << "\n";
}

//This function is accessor for head
Node* CityList::getHead()
{
	return head;
}

//Given a departure city name, this function searches
//the adjacency list and return a pointer that points
//to it, otherwise it returns NULL
Node* CityList::CityListSearch(string deptCityName)
{
	Node* iteratorPtr = head;
	while (iteratorPtr != NULL) {
		// if the departure city name is the same then break from the while loop
		if (iteratorPtr->depCity.compare(deptCityName) == 0) {
			break;
		}
		else {
			//if not, then iterate through the list.
			iteratorPtr = iteratorPtr->next;
		}
	}
	//return the found node
	return iteratorPtr;
}

//This function inserts a departure city with its arrival city list into
//the cityList. It returns true if the data is inserted successfully
//and false otherwise. Note: departure cities are inserted in alphabetical
//order
bool CityList::CityListInsert(string deptCityName, LinkedList* arrCityList)
{
	Node *previousPtr = NULL;
	Node *iteratorPtr = head;

	bool insertCityBool = false;
	// if the to be inserted node is found then don't insert duplicate node.
	if (CityListSearch(deptCityName) != NULL) {
		insertCityBool = false;
	}
	//else continue adding the node
	else {
		if (head != NULL) {
			//initialize informaiton for the newNode.
			Node* toBeAdded = new Node();
			toBeAdded->depCity = deptCityName;
			toBeAdded->arrCityList = arrCityList;
			toBeAdded->color = "";
			toBeAdded->fTime = 0;
			toBeAdded->dTime = 0;
			toBeAdded->pi = "";
			toBeAdded->next = NULL;
			while (iteratorPtr != NULL) {
				//alphabetical insert
				if (toBeAdded->depCity.compare(iteratorPtr->depCity) < 0) {
					//base case
					if (previousPtr == NULL) {
						toBeAdded->next = head;
						head = toBeAdded;
						insertCityBool = true;
					}
					//insert in an already filled up list
					else {
						previousPtr->next = toBeAdded;
						toBeAdded->next = iteratorPtr;
						insertCityBool = true;
					}
					break;
				}
				previousPtr = iteratorPtr;
				iteratorPtr = iteratorPtr->next;
			}
			// set first node of the linkedlist to addNode information
			if (insertCityBool == false) {
				previousPtr->next = toBeAdded;
				//set bool to true after adding Node
				insertCityBool = true;
			}
		}
		else {
			head = new Node();
			head->depCity = deptCityName;
			head->pi = "NULL";
			head->next = NULL;
			head->fTime = 0;
			head->dTime = 0;
			head->arrCityList = arrCityList;
			head->color = "";
			insertCityBool = true;
		}
	}
	return insertCityBool;
}

//Given a departure city name, this function deletes it from the CityList.
//it returns true if it is deleted successfully and false otherwise
bool CityList::CityListDelete(string deptCityName)
{
	Node* nodetbDeleted = CityListSearch(deptCityName);
	bool deleteCityBool = false;
	if (nodetbDeleted == NULL) {
		deleteCityBool = false;
	}
	else {
		Node *deleteCityNode = head;
		// iterate till node to be deleted
		while (deleteCityNode->next != NULL) {
			if (deleteCityNode->next == nodetbDeleted) {
				break;
			}
			// iterate to the next node
			deleteCityNode = deleteCityNode->next;
		}
		// if the node to be deleted is not head
		if (deleteCityNode != head) {
			deleteCityNode->next = nodetbDeleted->next;
			delete nodetbDeleted;
			deleteCityBool = true;
		}
		// base case
		else {
			delete nodetbDeleted;
			head = NULL;
			deleteCityBool = true;
		}
	}
	return deleteCityBool;
}

//This function print the CityList on screen. It will
//print departure cities in alphabetical order, and for
//each departure city's reachable arrival city, it will
//also display them in alphabetical order
void CityList::CityListDisplay()
{
	Node* iteratorPtr = NULL;
	iteratorPtr = head;
	while (iteratorPtr != NULL) {
		cout << left;
		cout << setw(15) << iteratorPtr->depCity;
		iteratorPtr->arrCityList->printArrCityList();
		iteratorPtr = iteratorPtr->next;

	}
}
