#include "Stronghold.h"

KingdomEvent::KingdomEvent(int minutes)
    : intervalMinutes(minutes), lastEvent(EventType::NONE) {
    lastTrigger = time(nullptr);
}

bool KingdomEvent::shouldTrigger() {
    time_t now = time(nullptr);
    return difftime(now, lastTrigger) >= (intervalMinutes * 60);
}

EventType KingdomEvent::getRandomEvent() const {
    int random = rand() % 100;
    if (random < 15)  return EventType::FAMINE;
    if (random < 30)  return EventType::PLAGUE;
    if (random < 45)  return EventType::FLOOD;
    if (random < 60)  return EventType::TORNADO;
    if (random < 75)  return EventType::ECONOMIC_CRISIS;
    if (random < 90)  return EventType::CORRUPTION;
    return EventType::REVOLT;
}

void KingdomEvent::executeEvent(EventType type, Population& pop,
    Army& army, Economy& econ, Resources& res,
    Peasant& peasants, Merchant& merchants, Noble& nobles) {
    system("cls");
    cout<<endl << "=== EMERGENCY EVENT ALERT ===\n"<<endl;
    applyEffects(type, pop, army, econ, res, peasants, merchants, nobles);
    lastTrigger = time(nullptr);

    cout << endl<<"Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void KingdomEvent::applyEffects(EventType type, Population& pop,
    Army& army, Economy& econ, Resources& res,
    Peasant& peasants, Merchant& merchants, Noble& nobles) {
    switch (type) {
    case EventType::FAMINE:
        cout << "Famine Alert!"<<endl;
        cout << "Storages halved!"<<endl;
        res.gatherFood(-res.getFood() / 2);
        peasants.setHappiness(peasants.getHappiness() - 20);
        break; 

    case EventType::PLAGUE: {
        cout << "Plague OUTBREAK!"<<endl;
        int casualties = pop.getTotal() / 5;
        pop.setTotal(max(0, pop.getTotal() - casualties));
        pop.setDeaths(casualties);
        army.setMorale(army.getMorale() - 25);
        break;
    }

    case EventType::FLOOD:
        cout << "A Massive Flood Arrived!"<<endl;
        res.gatherWood(-res.getWood() / 2);
        res.gatherFood(-res.getFood() / 3);
        merchants.setHappiness(merchants.getHappiness() - 15);
        break;

    case EventType::TORNADO:
        cout << "Kingdom is hit by a Huge Tornado!"<<endl;
        res.gatherWood(-res.getWood() / 2);
        res.gatherStone(-res.getStone() / 3);
        army.recruitt(-army.getRecruits() / 4);
        nobles.setHappiness(nobles.getHappiness() - 10);
        break;

    case EventType::ECONOMIC_CRISIS:
        cout << "Economic Collapse!"<<endl;
        econ.adjustTaxRate(min(econ.getTaxRate() + 0.15f, 0.5f));
        econ.adjustTreasury(-static_cast<int>(econ.getTreasury() / 3));
        merchants.setHappiness(merchants.getHappiness() - 25);
        break;

    case EventType::CORRUPTION:
        cout << "Corrupton Scandal!"<<endl;
        army.setCorruption(min(army.getCorruption() + 25, 100));
        econ.adjustTreasury(-1000);
        nobles.setHappiness(nobles.getHappiness() - 15);
        break;

    case EventType::REVOLT: {
        cout << "PEASANTS REVOLT!"<<endl;
        int rebels = peasants.getPopulation() / 3;
        peasants.setPopulation(max(0, peasants.getPopulation() - rebels));
        army.recruitt(-army.getRecruits() / 2);
        res.gatherFood(-res.getFood() / 2);
        res.gatherIron(-res.getIron() / 3);
        break;
    }

    default: break;
    }

    army.setMorale(max(0, min(100, army.getMorale())));
    army.setCorruption(max(0, min(100, army.getCorruption())));
    peasants.setHappiness(max(0, min(100, peasants.getHappiness())));
    merchants.setHappiness(max(0, min(100, merchants.getHappiness())));
    nobles.setHappiness(max(0, min(100, nobles.getHappiness())));
    res.setFood(max(0, res.getFood()));
    res.setWood(max(0, res.getWood()));
    res.setStone(max(0, res.getStone()));
    res.setIron(max(0, res.getIron()));
}