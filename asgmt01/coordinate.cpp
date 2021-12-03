#include <iostream>
#include <iomanip>
#include "coordinate.h"

using namespace std;

Coordinate::Coordinate(int degrees, int minutes, int secondsTenths)
{
	// your code here, or in this constructor's initialization list
	this -> degrees = degrees;
	this -> minutes = minutes;
	this -> secondsTenths =	secondsTenths;
}
Coordinate::Coordinate(void)
{
	// your code here, or in this constructor's initialization list
	degrees = 0;
	minutes = 0;
	secondsTenths = 0;
}

Coordinate::~Coordinate(void)
{
	
}

ostream& operator<<(ostream& out, Coordinate& coord)
{
	// your code here
	out << coord.degrees<< coord.degreeChar << " " << coord.minutes<< "\' " << setprecision(1) << fixed << setw(4) << setfill('0') <<right << (float)coord.secondsTenths / 10 << setfill(' ') << "\" ";
	return out;
}
