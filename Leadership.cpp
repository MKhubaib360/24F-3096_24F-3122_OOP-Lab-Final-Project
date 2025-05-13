#include "Stronghold.h"

using namespace std;

Leadership::Leadership(string name) : ruler_name(name), isStable(true) {}

void Leadership::displayLeadership() const {
    cout <<endl<< "===Leadership Status===" << endl;
    cout << "Ruler: " << ruler_name << endl;
    cout << "Stability: " << (isStable ? "Stable" : "Unstable") << endl;
}

bool Leadership::getStability() const {
    return isStable;
}