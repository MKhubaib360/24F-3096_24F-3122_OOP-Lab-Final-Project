#include "Stronghold.h"

using namespace std;

Economy::Economy(float initialGold) : treasury(initialGold), tax_rate(0.15f), inflation(0.02f) {}

void Economy::collectTaxes(const Population& pop, const Peasant& peasants,const Merchant& merchants) { 
    
    if (tax_rate < 0) tax_rate = 0;
    if (tax_rate > 0.5f) tax_rate = 0.5f;

    float peasantTax = peasants.getPopulation() * tax_rate * 0.5f;  
    float merchantTax = merchants.getPopulation() * tax_rate * 2.0f; 
    treasury += peasantTax + merchantTax;
    inflation += 0.005f; 
}

void Economy::payArmy(Army& army) {
    int salaryNeeded = army.getTrainedSoldiers() * 3;
    if (treasury >= salaryNeeded) {
        treasury -= salaryNeeded;
        army.pay(salaryNeeded);
    } else {
        army.pay(0);
    }
}

void Economy::adjustTreasury(int amount) {
    treasury += amount;
}

void Economy::adjustTaxRate(float newRate) {
    tax_rate = (newRate < 0) ? 0 : (newRate > 0.5f) ? 0.5f : newRate;
}

void Economy::applyInflation() {
    treasury *= (1.0f - inflation);
}

void Economy::displayEconomy() const {
    cout << "\n---Economy Status---" << endl;
    cout << "Treasury: " << treasury << " gold" << endl;
    cout << "Tax Rate: " << (tax_rate * 100) << "%" << endl;
    cout << "Inflation: " << (inflation * 100) << "%\n" << endl;
}