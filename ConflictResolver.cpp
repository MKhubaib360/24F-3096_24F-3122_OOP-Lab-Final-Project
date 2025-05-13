#include "Stronghold.h"

using namespace std;

const string ConflictResolver::BATTLE_LOG_FILE = "battles.txt";

ConflictResolver::Outcome ConflictResolver::resolveBattle(
    Army& attackerArmy, Army& defenderArmy,
    const Leadership& attackerLead, const Leadership& defenderLead) {

    int attackerPower = attackerArmy.getTrainedSoldiers() *
        (attackerArmy.getMorale() / 100.0);
    int defenderPower = defenderArmy.getTrainedSoldiers() *
        (defenderArmy.getMorale() / 100.0);

    if (attackerLead.getStability()) attackerPower *= 1.2;
    if (defenderLead.getStability()) defenderPower *= 1.3;

    attackerPower += rand() % (attackerPower / 2) + attackerPower / 10;
    defenderPower += rand() % (defenderPower / 2) + defenderPower / 10;

    Outcome result;
    if (attackerPower > defenderPower * 1.5) {
        result = ATTACKER_WINS;
    }
    else if (defenderPower > attackerPower * 1.5) {
        result = DEFENDER_WINS;
    }
    else {
        result = STALEMATE;
    }

    ofstream file(BATTLE_LOG_FILE, ios::app);
    if (file.is_open()) {
        file << "Attacker:" << attackerPower << "|Defender:" << defenderPower
            << "|Outcome:";
        switch (result) {
        case ATTACKER_WINS: file << "ATTACKER_WINS"; break;
        case DEFENDER_WINS: file << "DEFENDER_WINS"; break;
        case STALEMATE:     file << "STALEMATE";     break;
        }
        file <<  endl;
        file.close();
    }

    return result;
}

void ConflictResolver::applyBattleEffects(Outcome result, Army& winner,
    Army& loser, Economy& economy) {
    switch (result) {
    case ATTACKER_WINS:
        loser.setTrainedSoldiers(loser.getTrainedSoldiers() * 0.5);
        winner.setMorale(min(100, winner.getMorale() + 10));
        economy.adjustTreasury(loser.getTrainedSoldiers() * 3); 
        break;

    case DEFENDER_WINS:
        winner.setTrainedSoldiers(winner.getTrainedSoldiers() * 0.6);
        loser.setMorale(max(0, loser.getMorale() - 15));
        break;

    case STALEMATE:
        winner.setTrainedSoldiers(winner.getTrainedSoldiers() * 0.8);
        loser.setTrainedSoldiers(loser.getTrainedSoldiers() * 0.8);
        economy.adjustTreasury(-(winner.getTrainedSoldiers() + loser.getTrainedSoldiers()));
        break;
    }

    winner.setCorruption(min(100, winner.getCorruption() + 5));
    loser.setCorruption(min(100, loser.getCorruption() + 8));
}

void ConflictResolver::displayBattleHistory(int playerID) {
    ifstream file(BATTLE_LOG_FILE);
    string line;

    cout <<endl<< "=== Battle History ==="<<endl;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}