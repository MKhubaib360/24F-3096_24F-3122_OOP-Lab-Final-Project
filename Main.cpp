#include "Stronghold.h"

using namespace std;

void initializeGame(Peasant& peasants, Merchant& merchants, Noble& nobles, 
    Population& population, Army& army, Economy& economy,
    Resources& resources, Leadership& leadership, Bank& bank, KingdomEvent &event) {

    const int INITIAL_PEASANTS = 800;
    const int INITIAL_MERCHANTS = 150;
    const int INITIAL_NOBLES = 50;
    const int INITIAL_POPULATION = INITIAL_PEASANTS + INITIAL_MERCHANTS + INITIAL_NOBLES;

    const int INITIAL_ARMY_RECRUITS = 100;
    const int INITIAL_FOOD = 1000;
    const int INITIAL_WOOD = 500;
    const int INITIAL_STONE = 300;
    const int INITIAL_IRON = 200;
    const float INITIAL_TREASURY = 10000.0f;

    string rulerName;
    cout << "Enter Ruler's name: ";
    getline(cin, rulerName);
    system("cls");

    peasants = Peasant(INITIAL_PEASANTS);
    merchants = Merchant(INITIAL_MERCHANTS);
    nobles = Noble(INITIAL_NOBLES);
    population = Population(INITIAL_POPULATION);
    army = Army(INITIAL_ARMY_RECRUITS, INITIAL_FOOD, INITIAL_TREASURY);
    economy = Economy(INITIAL_TREASURY);
    resources = Resources(INITIAL_FOOD, INITIAL_WOOD, INITIAL_STONE, INITIAL_IRON);
    leadership = Leadership(rulerName);
    bank = Bank();

    cout << "Game initialized with the following resources:-\n\n";
    cout << "Peasants: " << INITIAL_PEASANTS << "\nMerchants: " << INITIAL_MERCHANTS
        << "\nNobles: " << INITIAL_NOBLES << "\nTotal Population: " << INITIAL_POPULATION << "\n";
    cout << "Army Recruits: " << INITIAL_ARMY_RECRUITS << "\nTreasury: " << INITIAL_TREASURY << "\n";
    cout << "Resources:- \n Food: " << INITIAL_FOOD << ", Wood: " << INITIAL_WOOD
        << ", Stone: " << INITIAL_STONE << ", Iron: " << INITIAL_IRON << "\n\n";
    cout << "Press Enter to continue...";
    cin.ignore();
    system("cls");
}

void populationManagementMenu(Population& pop, Resources& res) {
    int choice;

    do {
        cout << "\n---Populaton management---" << endl;
        cout << "1. Build Housing (50 wood, 30 stone)" << endl;
        cout << "2. Gather Resources" << endl;
        cout << "3. View Population Status" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            if (res.consumeWood(50) && res.consumeStone(30)) {
                pop.setShelter(pop.getShelter() + 100);
                cout << "Built shelter for 100 more people!\n";
            }
            else {
                cout << "Need 50 wood and 30 stone!\n";
            }
            break;
        }
        case 2: {
            int gatheredWood = pop.getTotal() / 10;
            int gatheredStone = pop.getTotal() / 20;
            res.setWood(min(res.getWood() + gatheredWood, 500));
            res.setStone(min(res.getStone() + gatheredStone, 300));
            cout << "Gathered " << gatheredWood << " wood and "
                << gatheredStone << " stone.\n";
            break;
        }
        case 3:
            pop.displayPopulation();
            cout << "Shelter Capacity: " << pop.getShelter() << endl;
            cout << "Homeless: " << max(0, pop.getTotal() - pop.getShelter()) << endl;
            break;
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
        }
    } while (choice != 0);
}


void armyManagementMenu(Army& army, Resources& res) {
    int choice;
    do {
        cout << "\n---Army Management Menu---" << endl;
        cout << "1. Recruit Soldiers\n";
        cout << "2. Train Soldiers\n";
        cout << "3. Feed Army\n";
        cout << "4. Pay Soldiers\n";
        cout << "5. View Army Status\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            int recruits;
            cout << "Enter number of soldiers to recruit: ";
            cin >> recruits;
            army.recruitt(recruits);
            break;
        }
        case 2: {
            int days;
            cout << "Enter training days: ";
            cin >> days;
            army.train(days);
            break;
        }
        case 3:
            army.manualFeed(res);
            break;
        case 4: {
            int gold;
            cout << "Enter payment amount: ";
            cin >> gold;
            army.pay(gold);
            break;
        }
        case 5:
            army.displayArmy();
            break;
        }
    } while (choice != 0);
}

void bankOperationsMenu(Bank& bank, Economy& econ) {
    int choice;
    do {
        cout << "\n---Bank---" << endl;
        cout << "1. Take Loan\n";
        cout << "2. Repay Loan\n";
        cout << "3. Conduct Audit\n";
        cout << "4. Display Bank Status\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            float amount;
            cout << "Enter loan amount: ";
            cin >> amount;
            bank.takeLoan(econ, amount);
            break;
        }
        case 2: {
            float amount;
            cout << "Enter repayment amount: ";
            cin >> amount;
            bank.repayLoan(econ, amount);
            break;
        }
        case 3:
            bank.conductAudit(econ);
            break;
        case 4:
            bank.displayBank();
            break;
        }
    } while (choice != 0);
}

void displayMainMenu() {
    cout << "\n---StrngHold Kingdom Management---" << endl;
    cout << "1. View Kingdom Status\n";
    cout << "2. Manage Army\n";
    cout << "3. Manage Population & Resources\n"; 
    cout << "4. Adjust Taxes\n";
    cout << "5. Bank Operations\n";
    cout << "6. Process Next Month\n";
    cout << "7. Save/Load Game\n";
    cout << "8. Exit\n";
    cout << "Choice: ";
}


void processMonth(Population& pop, Army& army, Economy& econ,
    Resources& res, Leadership& lead, Peasant& p,
    Merchant& m, Noble& n, KingdomEvent& events) {

    system("cls");
    cout << "---PROCESSING MONTH---" << endl;

    int possibleHousing = min(res.getWood() / 50, res.getStone() / 30);
    int newShelter = pop.getShelter() + (possibleHousing * 100); 
    pop.setShelter(newShelter);

    int peasants = p.getPopulation();
    int merchants = m.getPopulation();
    int nobles = n.getPopulation();

    res.gatherFood(peasants * 2);       
    res.gatherWood(peasants);           
    res.gatherStone(peasants / 3);     
    res.gatherIron(peasants / 5);     
    int foodConsumption = pop.getTotal();
    if (!res.consumeFood(foodConsumption)) {
        cout << "Food shortage! Population suffering!\n";
        army.setMorale(army.getMorale() - 5);
    }
    int ironNeeded = army.getTrainedSoldiers() / 10;
    if (!res.consumeIron(ironNeeded)) {
        cout << "Iron shortage! Army equipment deteriorating!\n";
        army.setMorale(army.getMorale() - 3);
    }

    pop.updatePopulation(res);  
    p.updatePeasant();
    m.updateMerchant();
    n.updateNoble();
    econ.collectTaxes(pop, p, m);
    econ.payArmy(army);
    econ.applyInflation();
    army.updateMorale(lead.getStability());
    res.spoilFood();

    pop.setShelter(possibleHousing*100);
    res.consumeWood(possibleHousing * 50);
    res.consumeStone(possibleHousing * 30);

    cout << "\n---MONTHLY REPORT---" << endl;
    cout << "Resource Changes:\n";
    cout << "  Food Gathered: " << peasants * 2 << endl;
    cout << "  Wood Gathered: " << peasants << endl;
    cout << "  Stone Gathered: " << peasants / 3 << endl;
    cout << "  Iron Gathered: " << peasants / 5 << endl;

    pop.displayPopulation();
    army.displayArmy();
    econ.displayEconomy();
    res.displayResources();
    lead.displayLeadership();

    cout << "\nShelter Capacity: " << pop.getShelter();
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    system("cls");
}

int main() {
    Peasant peasants(0);
    Merchant merchants(0);
    Noble nobles(0);
    Population population(0);
    Army army(0, 0, 0);
    Economy economy(0);
    Resources resources(0, 0, 0, 0);
    Leadership leadership("");
    Bank bank;
	KingdomEvent event(5);
    GameState gameState;

    system("cls");
    cout << endl << endl << endl << endl << "****************************************************************************************************************************************************" << endl;
    cout << "**********************************************************___________________________***************************************************************" << endl;
    cout << "*********************************************************|                           |**************************************************************" << endl;
    cout << "*********************************************************|   Welcome to StrongHold   |**************************************************************" << endl;
    cout << "*********************************************************|___________________________|**************************************************************" << endl;
    cout << "**********************************************************                           ***************************************************************" << endl;
    cout << "****************************************************************************************************************************************************" << endl;
    initializeGame(peasants, merchants, nobles, population, army, economy,
        resources, leadership, bank, event);

    int choice;
    bool gameRunning = true;

    while (gameRunning) {
        if (event.shouldTrigger()) {
            EventType currentEvent = event.getRandomEvent();
            event.executeEvent(currentEvent, population, army, economy, resources,
                peasants, merchants, nobles);
        }
        cin.ignore();
		cin.clear(); 
        displayMainMenu();
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:{ 
            cout << "\n---Kingdom Status---\n";
            population.displayPopulation();
            army.displayArmy();
            economy.displayEconomy();
            resources.displayResources();
            leadership.displayLeadership();
            int garbage;
            cout << "\nEnter any integar to exit: ";
            cin >> garbage;
            cin.ignore();
            system("cls");
            break;
		}
        case 2:
            armyManagementMenu(army, resources);
            system("cls");
            break;
        case 3:
            populationManagementMenu(population, resources);
            break;
        case 4: {
            float newRate;
            cout << "Enter new tax rate (0-0.5): ";
            cin >> newRate;
            economy.adjustTaxRate(newRate);
            cout << "Tax rate updated!\n";
            Sleep(1000);
            system("cls");
            break;
        }

        case 5: 
            bankOperationsMenu(bank, economy);
            break;

        case 6: 
            processMonth(population, army, economy, resources,
                leadership, peasants, merchants, nobles, event);
            break;

        case 7:  {
            int saveChoice;
            std::cout << "1. Save 2. Load: ";
            std::cin >> saveChoice;
            if (saveChoice == 1) {
                gameState.saveGame(economy, army, population, resources,
                    leadership, peasants, merchants, nobles, event);
                std::cout << "Game saved!\n";
            }
            else {
                if (gameState.loadGame(economy, army, population, resources,
                    leadership, peasants, merchants, nobles, event)) {
                    std::cout << "Game loaded!\n";
                }
                else {
                    std::cout << "No save file found!\n";
                }
            }
            break;
		}
        case 8:
            gameRunning = false;
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
            Sleep(1000);
            system("cls");
        }
    }

    cout << "      Thanks for playing Stronghold\n";
    return 0;
}