#include "Stronghold.h"

using namespace std;

Population::Population(int t)
{
	total = t;
	deaths = 0;
	births = 0;
	ill = 0;
	shelter = 0;
}



void Population::updatePopulation(const Resources& res) {
    int foodSupply = res.getFood(); 
    if (foodSupply < total) {
        ill = (total - foodSupply) / 10;
		deaths = (total - foodSupply) / 20;
		total -= deaths;
	}
	else
	{
		deaths = 0;
		ill = 0;
	}
	if (shelter < total / 2)
		births = shelter / 20;
	else
		births = shelter / 10;

	total += births;
	total = max(0, total);
}

bool Population::isStable()
{
	return ill < total / 10 && deaths < total / 25;
}

void Population::displayPopulation() const
{
	cout <<"=== Total Population ===" << total << endl;
	cout << "Births: " << births << ", Ill: " << ill << ", Deaths: " << deaths << endl;
}