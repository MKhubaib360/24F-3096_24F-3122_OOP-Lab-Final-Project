#include "Stronghold.h"

using namespace std;

SocialClass::SocialClass(string n,int pop)
{
	socialName = n;
	population = pop;
	happiness = 70.0;
}

int SocialClass::getPopulation() const {
    return population;
}



void SocialClass::display() const
{
	cout << "Type: " << socialName;
	cout << endl<<"Population: " << population ;
	cout <<endl<< "Happiness: " << happiness << "%" << endl;
}

Peasant::Peasant(int pop) : SocialClass("Peasant", pop){}

void Peasant::updatePeasant()
{
	if (population >= 150)
		happiness -= 4;
	else
		happiness += 2;
	if (happiness > 100) 
		happiness = 100;
	if (happiness < 0) 
		happiness = 0;
}

Merchant::Merchant(int pop) : SocialClass("Merchant",pop){}

void Merchant::updateMerchant()
{
	happiness += 2;

	if (happiness > 100)
		happiness = 100;
	
}

Noble::Noble(int pop): SocialClass("Noble",pop){}

void Noble::updateNoble()
{
	happiness += 1;

	if (happiness > 100)
		happiness = 100;
}

