// add code to these functions to make Quack do something useful

#include "quack.h"

using namespace std;

// change the value of this variable to be your own name instead of "I. Forgot"
const char	Quack::YOUR_NAME[]{"Ya Zou"};

// change the value of this variable to true if you're doing the Premium version
const bool	Quack::PREMIUM_VERSION{true};

Quack::Quack(int capacity, int growBy) :
	// replace these initializations with the ones you actually need
	grow{ growBy },
	items{new char[capacity]},
	capacity{capacity}
{
	initArray();	// you are required to call this function here, and
					// it must be the first thing in the constructor body
}

Quack::~Quack(void)
{
	delete[] items;
}

// items are pushed to successively LOWER slots in the circular array
// (except for when the beginning of the array "wraps around" to the end)
bool Quack::pushFront(const char ch)
{
	// Insert in an empty array
	if (front == -1 && back == -1)
	{
		back = front = 0;
		items[front] = ch;
	}
	 /*check if array is full, if it is full, then increase array by grow elemnts*/
	 else if ((back + 1) % capacity == front)
	 {

		char* items2 = new char[capacity+grow];
		for (int i = 0; i < capacity+grow; i++)
		{
			items2[i] = '\0';
		}
		for (int i = 0; i < capacity; i++)
		{
			items2[i] = items[(front + i) % capacity];
		}

		delete[] items;
		items = items2;
		capacity += grow;


		if (front == 0)
			front = capacity - 1 % capacity;
		else
			front = (front - 1) % capacity;
		items[front] = ch;
		
	 } 
	// Insert in a not empty array
	else
	{  
		if (front == 0)
		{
			front = capacity - 1 % capacity;
			items[front] = ch;
		}
		else 
		{
			front = (front - 1) % capacity;
			items[front] = ch;
		}
		
    }
	count++;
	return true;	
}

// items are pushed to successively HIGHER slots in the circular array
// (except for when the end of the array "wraps around" to the beginning)
bool Quack::pushBack(const char ch)
{
	// check if the circular array is empty
	if (front == -1 && back == -1)
	{
		back = front = 0;
		items[back] = ch;
	}
	/*check if circular array is full, 
	if it is full then gow by the grow numbers element */
	else if ((back + 1) % capacity == front)
	{  
		char* items2 = new char[capacity +grow];
		for (int i = 0; i < capacity + grow; i++)
		{
			items2[i] = '\0';
		}
		for (int i = 0; i < capacity; i++)
		{
			items2[i] = items[(front+i)% capacity];
		}
		delete[] items;
		items = items2;
		back = capacity;
		capacity += grow; 
		front = 0;
		items[back] = ch;
	}	
	// Insert in an not empty circular array
	else 
	{
		back  = (back + 1) % capacity;
		items[back] = ch;	
	}
	count++;
	return true;
}

bool Quack::popFront(char& ch)
{
	// Check if the circular array is empty
	if (front == -1 && back == -1)
		return false;
	// check if there is only one element in the circular array
	else if (front == back)
	{
		ch = items[front];
		front = back = -1;	
	}
	/*Pop front,increse front by one position
	in order to pop from the begeining*/
	else
	{
		ch = items[front];
		front = (front + 1) % capacity;
	}
	count--;
	return true;
}

bool Quack::popBack(char& ch)
{
	// Check if the circular array is empty
	if (front == -1 && back == -1)
		return false;
	// check if there is only one elefment in the circular array
	else if (front == back)
	{
		ch = items[back];
		front = back = -1;
	}
	else
	{
		ch = items[back]; // return back
		if (back == 0)
		{
			back = (capacity - 1) % capacity;
		}
		else 
		{
			back = (back - 1) % capacity;
		}	
	}
	count--;
	return true;
}

void Quack::rotate(int r)
{
	int i{ 0 };
	// avoid r is grader than capacity of array
	r= r % capacity;
	if (r > 0)
	{
		for (i = 1; i <= r; i++)
		{
			items[back + 1] = items[front];
			front = (front + 1) % capacity;
			back = (back + 1) % capacity;
		}
	}
	else if (r < 0)
	{
		for (i = 0; i > r; i--)
		{
			if (front < 1)
				front = (capacity + front);
			if (back < 0)
				back = (capacity + back);
			items[front - 1] = items[back];
			back--;
			front--;
		}
	}
	else
	{
		throw " r euqals zero or 7, No changes";
	}
}

void Quack::reverse(void)
{
	int tempFront {front};
	int tempBack  {back};

	char tempChar;
	for (int i = 0; i < count / 2; i++)
	{
		tempChar = items[tempFront];
		items[tempFront] = items[tempBack];
		items[tempBack] = tempChar;
		tempFront = (tempFront + 1) % capacity;
		if (tempBack == 0)
		{
			tempBack = (count - 1) % capacity;
		}
		else
		{
			tempBack = (tempBack - 1) % capacity;
		}
	}
}

int	Quack::itemCount(void)
{
	return count;
}

ostream& operator<<(ostream& out, Quack *q)
{
	int i = q->front;
	if (q->front == -1 && q->back == -1)
		out << "quack: empty" << endl << endl;
	else
	{
		out << "quak: ";
		while (i != q->back)
		{
			out << q->items[i] << "," << " ";
			i = (i + 1) % q->capacity;
		}
		out << q->items[q->back];
	 	out << endl << endl;
	}
	// returning out is ALWAYS required for an operator<< overload
	return out;
}
