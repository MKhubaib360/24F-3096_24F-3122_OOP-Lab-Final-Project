#include "Stronghold.h"
#include <string>

using namespace std;

const string NetworkHandler::CHAT_FILE = "chat_history.txt";
string NetworkHandler::messages[4] = {};

void NetworkHandler::sendMessage(int senderID, int receiverID, const string& msg) {
    if (receiverID >= 0 && receiverID < 4) {
        string formattedMsg = "[Player" + to_string(senderID + 1) + "->Player" +
            to_string(receiverID + 1) + "]: " + msg;

        messages[receiverID] += formattedMsg + "\n";

        ofstream file(CHAT_FILE, ios::app);
        if (file.is_open()) {
            file << formattedMsg << endl;
            file.close();
        }
    }
}

string NetworkHandler::getMessages(int playerID) {
    return (playerID >= 0 && playerID < 4) ? messages[playerID] : "";
}

void NetworkHandler::showChatHistory(int playerID) {
    ifstream file(CHAT_FILE);
    string line;

    cout <<endl<< "=== Chat History for Player" << playerID + 1 << "===" << endl;

    while (getline(file, line)) {
        size_t arrowPos = line.find("->Player" + to_string(playerID + 1) + "]:");
        if (arrowPos != string::npos) {
            cout << line << endl;
        }
    }
    file.close();
}

void NetworkHandler::clearSession() {
    for (auto& msg : messages) msg.clear();
}