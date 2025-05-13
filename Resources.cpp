#include "Stronghold.h"

using namespace std;

Resources::Resources(int f, int w, int s, int i) 
    : food(f), wood(w), stone(s), iron(i) {}

bool Resources::consumeFood(int amount) {
    if (food >= amount) {
        food -= amount;
        return true;
    }
    food = 0;
    return false; 
}

void Resources::gatherFood(int amount) {
    food += amount;
    if (food > 1000) food = 1000;   
}

bool Resources::consumeWood(int amount) {
    if (wood >= amount) {
        wood -= amount;
        return true;
    }
    wood = 0;
    return false;
}

void Resources::gatherStone(int amount) {
    stone += amount;
    if(stone > 300) stone = 300;
}

void Resources::gatherIron(int amount) {
    iron += amount;
    if(iron > 200) iron = 200; 
}

bool Resources::consumeStone(int amount) {
    if(stone >= amount) {
        stone -= amount;
        return true;
    }
    return false;
}

bool Resources::consumeIron(int amount) {
    if(iron >= amount) {
        iron -= amount;
        return true;
    }
    return false;
}

void Resources::gatherWood(int amount) {
    wood += amount;
    if (wood > 500) wood = 500; 
}

void Resources::spoilFood() {
    food -= static_cast<int>(food * 0.05); 
    if (food < 0) food = 0;
}


void Resources::displayResources() const {
    cout << endl<<"     Resources" << endl;
    cout << "Food: " << food << " units"<<endl;
    cout << "Wood: " << wood << " logs"<<endl;
    cout << "Stone: " << stone << " blocks"<<endl;
    cout << "Iron: " << iron << " ingots"<<endl;
}

