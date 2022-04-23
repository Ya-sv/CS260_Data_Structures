#include "hashmap.h"
#include <cstring>

using namespace std;

// change the value of this variable to be your own name instead of "I. Forgot"
const char	HashMap::YOUR_NAME[] = "Ya Zou";

HashMap::HashMap(int capacity):
	slots{ new Slot[capacity] },
	capacity{ capacity },
	nStocks {0}
{
}

HashMap::~HashMap(void)
{
	if (slots)
		delete[] slots;
	slots = nullptr;
}

bool HashMap::get(char const * const symbol, Stock& s,
				  unsigned int& symbolHash, unsigned int& hashIndex,
				  unsigned int& usedIndex, unsigned int& seqLength)
	 const
{
	// If the symbol is not found, this function is required
	// to set usedIndex to 0xFFFFFFFF before it returns false.

	// recode these to return the right things
	bool indexFound = false;
	symbolHash = hashStr(symbol);
	hashIndex = symbolHash % capacity;
	usedIndex = hashIndex;
	seqLength = 0;
	int i = 0;
	// Traverse the hash table 
	while (i < capacity && indexFound == false)
	{
		if (slots[usedIndex].slotInfoState == OCCUPIED) // if the slots[index] is occupied 
		{
			if (strcmp(slots[usedIndex].slotStock.stockSymbol, symbol) == 0)// start to check if the slot[index] is the elemnt we want to find
			{

				indexFound = true;
				seqLength = i + 1;
			}
			else // if it is not, then start linear probing to check the next element.
			{
				usedIndex = (usedIndex + 1) % capacity;
				i++;
			}
		}
		else if (slots[usedIndex].slotInfoState == DELETED) // If the slots[index] is deleted then start linear probing to check the next element
		{
			usedIndex = (usedIndex + 1) % capacity;
			i++;
		}
		else // If the hashtable is EMPTY,
		{
			seqLength = i + 1;
			usedIndex = 0xFFFFFFFF;
			i = capacity;
		}
	}

	return indexFound;
}

bool HashMap::put(const Stock& s,
				  unsigned int& symbolHash, unsigned int& hashIndex,
				  unsigned int& usedIndex, unsigned int& seqLength)
{
	// recode these to return the right things
	bool indexFound = false;
	int  uIndex = 0;
	symbolHash = hashStr(s.getSymbol());
	hashIndex = symbolHash % capacity;
	uIndex = usedIndex = hashIndex ;
	seqLength = 0;
	
	// Check is the array is full, if hash tabke is full return false
	if (nStocks >= capacity)
	{
		hashIndex = 0xFFFFFFFF;
		return false;
	}
	if ((nStocks<capacity) && 0 <= uIndex && uIndex  < capacity)// if nStocks less than capacity means that hash table is not full
	{
		
		while (indexFound == false && 0 <= uIndex && uIndex < capacity)
		{   
			 //check if the element has alredy existed in the hash table
			if (slots[usedIndex].slotInfoState == OCCUPIED &&
				strcmp(slots[usedIndex].slotStock.getSymbol(), s.getSymbol()) == 0)
			{
				
				usedIndex = 0xFFFFFFFF;
				return false;
				break;
			}
			else // if it is empty then insert(copy) data into the hash table
			{
				if (slots[usedIndex].slotInfoState != OCCUPIED)
				{
					slots[usedIndex].slotInfoState = OCCUPIED;
					slots[usedIndex].slotStock.stockSymbol = new char[strlen(s.stockSymbol) + 1];
					strcpy(slots[usedIndex].slotStock.stockSymbol, s.stockSymbol);
					slots[usedIndex].slotStock.stockName = new char[strlen(s.stockName) + 1];
					strcpy(slots[usedIndex].slotStock.stockName, s.stockName);
					slots[usedIndex].slotStock.stockSharePrice = s.stockSharePrice;
					slots[usedIndex].slotStock.stockPriceDate = s.stockPriceDate;
					nStocks++;
					seqLength++;
					indexFound = true;
				}
				/*
				* if cllisions happend, start to linear probing procees 
				in oder to find a next empty slot to insert in the hashtable
				*/
				else
				{
					if (uIndex == capacity - 1)
					{
						usedIndex = 0;
						seqLength++;
					}
					else 
					{
						
						usedIndex = (usedIndex + 1) % capacity;
						seqLength++;
					}
					
				}
	
			}

			
		}

	}
	return indexFound;
}

bool HashMap::remove(char const * const symbol, Stock& s,
					 unsigned int& symbolHash, unsigned int& hashIndex,
					 unsigned int& usedIndex, unsigned int& seqLength)
{
	// recode these to return the right things
	symbolHash = hashStr(symbol);
	hashIndex = symbolHash % capacity;
	usedIndex = hashIndex;
	seqLength = 0;
	if (nStocks >= capacity)
	{
		seqLength++;
		usedIndex = 0xFFFFFFFF;
		return false; 
	}
	if (nStocks < capacity)
	{
		// Traverse
		for (int i = 0; i < capacity; ++i)
		{
			// if the element has found, then deletet the element and treturn true
			if (slots[usedIndex].slotInfoState == OCCUPIED &&
				strcmp(slots[usedIndex].slotStock.stockSymbol,symbol) == 0)
			{
				slots[usedIndex].slotInfoState = DELETED;
				if (slots[usedIndex].slotStock.stockSymbol)
				{
					delete[] slots[usedIndex].slotStock.stockSymbol;
					slots[usedIndex].slotStock.stockSymbol = nullptr;
				}
				
				if (slots[usedIndex].slotStock.stockName)
				{
					delete[] slots[usedIndex].slotStock.stockName;
					slots[usedIndex].slotStock.stockName = nullptr;
				}	
				slots[usedIndex].slotStock.stockSharePrice = 0;
				slots[usedIndex].slotStock.stockPriceDate = Date();
				--nStocks;
				seqLength++;
				return true;
			}
			usedIndex = (usedIndex + 1) % capacity;	// if didnt find the elemnt go to the next element
			seqLength++;
		}
		if (slots[usedIndex].slotInfoState == DELETED)
		{
			seqLength++;
			usedIndex = 0xFFFFFFFF;
			return false;
		}
	
		seqLength++;
	//	usedIndex = 0xFFFFFFFF;
		return false;
	}
	return false;
}

unsigned int HashMap::hashStr(char const * const s)
{
	// Hash C string argument using the formula in java.lang.String.hashCode():
	//
	//   s[0]*(31^(n-1)) + s[1]*(31^(n-2)) + ... + s[n-1]
	//
	// s is the array of characters, n is the number of characters in the string,
	// and 31^n means 31 to the nth power.
	//
	// This function is declared static because its result depends
	// only on the characters in the string. You will need to apply
	// the modulo operator to the result of this function to generate
	// the required table index. The place to do this is in the functions
	// that call this function.
	//
	// You can and should do this computation entirely with integers. In other
	// words, there is no need to use floating point values. In particular, you
	// should not use the pow() function from <math.h> in this lab.
	int hashVal{ 0 };
	int keylength = strlen(s);
	for (int i = 0; i < keylength; i++)
	{
		hashVal = 31 * hashVal + s[i];
	}

	return hashVal;
}

ostream& operator<<(ostream& out, const HashMap &h)
{
	if (h.nStocks <= 0)
		out << "no stocks" << endl;
	else 
	{
		// Call the function for printing headers
		
		// Call the function for printing headers
		h.slots->slotStock.displayHeaders(out);
		for (int i = 0; i < h.capacity; i++)
		{
			if (h.slots[i].slotInfoState == h.OCCUPIED)
			{
				out << h.slots[i].slotStock;
			}
		}
	}
	return out;
}
