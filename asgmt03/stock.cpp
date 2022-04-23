#include <iomanip>
#include <cstring>
#include "stock.h"

using namespace std;

Stock::Stock(char const * const symbol, char const * const name, int sharePrice, Date priceDate)
{
	// Clear before allocate 
	stockSymbol = new char[strlen(symbol) + 1];
	strcpy(stockSymbol, symbol);
	stockName = new char[strlen(name)+ 1];
	strcpy(stockName, name);
	stockSharePrice = sharePrice;
	stockPriceDate = priceDate;
}

Stock::Stock(void):
	stockSymbol{ nullptr },
	stockName{ nullptr },
	stockSharePrice{ 0 },
	stockPriceDate { Date()}
{
}

Stock::~Stock(void)
{
	if (stockSymbol != nullptr)
		delete[] stockSymbol;
	if (stockName != nullptr )
		delete[] stockName;
}

char const * const Stock::getSymbol(void) const
{
	return stockSymbol;	// change this to return the actual stock symbol
}


//you can choose to implement any of the next 3 items if necessary --
//if not, feel free not to implement them

Stock::Stock(const Stock& s)
{
	stockSymbol = new char[strlen(s.stockSymbol) + 1];
	strcpy(stockSymbol, s.stockSymbol);
	stockName = new char[strlen(s.stockName) + 1];
	strcpy(stockName, s.stockName);
	stockSharePrice = s.stockSharePrice;
	stockPriceDate = s.stockPriceDate;
}

/*Stock& Stock::operator=(const Stock& s)
{
	return *this;
}

Stock& Stock::operator=(Stock const * const s)
{
	return *this;
}
*/

// display column headers for printout of stocks
void Stock::displayHeaders(ostream& out)
{
	// print something like this:
	out << "symbol   " << "name                              " << "price    " << "     date" << endl;
	out << "------   ----                              -----	 ---- " << endl;
}

// print share price as DOLLARS
// (e.g. 2483 would print out as 24.83 and 200 would print out as 2.00)
ostream& operator<<(ostream& out, const Stock& s)
{
	// Print the information which added in hash table
	out <<left <<setw(8) << s.stockSymbol
		<< setw(35) << s.stockName
	    << setw(2) << s.stockSharePrice / 100 << ".";
	if (s.stockSharePrice % 100 < 10)
		out << "0";
	out << s.stockSharePrice % 100 << "   "
		 << s.stockPriceDate;
	return out;
}
