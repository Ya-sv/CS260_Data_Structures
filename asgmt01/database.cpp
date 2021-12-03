#include <cstring>
#include "database.h"
#include "list2.h"

using namespace std;

Database::Database()
{
	// your code here, or in this constructor's initialization list
	
}

Database::~Database()
{
	// your code here
}

void Database::insert(const Fire& fire)
{
	// your code here
	list2.add(fire);
}

Fire* const Database::find(const char* const name) const
{
	// your code here

	if (Fire * f = list2.find(name))
		return f;
	else
		return nullptr;
}

bool Database::remove(const char* const name)
{
	// your code here
	if (list2.remove(name)) 
		return true;
	else
		return false;   
}

ostream& operator<<(ostream& out, const Database& database)
{
	// your code here
	out << database.list2;
	return out;
}
