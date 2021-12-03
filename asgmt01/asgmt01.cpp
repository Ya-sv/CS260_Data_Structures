// make NO CHANGES to this file, except to change YOUR_NAME to your actual name
#define _CRTDBG_MAP_ALLOC
#include <cstring>
#include <crtdbg.h>
#include <iostream>
#include "fire.h"
#include "database.h"

using namespace std;

const char			YOUR_NAME[]{ "Ya Zou" };	// change to your own name
static Database* fires;

// Asks Database to insert a Fire. Note what this function does with memory,
// which has implications for how you will (and will not) be able to use
// the Fire instance that's passed to fires->insert.
static void insertFire(Fire::District district,  char* name,
	int latDeg, int latMin, 
	int latSec,
	int longDeg, int longMin, int longSec)
{
	Fire* f;
	char* nm{ new char[strlen(name) + 1] };
	//strcpy(name, nm);
	f = new Fire(district, name, latDeg, latMin, latSec, longDeg, longMin, longSec);
	fires->insert(*f);
	delete[] nm;
	delete f;
}

static void find(char* name)
{
	Fire* fPtr;

	cout << endl << ">>> search for \"" << name << "\"" << endl << endl;
	fPtr = fires->find(name);
	if (fPtr != 0)
		cout << fPtr;
	else
		cout << "not found" << endl;
}

static void removeFire(char* name)
{
	cout << ">>> ";
	if (fires->remove(name))
		cout << "removed";
	else
		cout << "could not remove";
	cout << " \"" << name << "\"" << endl;
}




int main(int argc, char** argv)  
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (argc > 1)				// turn off cout
		std::cout.setstate(std::ios_base::badbit);

	cout << "CS260 - Assignment 1 - " << YOUR_NAME << endl << endl;

	fires = new Database();

	insertFire(Fire::District::Tillamook,(char*) "Strawberry Lane Fire", 45, 35, 212, 123, 57, 7);
	insertFire(Fire::District::Tillamook, (char*)"Bob Straub", 45, 11, 463, 123, 57, 580);
	insertFire(Fire::District::Astoria, (char*)"Mosquito Fire", 46, 9, 215, 123, 57, 573);
	insertFire(Fire::District::Astoria, (char*)"Little Walluski", 46, 8, 276, 123, 45, 360);
	insertFire(Fire::District::Astoria, (char*)"Pig Pen Crossing Fire", 46, 4, 38, 123, 50, 360);
	insertFire(Fire::District::Astoria, (char*)"Round Bale", 46, 6, 328, 123, 55, 180);
	insertFire(Fire::District::Forest_Grove, (char*)"Bishop Scott Fire", 45, 22, 36, 123, 11, 535);
	insertFire(Fire::District::Columbia_City, (char*)"Cox Rd #1", 46, 7, 382, 123, 3, 322);
	insertFire(Fire::District::Forest_Grove, (char*)"Manning Fire #1", 45, 39, 524, 123, 9, 553);
	insertFire(Fire::District::Columbia_City, (char*)"Timber Road #1", 45, 47, 294, 123, 16, 220);
	insertFire(Fire::District::Forest_Grove, (char*)"Kuykendall Field Fire", 45, 20, 575, 123, 12, 424);
	insertFire(Fire::District::Forest_Grove, (char*)"Hartwick Burn Pile", 45, 37, 387, 123, 8, 340);
	insertFire(Fire::District::Columbia_City, (char*)"Prescott Beach #2", 46, 3, 263, 122, 53, 296);
	insertFire(Fire::District::Columbia_City, (char*)"Hwy 47 MP 5", 46, 4, 11, 123, 15, 382);
	insertFire(Fire::District::Forest_Grove, (char*)"Sheltered Nook Bark Fire", 45, 38, 16, 122, 51, 473);
	insertFire(Fire::District::Columbia_City, (char*)"Neer City Road #1", 46, 2, 362, 122, 55, 75);
	insertFire(Fire::District::Columbia_City, (char*)"Wilark Rd", 45, 52, 318, 122, 59, 198);
	insertFire(Fire::District::Columbia_City, (char*)"Pisgah Homes Rd Fire #1", 45, 46, 153, 122, 58, 540);
	insertFire(Fire::District::Columbia_City, (char*)"Anliker Rd #1", 45, 57, 23, 122, 58, 246);
	insertFire(Fire::District::Forest_Grove, (char*)"Fir Crest Rd #1", 45, 16, 34, 123, 14, 215);
	insertFire(Fire::District::Forest_Grove, (char*)"Fire Break 1", 45, 37, 230, 123, 22, 140);
	insertFire(Fire::District::Forest_Grove, (char*)"Stubb Stewart Fire", 45, 44, 240, 123, 11, 392);
	insertFire(Fire::District::Dallas, (char*)"Socialist Valley", 44, 52, 240, 123, 26, 480);
	insertFire(Fire::District::Toledo, (char*)"Olalla Rd Fire", 44, 39, 590, 123, 55, 559);
	insertFire(Fire::District::Dallas, (char*)"Gold Creek", 45, 2, 432, 123, 32, 31);
	insertFire(Fire::District::Dallas, (char*)"Riley Central Fire", 44, 53, 510, 123, 36, 144);
	insertFire(Fire::District::Dallas, (char*)"Tindle Creek Fire", 45, 6, 277, 123, 30, 247);
	insertFire(Fire::District::Toledo, (char*)"Little Euchre", 44, 47, 190, 123, 53, 330);
	insertFire(Fire::District::Philomath, (char*)"Peterson Road", 44, 27, 519, 123, 23, 159);
	insertFire(Fire::District::Santiam, (char*)"Alder Creek", 44, 47, 97, 122, 41, 552);
	insertFire(Fire::District::Molalla, (char*)"Wagon Wheel Fire", 45, 11, 491, 122, 34, 348);
	insertFire(Fire::District::Molalla, (char*)"Paha Piles", 45, 22, 149, 122, 11, 50);
	insertFire(Fire::District::Santiam, (char*)"Ike Mooney Pile", 45, 0, 83, 122, 45, 178);
	insertFire(Fire::District::Molalla, (char*)"Vick Rd", 45, 9, 527, 122, 35, 563);
	insertFire(Fire::District::Santiam, (char*)"Shepards Pie Fire", 44, 43, 470, 122, 26, 560);
	insertFire(Fire::District::Molalla, (char*)"Beavercreek Brush", 45, 14, 20, 122, 28, 410);
	insertFire(Fire::District::Molalla, (char*)"Hwy 211 Slash", 45, 22, 133, 122, 17, 578);

	cout << *fires << endl;

	cout << endl;
	removeFire((char*)"Beavercreek Brush");
	removeFire((char*)"Peterson Road");
	removeFire((char*)"Vick Rd");
	removeFire((char*)"No Fire");
	cout << endl;

	cout << *fires;

	cout << endl << ">>> inserting Wall St Pile" << endl << endl;
	insertFire(Fire::District::Molalla, (char*)"Wall St Pile", 45, 9, 458, 122, 26, 380);

	cout << *fires;

	find((char*)"Wall St Pile");

	find((char*)"No Fire");

	cout << endl;

	delete fires;
	return 0;
}

