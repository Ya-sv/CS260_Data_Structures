#include <iostream>
#include <iomanip>
#include <cstring>
#include "bst.h"

using namespace std;

// change the value of this variable to be your own name instead of "I. Forgot"
const char	BST::YOUR_NAME[]{"Ya Zou"};

// change the value of this variable to true if you're doing the Premium version
const bool	BST::PREMIUM_VERSION{true};

BST::BST(int capacity):
	items{new Item[capacity] },
	currentSize {0},
	capacity {capacity}
{
}

BST::~BST()
{
	if (items)
	{
		delete[] items;
		items = nullptr;
	}
}


bool BST::checkLeft( int& index) const
{

	if ((2 * index + 1) < capacity)
	{
		index = (2 * index) + 1;
		return true;

	}

	else
	{
		return false;
	}

}


bool BST::checkRight(int& index) const
{

	if ((2 * index + 2) < capacity)
	{
		index = (2 * index) + 2;
		return true;
	}
	else
	{
		return false;
	}

}


bool BST::checkLeafNode(int index)const
{
	if ((2 * index + 1) >= capacity - 1 || (items[2 * index + 1].empty && items[2 * index + 2].empty)) 
	{
		return true;
	}
	else 
	{
		return false;
	}

}
// insert a new item into the BST
void BST::insert(const GCS& gcs)
{
	 int index = 0;
	if (currentSize == 0)
	{
		// if the tree is empty, index 0 is always be the root of the tree
		items[index].gcs = gcs;
		items[index].empty = false;
		currentSize++;
	}
	// else start to compare gcs to the roott node, if gcs is greater than root node go to the right subtree
	// if it is smaller go to let sub-tree
	else
	{
	
		while(items[index].empty == false)
		{
			// Case 2: insert in left
			if (gcs < items[index].gcs)
			{
						
				if (checkLeft(index) == false )
				{
					increaseArray();
					checkLeft(index);
				}
				if (items[index].empty == true)
				{
					
					items[index].gcs = gcs;
					items[index].empty = false;
					currentSize++;
					return;
				}
				
			}
			// insert right child
			else if ( items[index].gcs < gcs)
			{
				
				/*
				* Check if the rightIndx is out of bound,
				if the right indx is out of the bound increase the array
				by calling the helper function increaseArray() and go left then insert the name
				*/
				if (checkRight(index) == false)
				{
					increaseArray();
					checkRight(index);
				}
				else if (items[index].empty == true)
				{
					items[index].gcs = gcs;
					items[index].empty = false;
					currentSize++;
					return;
				}
				
			}
		}

	}

}

// retrieve item associated with key
// returns true if it finds key, false if it can't
bool BST::retrieve(const char* key, GCS const *& gcs) const
{
	int index = 0;
	int i = 0;

	do 
	{
		if (strcmp(key, items[index].gcs.getName()) == 0)
		{
			gcs = &items[index].gcs;
			return true;
		}
		else if (strcmp(key, items[index].gcs.getName()) < 0)
		{
			index = (2 * index + 1);
			i++;
			continue;
		}
		else if (strcmp(key, items[index].gcs.getName()) > 0)
		{
			index = (2 * index + 2);
			i++;
			continue;
		}
	} while (i < currentSize && index < capacity);

	return false;
}

// remove item associated with key from BST
bool BST::remove(const char* key)
{
	int index = 0;
	int i = index;
	do
	{
		// check if the tree is empty
		if (items[index].empty)
			return false;
		else if (key == items[index].gcs)
		{
			// Case 1: delete a leaf node
			if (checkLeafNode(index) == true)
			{
				items[index].empty = true;
				currentSize--;
				return true;
			}
			// Case 2: delete a node with only one child
			// wheather has left or right child will satisfy the requirment of one child
		   if ((items[2 * index + 1].empty == false && items[2 * index + 2].empty)
				|| (items[2 * index + 1].empty && items[2 * index + 2].empty == false))
			{
			    i = index;
				//Only has left child
				if ((items[2 * index + 1].empty == false) && (items[2 * index + 2].empty== true))
				{

					checkLeft(i);
					items[index].gcs = items[i].gcs;
					items[i].empty = true;
				}
				// Only has right child
				else
				{
					checkRight(i);
					items[index].gcs = items[i].gcs;
					items[i].empty = true;
				}
				currentSize--;
				return true;
			}
			// Case3: delete a node with two children 
			// check a node must have right and left child will meet the requirment of two chldren
		    // find the smallest value in the right sub-tree a overwrite it with the value and delete the value 
		   else
		   {
			   i = index;
			   checkRight(i);
			   while (((2 * i + 2) < capacity)
				    && (items[2 * i + 2].empty == true)
				    && (items[2 * i + 1].empty== false))
				   {
					   checkLeft(i);
				   }
				   if ((2 * i + 2) < capacity 
					&& items[2 * i + 2].empty == false)
				   {
					   int j = i;
					   while ((2 * j + 2) < capacity
						  && items[2 * j + 1].empty)
					   {
						   checkRight(j);
					   }
					   items[index].gcs = items[i].gcs;
					   items[i].gcs = items[j].gcs;
					   items[j].empty = true;
					   currentSize--;
					   return true;
				   }
				   else 
				   {
					   items[index].gcs = items[i].gcs;
					   items[i].empty = true;
					   currentSize--;
					   return true;
				   }

		   }
		 

		}
		else if (key < items[index].gcs)
			checkLeft(index);
		else if (items[index].gcs < key)
			checkRight(index);


	} while (index < capacity);

	return false;
}

// return number of items contained in the BST
int BST::getSize(void) const
{
	return currentSize;
}

// display items in the tree by traversing the array from beginning to end
void BST::displayArrayOrder(ostream& out) const
{
	// Display headers
	displayHearders(out);
	// Check if the tree is empty
	if (currentSize == 0)
	{
		out << "The tree is empty" << endl;
	}
	else
	{
		for (int i = 0; i < capacity; i++)
		{
			// Print out name
			if (items[i].empty == false)
			{
				out << left << setw(25) << items[i].gcs;
				out << setw(10);
				// Print if it is leaf
				if (checkLeafNode(i) == true)
				{
					out << "leaf";
					out << i << endl;
				}
				else
				{
					// Print index
					out << "  " << i << endl;
				}
			}
			else
			{
				continue;
			}
		}
		out << left << setw(40) << "(items printed)" << "(" << currentSize << ")" << endl;

	}
}


void BST::PrintOrder(int index,std::ostream& out ) const
{
	out << left << setw(25) << items[index].gcs;
	out << setw(10);
	// Print if it is leaf(LEAF) = 0
	if (checkLeafNode(index) == true)
	{
		out << "leaf";
		out << index << endl;
	}
	else
	{
		// Print index
		out << "  " << index << endl;
	}
}

void BST::preOrder(int index, std::ostream& out)const
{

	//root, then left, then right while in bounds of the tree and array
	if (index <= capacity-1 && items[index].empty== false)
	{
		PrintOrder(index,out);
		preOrder(2 * index + 1, out);
		preOrder(index*2 + 2, out);
	}
	index++;

}

// display items in the tree in preorder
void BST::displayPreOrder(ostream& out) const
{
	// display headers
	displayHearders(out);
	int index{ 0 };
	//check if the tree is empty
	if (currentSize == 0)
		throw " The tree is empty!!";
	else 
	{
		 preOrder(index, out);
		out << left << setw(40) << "(items printed)" << "(" << currentSize << ")" << endl;
	}
}

void BST::inOrder(int index, std::ostream& out)const
{
	if ( index <= capacity-1 &&items[index].empty == false)
	{
		inOrder(2 * index + 1, out);
		PrintOrder(index, out);
		inOrder(index * 2 + 2, out);
	}
	index++;

}
// display items in the tree in inorder
void BST::displayInOrder(ostream& out) const
{
	int index = 0;
	// display headers
	displayHearders(out);
	if (currentSize == 0)
		throw " The tree is empty!!";
	else
	{
		inOrder(index, out);
		out << left << setw(40) << "(items printed)" << "(" << currentSize << ")" << endl;
	}
}


void BST::postOrder(int index, std::ostream& out)const
{
	if (index <= capacity - 1 && items[index].empty == false)
	{
		postOrder(2 * index + 1, out);
		postOrder(index * 2 + 2, out);
		PrintOrder(index, out);
	}
	index++;
}
// display items in the tree in postorder
void BST::displayPostOrder(ostream& out) const
{
	// display headers
	displayHearders(out);
	int index = 0;
	if (currentSize == 0)
		throw " The tree is empty!!";
	else
	{
		postOrder(index, out);
		out << left << setw(40) << "(items printed)" << "(" << currentSize << ")" << endl;
	}
}


void BST::increaseArray()
{
	int growby = capacity*2;
	Item* items2 = new Item[growby];
	for (int i = 0; i < capacity ; ++i)
	{
		items2[i].gcs = items[i].gcs;
		items2[i].empty = items[i].empty;
	}
	delete[] items;
	items = items2;
	capacity = growby;
}
// Increaseing the size of the array
void BST::displayHearders(ostream& out)const
{
	out << setw(24) << left << "name"
		<< setw(5) << "leaf?" << "  "
		<< setw(5) << "index" << endl;

	out << setw(24) <<left <<"----                    -----   -----" << endl;
}

