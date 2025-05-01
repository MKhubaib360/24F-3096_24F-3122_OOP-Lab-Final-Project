#include "Stronghold.h"

using namespace std;

Army::Army(int rec, int food, int gold)
{
	recruit = rec;
	foodStock = food;
	salary_fund = gold;
	trained_soldiers = 15;
	corruption = 0;
	morale = 70; 
}

void Army::recruitt(int newRecruit)
{
	recruit += newRecruit;
	morale -= 2; 
	if (morale < 0)
		morale = 0;
}


void Army::train(int days)
{
	int newtrained = recruit * days / 20;
	if (newtrained > recruit)
		newtrained = recruit;
	trained_soldiers += newtrained;
	recruit -= newtrained;
	morale += days / 2;
	if (morale > 100)
		morale = 100;
}

void Army::autoFeed(Resources& res) {
	int requireFood = trained_soldiers + recruit;
	if (res.consumeFood(requireFood)) {
		morale += 5;
	}
	else {
		morale -= 10;
	}
	morale = max(0, min(100, morale));
}

void Army::manualFeed(Resources& res) {
	cout << "\nArmy feeding:-";
	cout << "\nAvailable food: " << res.getFood();
	cout << "\nTotal soldiers: " << (trained_soldiers + recruit);
	cout << "\nEnter food amount to use: ";

	int foodAmount;
	cin >> foodAmount;

	if (res.consumeFood(foodAmount)) {
		int required = trained_soldiers + recruit;
		if (foodAmount >= required * 2) {
			morale += 10;  
		}
		else if (foodAmount >= required) {
			morale += 5;   
		}
		else {
			morale -= 5;   
		}
		cout << "Fed army with " << foodAmount << " food units!\n";
	}
	else {
		cout << "Not enough food!\n";
		morale -= 15;
	}

	morale = max(0, min(100, morale));
}

void Army::pay(int gold)
{
	salary_fund += gold;
	int requireFund = trained_soldiers * 3;
	if (salary_fund > requireFund)
	{
		salary_fund -= requireFund;
		morale += 10;
		corruption -= 5;
	}
	else
	{
		morale -= 13;
		corruption += 10;
	}

	if (morale > 100)
		morale = 100;
	if (morale < 0)
		morale = 0;
	if (corruption > 100)
		corruption = 100;
	if (corruption < 0)
		corruption = 0;
}

int Army::getMorale() const {
    return morale;
}

int Army::getCorruption() const {
    return corruption;
}

void Army::updateMorale(bool stableLeadership)
{
	if (stableLeadership)
	{
		morale += 5;
		corruption -= 5;
	}
	else
	{
		morale -= 8;
		corruption += 7;
	}

	if (morale > 100)
		morale = 100;
	if (morale < 0)
		morale = 0;
	if (corruption > 100)
		corruption = 100;
	if (corruption < 0)
		corruption = 0;
}

int Army::getTrainedSoldiers() const {
    return trained_soldiers;
}

void Army::displayArmy() const {
	cout << "Recruits: " << recruit << endl;
	cout << "Trained Soldiers: " << trained_soldiers << endl;
	cout << "Total Soldiers: " << (recruit + trained_soldiers) << "\n";
	cout << "Morale: " << morale << "%\n";
	cout << "Corruption: " << corruption << "%\n";
	cout << "Food Stock: " << foodStock << "\n";
	cout << "Salary Fund: " << salary_fund << " gold\n";
}