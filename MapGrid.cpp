#include "Stronghold.h"

using namespace std;

MapGrid::MapGrid() {
    initializeMap();
}

void MapGrid::initializeMap() {
    const char terrain[] = { 'F', 'M', 'P', 'R' };

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = terrain[rand() % 4];
            controllers[i][j] = -1; 
        }
    }

    grid[0][0] = 'P'; controllers[0][0] = 0;  
    grid[9][9] = 'P'; controllers[9][9] = 1;  
    grid[0][9] = 'P'; controllers[0][9] = 2;  
    grid[9][0] = 'P'; controllers[9][0] = 3;  
}

void MapGrid::displayMap() const {
    cout << endl << "=== KINGDOM MAP ===" << endl;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (controllers[i][j] != -1) {
                cout << "P" << controllers[i][j] + 1 << " ";
            }
            else {
                cout << grid[i][j] << "  ";
            }
        }
        cout << endl;
    }
}

bool MapGrid::moveArmy(int playerID, int oldX, int oldY, int newX, int newY) {
    if (abs(oldX - newX) > 1 || abs(oldY - newY) > 1) {
        cout << "Can only move adjacent tiles!"<<endl;
        return false;
    }

    if (controllers[newX][newY] == playerID) {
        cout << "Already controlled!"<<endl;
        return true;
    }

    return true;
}

void MapGrid::updateControl(int playerID, int x, int y, const Army& army) {
    if (army.getTrainedSoldiers() > 50) { 
        controllers[x][y] = playerID;
        grid[x][y] = 'K'; 
    }
}

void MapGrid::applyTerrainBonus(int x, int y, Resources& res) {
    switch (grid[x][y]) {
    case 'F': res.gatherWood(10); break;  
    case 'M': res.gatherStone(5); break;  
    case 'R': res.gatherFood(15); break; 
    case 'P': res.gatherFood(5); break;   
    case 'K': break;
    }
}

void MapGrid::processTerrainBonuses(Resources& res, int playerID) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (controllers[i][j] == playerID) {
                applyTerrainBonus(i, j, res);
            }
        }
    }
}

void MapGrid::saveMap(const string& filename) const {
    ofstream file(filename);
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            file << grid[i][j] << " " << controllers[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
}

void MapGrid::loadMap(const string& filename) {
    ifstream file(filename);
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            file >> grid[i][j] >> controllers[i][j];
        }
    }
    file.close();
}