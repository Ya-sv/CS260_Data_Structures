#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "fire.h"

using namespace std;

static const int	NAME_COL_WIDTH{ 26 };

Fire::Fire(const Fire::District district, const char* name,
	int latDeg, int latMin, int latSec, int longDeg, int longMin, int longSec)
{
	// your code here, or in this constructor's initialization list
	this->latitude = Coordinate(latDeg, latMin, latSec);
	this->longitude = Coordinate(longDeg, longMin, longSec);
	this->district = district;
	this->name = new char[strlen(name) + 1];
	strcpy(this ->name, name);
	
}

Fire::Fire(const Fire::District district, const char* const name,
	Coordinate latitude, Coordinate longitude)
{
	// your code here, or in this constructor's initialization list
	this->latitude = latitude;
	this->longitude = longitude;
	this->district = district;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	
}

Fire::Fire()
{
	// your code here, or in this constructor's initialization list
	this->district = District();
	name = nullptr;
    this->latitude = Coordinate() ;
	this->longitude = Coordinate() ;
	
}

Fire::Fire(const Fire& fire)
{
	// your code here, or in this constructor's initialization list
	this->district =  fire.district;
	this->name = new char[strlen(fire.name) + 1];
	strcpy(this->name, fire.name);
	this->latitude = fire.latitude;
	this->longitude= fire.longitude;
	
}

Fire::~Fire()
{	
	
}

bool operator<(const Fire& fire1, const Fire& fire2)
{
	cout << "< overloaded constructor called" << endl;
	return false;
}

bool operator==(const Fire& fire1, const Fire& fire2)
{
	// your code here
	cout << "== overloaded constructor called" << endl;

	return false;
}

void Fire::displayColumnHeadings(ostream& out)
{
	// your code here

	out << "-----------------------   ----------------    --------------   -------------" << endl;
}

std::ostream& operator<<(std::ostream& out, Fire::District district)
{
	// your code here	
	
	switch (district) 
	{
		case Fire::District ::Astoria:
			out << "Astoria";
			break;
		case Fire::District::Columbia_City:
			out << "Columbia_City";
			break;
		case Fire::District::Dallas:
			out << "Dallas";
			break;
		case Fire::District::Forest_Grove:
			out <<"Forest_Grove";
			break;
		case Fire::District::Molalla:
			out  <<"Molalla";
			break;
		case Fire::District::Philomath:
			out << "Philomath";
			break;
		case Fire::District::Santiam:
			out << "Santiam";
			break;
		case Fire::District::Tillamook:
			out << "Tillamook";
			break;
		case Fire::District::Toledo:
			out << "Toledo";
			break;
		default:
			out << "N_DISTRICTS";
			break;
	}
	
	return out;
}

ostream& operator<<(ostream& out, Fire* fire)
{
	// your code here
	
	out << fire->getName() << "\t" << fire->getDistrict()  << "\t\t" << fire->longitude <<"\t" << fire->latitude;

	return out;
}
