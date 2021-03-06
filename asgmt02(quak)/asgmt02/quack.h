#ifndef _QUACK_H_
#define _QUACK_H_

// you can only change this file by adding variables and/or functions to the "private" section

#include <ostream>
#include <iomanip>

class Quack
{
public:
	static const char	YOUR_NAME[];		// used for printing out programmer's name
	static const bool	PREMIUM_VERSION;	// used to designate Regular vs. Premium

	Quack(int capacity, int growBy = 0);
		// capacity: # of slots in array
		// growBy:   # of slots to add to array when it grows, 0 means "don't grow"
	~Quack(void);
	bool pushFront(const char ch);		// push an item onto the front
	bool pushBack(const char ch);		// push an item onto the back
	bool popFront(char& ch);			// pop an item off the front
	bool popBack(char& ch);				// pop an item off the back
	void rotate(int r);					// "rotate" the stored items (see note below)
	void reverse(void);					// reverse the order of the stored items
	int	itemCount(void);				// return the current number of stored items

	void initArray(void)								// initialize contents of array
	{
		for (int i = 0; i < capacity; i++)
			items[i] = '\0';
	}

	void printArray(std::ostream& out)					// print contents of array
	{
		unsigned char	ch;

		out << "[ ";
		for (int i = 0; i < capacity; i++) {
			ch = items[i];
			if (ch == '-')								// print in hex, because using '-' for '\0'
				goto printHex;
			else if (ch >= '!' && ch <= '}')			// ASCII text character
				out << ch << ' ';
			else if (ch == '\0')						// print '\0' as '-'
				out << "- ";
			else										// print everything else as hex
				goto printHex;
			continue;

		printHex:	
			out << std::setw(2) << std::setfill('0') << std::hex << ch << ' ';
			}
		out << ']' << std::endl;
	}

private:
	int     grow;
	char	*items;						// pointer to storage for circular array,
										// each item in the array is a char
	int		capacity;					// # of slots in array
	int count {0 };                     // # of items in current array
	int front {-1};				        // always trace the first element
	int back  {-1};						// always trace the last element
						

public:
	friend std::ostream& operator<<(std::ostream& out, Quack *q);
};

// The following example should make it clear what "rotate" means.
// This is showing you the "logical contents" of the quack, i.e.
// which item is first, which is second, etc. It is NOT showing you
// where the items are in the array.
//
//   quack: a, b, c, d, e, f, g			-- current contents, front is on the left
//   >>> rotate(2)
//   quack: c, d, e, f, g, a, b			-- contents after rotation by +2
//   >>> rotate(-3)
//   quack: g, a, b, c, d, e, f			-- contents after rotation by -3

#endif
