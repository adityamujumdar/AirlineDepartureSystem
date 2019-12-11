// @author Aditya Mujumdar
// Description: this is a linked list used to store arrival cities

#include <iostream>
#include <iomanip> //to format the output
#include <string>

using namespace std;

//struct ArrCity represents an arrival city information
struct ArrCity
{
	string arrCity;
	double price;
	struct ArrCity * next;
};

//class LinkedList will contains a linked list of arrival cities
class LinkedList
{
private:
	struct ArrCity* head;


public:
	LinkedList();
	~LinkedList();
	ArrCity* getHead();
	bool isFound(string aCity);
	bool addArrCity(string aCity, double price);
	bool removeArrCity(string aCity);
	void printArrCityList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
	head = NULL;
}

//Destructor
//Before termination, the destructor is called to free the associated memory.
//It deletes all the ArrCitys including the head and finally prints the number
//of ArrCitys deleted by it.
LinkedList::~LinkedList()
{
	ArrCity* ptr = head;
	int cityCount = 0;
	while (ptr != NULL) {
		ptr = head;
		head = head->next;
		delete ptr;
		cityCount += 1;
	}
	head = NULL;
	cout << "The number of deleted arrival cities are: " << cityCount << "\n";
}

//Accessor to the header of the linked list
ArrCity* LinkedList::getHead()
{
	return head;
}

//A function to check if the parameterized arrival city is
//inside the LinkedList or not. Return true if it exists and
//false otherwise.
bool LinkedList::isFound(string aCity)
{
	ArrCity *iteratorPtr = head;
	bool foundBool = false;
	while (iteratorPtr != NULL) {
		//if the strings are same then found the node. set bool to true and break
		if (iteratorPtr->arrCity.compare(aCity) == 0) {
			foundBool = true;
			break;
		}
		else {
			//else keep iterating through the list
			iteratorPtr = iteratorPtr->next;
		}
	}
	//return boolean
	return foundBool;
}

//Creates a new ArrCity and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of the ArrCitys
//while inserting it into the list. Note: you cannot insert duplicated ArrCitys
//Return value: true if it is successfully inserted and false otherwise
bool LinkedList::addArrCity(string aCity, double price)
{
	ArrCity *previousPtr = NULL;
	bool addedBool = false;
	ArrCity *iteratorPtr = head;
	// if duplicate city of the given name is found, return false
	if (isFound(aCity) == true) {
		addedBool = false;
	}
	else {
		//fill in a non-empty list
		if (head != NULL) {
			// new node to be added
			ArrCity *addNode = new ArrCity();
			addNode->arrCity = aCity;
			addNode->next = NULL;
			addNode->price = price;
			while (iteratorPtr != NULL) {
				//alphabetical insert
				if (addNode->arrCity.compare(iteratorPtr->arrCity) < 0) {
					if (previousPtr != NULL) {
						previousPtr->next = addNode;
						addNode->next = iteratorPtr;
						addedBool = true;
					}
					else {
						//add to head
						addNode->next = head;
						head = addNode;
						addedBool = true;
					}
					break;
				}
				previousPtr = iteratorPtr;
				iteratorPtr = iteratorPtr->next;
			}

			if (addedBool == false) {
				// if inside this scope, insertion operation hasn't took place
				previousPtr->next = addNode;
				addedBool = true;
			}
		}
		//base case
		else {
			head = new ArrCity();
			head->arrCity = aCity;
			head->next = NULL;
			head->price = price;
			addedBool = true;
		}
	}
	return addedBool;
}

//Removes the given ArrCity from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeArrCity(string aCity)
{
	ArrCity *currentNode = head;
	bool deleteBool = false;
	ArrCity *nextNode = head->next;
	if (head->arrCity == aCity) {
		ArrCity *iteratorPtr = head->next;
		delete head;
		deleteBool = true;
		iteratorPtr = head;
	}
	else {
		while (nextNode != NULL) {
			//compare the nodes if they are equal, delete the next and move on to previous nodes.
			if (nextNode->arrCity.compare(aCity) == 0) {
				currentNode->next = nextNode->next;
				delete nextNode;
				deleteBool = true;
				break;
			}
			//iterate the list
			currentNode = currentNode->next;
			nextNode = nextNode->next;
		}
	}
	return deleteBool;
}


//Prints all the arrival cities info. in the linked list starting from the head.
void LinkedList::printArrCityList()
{
	struct ArrCity *temp = head;
	if (head == NULL)
	{
		cout << "The arrival city list is empty\n";
		return;
	}
	while (temp != NULL)
	{
		cout << temp->arrCity << fixed << setprecision(2) << "(" << temp->price << "), ";
		temp = temp->next;
	}
	cout << "\n";
}
