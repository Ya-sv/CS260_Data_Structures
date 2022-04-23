#include "gcs.h"
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

GCS::GCS(char const * const name):
	name{ nullptr}
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

GCS::~GCS()
{
	if (name)
	{
		delete[] name;
		name = nullptr;
	}
}

GCS& GCS::operator=(const GCS& gcs)
{
	setName(gcs.name);
	return *this;
}

GCS::GCS(const GCS& source)
{
	this->name = new char[strlen(source.name) + 1];
	strcpy(this->name, source.name);
}

void GCS::setName(char const * const name)
{
	if (this->name)
	{
		delete[] this->name;
		this -> name = NULL;
	}
	if (!name)
	{
		this->name = nullptr;
	}
	else
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
}

bool operator<(const GCS& gcs1, const GCS& gcs2)
{
	if (strcmp(gcs1.getName(), gcs2.getName()) < 0)
		return true;
	else
		return false;
}

bool operator==(const GCS& gcs1, const GCS& gcs2)
{
	if (strcmp(gcs1.name, gcs2.name) == 0)
		return true;
	else
		return false;
}

ostream& operator<<(ostream& out, const GCS& gcs)
{
	out << gcs.name;
	return out;
}
