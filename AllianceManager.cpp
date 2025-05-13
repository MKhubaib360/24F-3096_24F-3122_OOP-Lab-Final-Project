#include "Stronghold.h"

using namespace std;

const string AllianceManager::ALLIANCE_FILE = "alliances.txt";

void AllianceManager::proposeTreaty(int proposerID, int targetID, TreatyType type) {
    ofstream file(ALLIANCE_FILE, ios::app);
    if (file.is_open()) {
        const char* typeNames[] = { "Non-Aggression", "Defense Pact", "Full Alliance" };
        file << "Player" << proposerID + 1 << "|Player" << targetID + 1 << "|"
            << typeNames[type] << endl;
        cout << "Treaty proposed between Player" << proposerID + 1
            << " and Player" << targetID + 1 << "!" << endl;
    }
}

void AllianceManager::breakTreaty(int breakerID, int targetID) {
    ifstream inFile(ALLIANCE_FILE);
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line.find("Player" + to_string(breakerID + 1) + "|Player" + to_string(targetID + 1)) == string::npos &&
            line.find("Player" + to_string(targetID + 1) + "|Player" + to_string(breakerID + 1)) == string::npos) {
            tempFile << line << endl;
        }
        else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();
    remove(ALLIANCE_FILE.c_str());
    rename("temp.txt", ALLIANCE_FILE.c_str());

    if (found) {
        cout << "Player" << breakerID + 1 << " broke treaty with Player" << targetID + 1 << "!" << endl;
    }
    else {
        cout << "No treaty existed!" << endl;
    }
}

void AllianceManager::displayAlliances(int playerID) {
    ifstream file(ALLIANCE_FILE);
    string line;
    cout << endl << "=== Player" << playerID + 1 << "'s Alliances ===" << endl;

    while (getline(file, line)) {
        if (line.find("Player" + to_string(playerID + 1)) != string::npos) {
            size_t pipe1 = line.find("|");
            size_t pipe2 = line.find("|", pipe1 + 1);
            cout << "- " << line.substr(pipe1 + 1, pipe2 - pipe1 - 1)
                << ": " << line.substr(pipe2 + 1) << endl;
        }
    }
    file.close();
}

bool AllianceManager::hasTreaty(int player1, int player2) {
    ifstream file(ALLIANCE_FILE);
    string line;

    while (getline(file, line)) {
        if ((line.find("Player" + to_string(player1 + 1) + "|Player" + to_string(player2 + 1)) != string::npos) ||
            (line.find("Player" + to_string(player2 + 1) + "|Player" + to_string(player1 + 1)) != string::npos)) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}