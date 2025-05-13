#include "Stronghold.h"

using namespace std;

const string GameState::SINGLEPLAYER_SAVE = "stronghold_save.txt";
const string GameState::MULTIPLAYER_SAVE = "multi_save.txt";

void GameState::saveGame(const Economy& econ, const Army& army,
    const Population& pop, const Resources& res,
    const Leadership& lead, const Peasant& p,
    const Merchant& m, const Noble& n,
    const KingdomEvent& events) {
    ofstream file(SINGLEPLAYER_SAVE);
    if (file.is_open()) {
        file << econ.getTreasury() << endl;
        file << econ.getTaxRate() << endl;
        file << econ.getInflation() << endl;

        file << army.getRecruits() << endl;
        file << army.getMorale() << endl;
        file << army.getCorruption() << endl;
        file << army.getTrainedSoldiers() << endl;
        file << army.getFoodStock() << endl;
        file << army.getSalaryFund() << endl;

        file << pop.getTotal() << endl;
        file << pop.getIll() << endl;
        file << pop.getBirths() << endl;
        file << pop.getDeaths() << endl;
        file << pop.getShelter() << endl;

        file << res.getFood() << endl;
        file << res.getWood() << endl;
        file << res.getStone() << endl;
        file << res.getIron() << endl;

        file << lead.getStability() << endl;

        file << p.getPopulation() << endl;
        file << p.getHappiness() << endl;
        file << m.getPopulation() << endl;
        file << m.getHappiness() << endl;
        file << n.getPopulation() << endl;
        file << n.getHappiness() << endl;

        file << events.getIntervalMinutes() << endl;
        file << events.getLastTrigger() << endl;
        file << static_cast<int>(events.getLastEvent()) << endl;
        file.close();
    }
}

bool GameState::loadGame(Economy& econ, Army& army, Population& pop,
    Resources& res, Leadership& lead, Peasant& p,
    Merchant& m, Noble& n, KingdomEvent& events) {
    bool dummy;
    return loadGame(dummy, econ, army, pop, res, lead, p, m, n, events);
}

bool GameState::loadGame(bool& isMultiplayer, Economy& econ, Army& army,
    Population& pop, Resources& res, Leadership& lead,
    Peasant& p, Merchant& m, Noble& n, KingdomEvent& events) {
    if (fileExists(SINGLEPLAYER_SAVE)) {
        isMultiplayer = false;
        ifstream file(SINGLEPLAYER_SAVE);
        if (file.is_open()) {
            float treasury, taxRate, inflation;
            file >> treasury >> taxRate >> inflation;
            econ.setTreasury(treasury);
            econ.setTaxRate(taxRate);
            econ.setInflation(inflation);

            int recruits, morale, corruption, trained, foodStock, salaryFund;
            file >> recruits >> morale >> corruption >> trained >> foodStock >> salaryFund;
            army.setRecruits(recruits);
            army.setMorale(morale);
            army.setCorruption(corruption);
            army.setTrainedSoldiers(trained);
            army.setFoodStock(foodStock);
            army.setSalaryFund(salaryFund);

            int total, ill, births, deaths, shelter;
            file >> total >> ill >> births >> deaths >> shelter;
            pop.setTotal(total);
            pop.setIll(ill);
            pop.setBirths(births);
            pop.setDeaths(deaths);
            pop.setShelter(shelter);

            int food, wood, stone, iron;
            file >> food >> wood >> stone >> iron;
            res.setFood(food);
            res.setWood(wood);
            res.setStone(stone);
            res.setIron(iron);

            bool stability;
            file >> stability;
            lead.setStability(stability);

            int pPop, mPop, nPop;
            float pHappy, mHappy, nHappy;
            file >> pPop >> pHappy >> mPop >> mHappy >> nPop >> nHappy;
            p.setPopulation(pPop);
            p.setHappiness(pHappy);
            m.setPopulation(mPop);
            m.setHappiness(mHappy);
            n.setPopulation(nPop);
            n.setHappiness(nHappy);

            int interval, eventType;
            time_t lastTrig;
            file >> interval >> lastTrig >> eventType;
            events.setIntervalMinutes(interval);
            events.setLastTrigger(lastTrig);
            events.setLastEvent(static_cast<EventType>(eventType));

            file.close();
            return true;
        }
        return false;
    }
    else if (fileExists(MULTIPLAYER_SAVE)) {
        isMultiplayer = true;
        return MultiplayerState::loadGame();
    }
    return false;
}

void GameState::saveGameMultiplayer() {
    MultiplayerState::saveGame();
}