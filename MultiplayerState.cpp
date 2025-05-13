#include "Stronghold.h"

const int MultiplayerState::MAX_PLAYERS = 4;
const string MultiplayerState::STATE_FILE = "multi_save.txt";
MapGrid MultiplayerState::gameMap;
int MultiplayerState::currentTurn = 0;

MultiplayerState::PlayerData::PlayerData(int startPop) :
    events(60),
    economy(10000.0f),
    army(100, 1000, 0),
    population(startPop),
    resources(1000, 500, 300, 200),
    leadership("Player"),
    peasants(startPop / 2),
    bank(),
    merchants(startPop / 10),
    nobles(startPop / 20),
    mapX(0), mapY(0) {
}

MultiplayerState::PlayerData MultiplayerState::players[4] = {
    PlayerData(1000),
    PlayerData(1000),
    PlayerData(1000),
    PlayerData(1000)
};

void MultiplayerState::initializeGame() {

    for (int i = 0; i < MAX_PLAYERS; i++) {
        players[i].leadership = Leadership("Player" + to_string(i + 1));
    }
    gameMap.initializeMap();
}

void MultiplayerState::saveGame() {
    ofstream file(STATE_FILE);
    if (file.is_open()) {
        for (int i = 0; i < MAX_PLAYERS; i++) {
            GameState::saveGame(
                players[i].economy,
                players[i].army,
                players[i].population,
                players[i].resources,
                players[i].leadership,
                players[i].peasants,
                players[i].merchants,
                players[i].nobles,
                players[i].events
            );
        }

        file << currentTurn << endl;
        gameMap.saveMap("map_state.txt");
        file.close();
    }
}

bool MultiplayerState::loadGame() {
    ifstream file(STATE_FILE);
    if (!file.is_open()) return false;

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!GameState::loadGame(
            players[i].economy,
            players[i].army,
            players[i].population,
            players[i].resources,
            players[i].leadership,
            players[i].peasants,
            players[i].merchants,
            players[i].nobles,
            players[i].events
        )) {
            file.close();
            return false;
        }
    }

    file >> currentTurn;
    gameMap.loadMap("map_state.txt");
    file.close();
    return true;
}

void MultiplayerState::processTurn() {

    processMonth(
        players[currentTurn].population,
        players[currentTurn].army,
        players[currentTurn].economy,
        players[currentTurn].resources,
        players[currentTurn].leadership,
        players[currentTurn].peasants,
        players[currentTurn].merchants,
        players[currentTurn].nobles,
        players[currentTurn].events
    );

    currentTurn = (currentTurn + 1) % MAX_PLAYERS;
}

void MultiplayerState::showPlayerStatus(int playerID) {
    if (playerID < 0 || playerID >= MAX_PLAYERS) return;

    cout <<endl<< "=== Player " << (playerID + 1) << " Status ==="<<endl;
    cout << "Position: (" << players[playerID].mapX
        << ", " << players[playerID].mapY << ")"<<endl;

    players[playerID].economy.displayEconomy();

    players[playerID].army.displayArmy();

    players[playerID].resources.displayResources();

    gameMap.displayMap();
}