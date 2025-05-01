#include "Stronghold.h"

void GameState::saveGame(const Economy& econ, const Army& army, const Population& pop,
    const Resources& res, const Leadership& lead, const Peasant& p,
    const Merchant& m, const Noble& n, const KingdomEvent& events) {
    std::ofstream file(SAVE_FILE);

    if (file.is_open()) {

        file << econ.getTreasury() << std::endl;
        file << econ.getTaxRate() << std::endl;
        file << econ.getInflation() << std::endl;

        file << army.getRecruits() << std::endl;
        file << army.getMorale() << std::endl;
        file << army.getCorruption() << std::endl;
        file << army.getTrainedSoldiers() << std::endl;
        file << army.getFoodStock() << std::endl;
        file << army.getSalaryFund() << std::endl;

        file << pop.getTotal() << std::endl;
        file << pop.getIll() << std::endl;
        file << pop.getBirths() << std::endl;
        file << pop.getDeaths() << std::endl;
        file << pop.getShelter() << std::endl; 

        file << res.getFood() << std::endl;
        file << res.getWood() << std::endl;
        file << res.getStone() << std::endl;
        file << res.getIron() << std::endl;

        file << lead.getStability() << std::endl;

        file << p.getPopulation() << std::endl;
        file << p.getHappiness() << std::endl;
        file << m.getPopulation() << std::endl;
        file << m.getHappiness() << std::endl;
        file << n.getPopulation() << std::endl;
        file << n.getHappiness() << std::endl;

        file << events.getIntervalMinutes() << std::endl;
        file << events.getLastTrigger() << std::endl;
        file << static_cast<int>(events.getLastEvent()) << std::endl;

        file.close();
    }
}

bool GameState::loadGame(Economy& econ, Army& army, Population& pop,
    Resources& res, Leadership& lead, Peasant& p,
    Merchant& m, Noble& n, KingdomEvent& events) {
    std::ifstream file(SAVE_FILE);

    if (!file.is_open()) return false;

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