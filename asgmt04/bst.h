#ifndef _BST_H_
#define _BST_H_

// do not change this file except within the private section of the BST class,
// where you can declare variables and/or functions

#include "gcs.h"

class BST								// a Binary Search Tree (BST)
{
public:
	static const char	YOUR_NAME[];		// used for printing out programmer's name
	static const bool	PREMIUM_VERSION;	// used to designate Regular vs. Premium

	BST(int capacity = 5);				// constructor (default if no argument supplied)
	~BST();								// destructor

	void insert(const GCS& gcs);		// insert a new item into BST
	bool remove(const char* key);		// remove item associated with key from BST
	bool retrieve(const char* key, GCS const *& gcs) const;	// retrieve item associated with key, if any
	int getSize(void) const;			// return number of items contained in the BST

	// see comments in bst.cpp for what these member functions do
	void displayArrayOrder(std::ostream& out) const;
	void displayPreOrder(std::ostream& out) const;
	void displayInOrder(std::ostream& out) const;
	void displayPostOrder(std::ostream& out) const;

private:
	// specify what is stored at each position in the array
	// (you can add additional items to this struct)
	struct Item
	{
		GCS		gcs;		// the GCS instance must be specified this way, NOT as a pointer
		bool    empty = true;
	};

	// pointer to the array
	Item*	items;
	int currentSize;      // It contains how many current items in the tree
	int capacity;         // the size of array
	bool checkLeft(int& index)const;
	bool checkRight(int& index) const;
	bool checkLeafNode(int index)const;
	void PrintOrder(int index, std::ostream& out) const;
	void  preOrder(int index, std::ostream& out)const;
	void  inOrder(int index, std::ostream& out)const;
	void  postOrder(int index, std::ostream& out)const;
	void increaseArray();
	void displayHearders(std::ostream& out) const;
};

#endif
