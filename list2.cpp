#include <iomanip>
#include "list2.h"

using namespace std;

List2::List2(void)
{
	// your code here, or in this constructor's initialization list
	headByName = nullptr;
	headByDistrict = nullptr;
	length = 0;
}

List2::Node::Node(const Fire& fire)
{
	this->fire = fire;
	nextByName = nullptr;
	nextByDistrict = nullptr;
	// your code here, or in this constructor's initialization list
	//this->fire = Fire(fire);
	//this->nextByName = nullptr;
	//this->nextByDistrict = nullptr;	
}

List2::~List2(void)
{
	
}

Fire* const List2::find(const char* const name) const
{
	// your code here
	Node* current = headByName;
	// Check if the list is empty
	if (headByName == nullptr)
	{
		cout << "Oppps!!The list is empty!! " << endl;
		return nullptr;
	}
	else {
		while (current != nullptr)
		{
			if (strcmp(current->fire.getName(), name) == 0)
			{
				return &(current->fire);
			}
			current = current->nextByName;
		}
	}

	return nullptr;
}

void List2::add(const Fire& fire)
{
	Node* newNode = new Node(fire);

	// Add the name thread in the linked list
	Node* Curr = headByName;
	Node* prev = nullptr;

	Node* CurrByDistrict = headByDistrict;
	Node* prevByDistrict = nullptr;
	//First Entry Insert in an empty linked list
	if (headByName == nullptr && headByDistrict == nullptr)
	{
		headByName = newNode;
		Curr = headByName;
		headByDistrict = newNode;
		CurrByDistrict = headByDistrict;
		length++;
		return;
	}

	prev = Curr;
	while (strcmp(Curr->fire.getName(), newNode->fire.getName()) < 0)
	{
		prev = Curr;
		Curr = Curr->nextByName;
		if (Curr == nullptr)
			break;
	}
	//This is the first Item in the list.  Add it at head
	if (Curr == headByName)
	{
		newNode->nextByName = headByName;
		headByName = newNode;
	}
	//If Curr = null, then this is the last item in the list.  Add at the end.
	else if (Curr == nullptr)
	{
		if (prev != NULL)
		{
			prev->nextByName = newNode;
			newNode->nextByName = nullptr;
		}

	}
	//curr != null, it is somewhere in the middle
	else // Insert in the middle of the list
	{
		newNode->nextByName = Curr;
		prev->nextByName = newNode;
	}


    // Add the district thread
	/*Insert a node which contains both district thread and name  thread in an empty list
    Because both thread is the same case to insert in an empty list
    */
	prevByDistrict = CurrByDistrict;
	//Traverse the district thread of list in order to insert in alphbetical order
	while (CurrByDistrict->fire.getDistrict() <= newNode->fire.getDistrict()) //district equal and current name is less than newnode -> name
	{
		if ((strcmp(newNode->fire.getName(), CurrByDistrict->fire.getName()) <= 0) &&
			(CurrByDistrict->fire.getDistrict() == newNode->fire.getDistrict()))
			break;
		prevByDistrict = CurrByDistrict;
		CurrByDistrict = CurrByDistrict->nextByDistrict;
		if (CurrByDistrict == nullptr)
			break;
	}
	//This is the first Item.  Add it to the Head
	if (CurrByDistrict == headByDistrict)
	{
		newNode->nextByDistrict = headByDistrict;
		headByDistrict = newNode;
	}
	//This is the Last Item.  Insert at the end
	else if (CurrByDistrict == nullptr)// Insert at the end
	{
		prevByDistrict->nextByDistrict = newNode;
		newNode->nextByDistrict = nullptr;
	}
	else // Insert in the middle 
	{
		newNode->nextByDistrict = CurrByDistrict;
		prevByDistrict->nextByDistrict = newNode;
	}
	
	length++;
}
// your code here
// Remove the fire with the specified name. Returns true if it
// found and removed the fire, false if it did not find the fire.
bool List2::remove(const char* const name)
{
	// your code here
	Node* CurrName = headByName;
	Node* PrevName = nullptr;

	//Step1: check if the list is empty, if it is empty retur false
	if ((headByName == nullptr) && (headByDistrict == nullptr))
		return false;

	/*Step2: check if there is only one node in the list,
	if the node equals to name then delete the only node in the list */
	if ((headByName->nextByName == nullptr) && (headByDistrict->nextByDistrict == nullptr))
	{
		if (strcmp(headByName->fire.getName(), name) == 0)
		{
			//delete node;
			headByName = nullptr;
			headByDistrict = nullptr;
			length--;
			return true;
		}
		else
			return false;
	}

	//Step3: Traverse the list and find the name to delete 
	while (CurrName != nullptr)
	{
		// Delete the node
		if (strcmp(CurrName->fire.getName(), name) == 0)
		{
			break;
		}
		
		PrevName = CurrName;
		CurrName = CurrName->nextByName;
	}
	
	// Find the name of district thread and delete it
	Node* CurrDistrict= headByDistrict;
	Node* PrevDistrict = nullptr;
	while(CurrDistrict != nullptr)
	{
		if (strcmp(CurrDistrict->fire.getName(), name) == 0)
		{
			break;
		}
		
		PrevDistrict = CurrDistrict;
		CurrDistrict = CurrDistrict->nextByDistrict;
	}

	if (CurrName == nullptr || strcmp(CurrName->fire.getName(), name) != 0)
		return false;
	if (PrevName == nullptr)
	{
		//first in name list
		headByName = CurrName->nextByName;
		headByDistrict = CurrDistrict->nextByDistrict;	
	}
	else if (CurrName->nextByName == nullptr)
	{
		//last in name list
		PrevName->nextByName = nullptr;
		PrevDistrict->nextByDistrict = nullptr;	
	}
	else
	{
		//middle of name list
		PrevName->nextByName = CurrName->nextByName;
		PrevDistrict->nextByDistrict = CurrDistrict->nextByDistrict;	
	}

	delete CurrName;
	length--;
	return true;
	
	
}
	

int List2::getLength(void) const
{
	if (length >= 0)
		return length;
	else
		cout << "something wrong " << endl;

}

ostream& operator<<(ostream& out, const List2& list)
{
	// your code here
	// Print out the linked list by alphbetical sorted oreder of name thread
	List2::Node* tempByName = list.headByName;
	tempByName->fire.displayColumnHeadings(out);
	out <<left << setw(26)<< "name" << setw(20) << "district" << setw(17) << "longtitude" << setw(6) << "latitude" << endl;
	tempByName->fire.displayColumnHeadings(out);
	static const unsigned char		degreeChar{ 0xB0 };
	while (tempByName)
	{
		out << left <<setw(26)<< tempByName->fire.getName()<<setw(21) << tempByName->fire.getDistrict() 
		    << tempByName->fire.getLongitude().getDegrees()  << degreeChar << " " 
		    << setw(2) << setfill('0') << right << tempByName->fire.getLongitude().getMinutes()<< "\' " 
			<< setprecision(1) << fixed << setw(4) << setfill('0') << right 
			<< (float)tempByName->fire.getLongitude().getSecondsTenths()/10 << setfill(' ') << "\" "
			
		    <<" " << tempByName->fire.getLatitude().getDegrees() << degreeChar << " "
			<< setw(2) << setfill('0') << right <<tempByName->fire.getLatitude().getMinutes() << "\' "
			<< setprecision(1) << fixed << setw(4) << setfill('0') << right 
			<< (float)tempByName->fire.getLatitude().getSecondsTenths()/10 << setfill(' ') << "\" " << endl;
		tempByName = tempByName->nextByName;
	}


	// Print out the linked list by Alphbetical sorted order of district thread
	List2::Node* tempByDistrict = list.headByDistrict;   
	tempByDistrict->fire.displayColumnHeadings(out);     // Print out the dot line
	out << left << setw(26) << "name" << setw(20) << "district" << setw(17) << "longtitude" << setw(6) << "latitude" << endl;
	tempByDistrict->fire.displayColumnHeadings(out);    // Print out the dot line
	while (tempByDistrict)
	{
		// Print out longtitude
		out <<left << setw(26)<< tempByDistrict->fire.getName() <<setw(21) << tempByDistrict->fire.getDistrict()
		    << tempByDistrict->fire.getLongitude().getDegrees() << degreeChar << " " 
			<< setw(2) << setfill('0') << right << tempByDistrict->fire.getLongitude().getMinutes() << "\' "
			<< setprecision(1) << fixed << setw(4) << setfill(' ') << right
			<< (float)tempByDistrict->fire.getLongitude().getSecondsTenths()/10 << setfill(' ') << "\" "
		    
			// Print out Latitudes
			<<" " << tempByDistrict->fire.getLatitude().getDegrees() << degreeChar << " "
			<< setw(2) << setfill('0') << right << tempByDistrict->fire.getLatitude().getMinutes() << "\' "
			<< setprecision(1) << fixed << setw(4) << setfill('0') << right
			<<(float) tempByDistrict->fire.getLatitude().getSecondsTenths()/10 << setfill(' ') << "\" " << endl;
		tempByDistrict = tempByDistrict->nextByDistrict;
	}

	return out;
}
