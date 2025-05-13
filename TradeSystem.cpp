#include "Stronghold.h"

using namespace std;

const string TradeSystem::TRADE_FILE = "trades.txt";

void TradeSystem::proposeTrade(int senderID, int receiverID,
    ResourceType offerType, int offerQty,
    ResourceType requestType, int requestQty) {
    ofstream file(TRADE_FILE, ios::app);
    if (file.is_open()) {
        const char* resourceNames[] = { "Food", "Wood", "Stone", "Iron", "Gold" };
        file << "Player" << senderID + 1 << "|Player" << receiverID + 1 << "|"
            << resourceNames[offerType] << "|" << offerQty << "|"
            << resourceNames[requestType] << "|" << requestQty << "|PENDING\n";
        cout << "Trade proposed!"<<endl;
    }
}

void TradeSystem::displayTradeHistory(int playerID) {
    ifstream file(TRADE_FILE);
    string line;
    int tradeCount = 0;

    cout <<endl<< "--- Trade History (Player" << playerID + 1 << ") ---" << endl;
    while (getline(file, line)) {
        if (line.find("Player" + to_string(playerID + 1)) != string::npos) {
            cout << "[" << tradeCount++ << "] " << line << endl;
        }
    }
    file.close();
}

bool TradeSystem::acceptTrade(int tradeID) {
    ifstream inFile(TRADE_FILE);
    ofstream tempFile("temp_trades.txt");
    string line;
    int currentID = 0;
    bool accepted = false;

    while (getline(inFile, line)) {
        if (currentID == tradeID && line.find("PENDING") != string::npos) {
            line.replace(line.find("PENDING"), 7, "ACCEPTED");
            accepted = true;
            cout << "Trade accepted!"<<endl;
        }
        tempFile << line <<endl;
        currentID++;
    }

    inFile.close();
    tempFile.close();
    remove(TRADE_FILE.c_str());
    rename("temp_trades.txt", TRADE_FILE.c_str());
    return accepted;
}