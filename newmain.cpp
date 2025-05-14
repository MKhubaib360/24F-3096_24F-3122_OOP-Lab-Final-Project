#include "Stronghold.h"
using namespace std;

int dummy;

void color(int textcolor, int backgroundcolor) {
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, (backgroundcolor << 4) | textcolor);
}

void displayMainMenu() {
    cout << endl<<"=== StrongHold Kingdom Management ===" << endl;
    cout << "[1] View Kingdom Status" << endl;
    cout << "[2] Manage Army" << endl;
    cout << "[3] Manage Population & Resources" << endl;
    cout << "[4] Adjust Taxes" << endl;
    cout << "[5] Manage Bank" << endl;
    cout << "[6] Process Next Month" << endl;
    cout << "[7] Save/Load Game" << endl;
    cout << "[8] Exit" << endl;
    cout << "Choice: ";
}

void initializeGame(Peasant& peasants, Merchant& merchants, Noble& nobles,
    Population& population, Army& army, Economy& economy,
    Resources& resources, Leadership& leadership, Bank& bank, KingdomEvent& event) {

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

    cout << "Game initialized with the following resources:-" << endl << endl;
    cout << "Peasants: " << INITIAL_PEASANTS << endl << "Merchants: " << INITIAL_MERCHANTS
        << endl << "Nobles: " << INITIAL_NOBLES << endl << "Total Population: " << INITIAL_POPULATION << endl ;
    cout << "Army Recruits: " << INITIAL_ARMY_RECRUITS << "\nTreasury: " << INITIAL_TREASURY << "\n";
    cout << "Resources:-" <<endl<<" Food: " << INITIAL_FOOD << ", Wood: " << INITIAL_WOOD
        << ", Stone: " << INITIAL_STONE << ", Iron: " << INITIAL_IRON << endl << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
	cin.get();
    system("cls");
}

void populationManagementMenu(Population& pop, Resources& res) {
    int choice;

    do {
        cout << "\n=== Populaton management ===" << endl;
        cout << "[1] Build Housing (50 wood, 30 stone)" << endl;
        cout << "[2] Gather Resources" << endl;
        cout << "[3] View Population Status" << endl;
        cout << "[0] Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            if (res.consumeWood(50) && res.consumeStone(30)) {
                pop.setShelter(pop.getShelter() + 100);
                cout << "Built shelter for 100 people!\n";
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
        cout << "\n=== Army Management Menu ===" << endl;
        cout << "[1] Recruit Soldiers" << endl;
        cout << "[2] Train Soldiers" << endl;
        cout << "[3] Feed Army" << endl;
        cout << "[4] Pay Soldiers" << endl;
        cout << "[5] View Army Status" << endl;
        cout << "[0] Back" << endl;
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
            cout << "Enter amount: ";
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
        cout << endl<<"=== Bank ===" << endl;
        cout << "[1] Take Loan" << endl;
        cout << "[2] Repay Loan" << endl;
        cout << "[3] Conduct Audit" << endl;
        cout << "[4] Display Bank Status" << endl;
        cout << "[0] Back" << endl;
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

void multiplayerGame() {
    MultiplayerState::initializeGame();
    bool multiplayerRunning = true;

    while (multiplayerRunning) {

        int currentPlayer = MultiplayerState::currentTurn;
        auto& player = MultiplayerState::players[currentPlayer];
        MultiplayerState::gameMap.processTerrainBonuses(player.resources, currentPlayer);
        bool turnActive = true;
        while (turnActive) {
            system("cls");
            cout << "\n=== PLAYER " << (currentPlayer + 1) << "'s TURN ===" << endl;

            MultiplayerState::gameMap.displayMap();
            AllianceManager::displayAlliances(currentPlayer);

            cout << "\n=== KINGDOM MANAGEMENT ===" << endl;
            cout << "[1] Kingdom Operations\n";
            cout << "[2] Diplomacy & Alliances\n";
            cout << "[3] Trade with Others\n";
            cout << "[4] Military Actions\n";
            cout << "[5] View Chat\n";
            cout << "[6] End Turn\n";
            cout << "[7] Save & Exit\n";
            cout << "Choice: ";

            int mainChoice;
            cin >> mainChoice;
            switch (mainChoice) {
            case 1: { 
                bool inKingdomMenu = true;
                while (inKingdomMenu) {
                    system("cls");
                    cout << "\n=== KINGDOM OPERATIONS ===" << endl;
                    cout << "[1] View Kingdom Status" << endl;
                    cout << "[2] Manage Army" << endl;
                    cout << "[3] Manage Population & Resources" << endl;
                    cout << "[4] Adjust Taxes" << endl;
                    cout << "[5] Manage Bank " << endl;
                    cout << "[6] Process Next Month" << endl;
                    cout << "[7] Return to Main Menu" << endl;
                    cout << "Choice: ";

                    int kingdomChoice;
                    cin >> kingdomChoice;
                    switch (kingdomChoice) {
                    case 1: {
                        cout << endl<<"=== Kingdom Status ===\n";
                        player.population.displayPopulation();
                        player.army.displayArmy();
                        player.economy.displayEconomy();
                        player.resources.displayResources();
                        player.leadership.displayLeadership();
                        cout << endl << "Press Enter to continue...";
                        cin.ignore();
                        cin.get();
						system("cls");  
                        break;
                    }
                    case 2:
                        armyManagementMenu(player.army, player.resources);
                        system("cls");
                        break;
                    case 3:
                        populationManagementMenu(player.population, player.resources);
                        system("cls");
                        break;
                    case 4: {
                        float newRate;
                        cout << "Enter new tax rate (0-0.5): ";
                        cin >> newRate;
                        player.economy.adjustTaxRate(newRate);
                        cout << "Tax rate updated!" << endl;
                        Sleep(1000);
                        system("cls");
                        break;
                    }
                    case 5:
                        bankOperationsMenu(player.bank, player.economy);
                        system("cls");
                        break;
                    case 6:
                        processMonth(player.population, player.army, player.economy,
                            player.resources, player.leadership,
                            player.peasants, player.merchants,
                            player.nobles, player.events);
						cout << endl << "Press Enter to continue...";
						cin.ignore();
						cin.get();
                        system("cls");
                        break;
                    case 7:
                        inKingdomMenu = false;
                        break;
                    default:
                        cout << "Invalid choice!\n";
                        Sleep(1000);
                    }
                }
                break;
            }
            case 2: { 
                system("cls");
                cout << endl << "=== DIPLOMACY ===" << endl;
                cout << "[1] Propose Treaty" << endl;
                cout << "[2] Break Treaty" << endl;
                cout << "[3] View Alliances" << endl;
                cout << "[4] Back" << endl;
                cout << "Choice: ";

                int allianceChoice;
                cin >> allianceChoice;
                switch (allianceChoice) {
                case 1: {
                    int targetPlayer;
                    cout << "Target Player (1-4): ";
                    cin >> targetPlayer;
                    cout << "Treaty Type (1-3):" << endl;
                    cout << " [1] Non-Aggression" << endl;
                    cout << " [2] Defense Pact" << endl;
                    cout << " [3] Full Alliance"<<endl;
                    int type;
                    cin >> type;
                    AllianceManager::proposeTreaty(currentPlayer, targetPlayer - 1,
                        static_cast<AllianceManager::TreatyType>(type - 1));
                    break;
                }
                case 2: {
                    int targetPlayer;
                    cout << "Target Player to Break With: ";
                    cin >> targetPlayer;
                    AllianceManager::breakTreaty(currentPlayer, targetPlayer - 1);
                    break;
                }
                case 3:
                    AllianceManager::displayAlliances(currentPlayer);
					cout << endl << "Enter any integer value to exit..." << endl;
					cin >> dummy;
					cin.ignore();
                    break;
                }
                break;
            }
            case 3: { 
                system("cls");
                cout << endl << "=== TRADE ===" << endl;
                cout << "[1] Propose Trade" << endl;
                cout << "[2] View Trade Offers" << endl;
                cout << "[3] Accept Trade" << endl;
                cout << "[4] Back" << endl;
                cout << "Choice: ";

                int tradeChoice;
                cin >> tradeChoice;
                switch (tradeChoice) {
                case 1: {
                    int targetPlayer;
                    cout << "Target Player: ";
                    cin >> targetPlayer;

                    cout << "Offer (1-5):"<<endl<<"1.Food 2.Wood 3.Stone 4.Iron 5.Gold" << endl;
                    int offerType, offerQty;
                    cout << "Type: "; cin >> offerType;
                    cout << "Quantity: "; cin >> offerQty;

                    cout << "Request (1-5):"<<endl<<"1.Food 2.Wood 3.Stone 4.Iron 5.Gold" << endl;
                    int requestType, requestQty;
                    cout << "Type: "; cin >> requestType;
                    cout << "Quantity: "; cin >> requestQty;

                    TradeSystem::proposeTrade(currentPlayer, targetPlayer - 1,
                        static_cast<TradeSystem::ResourceType>(offerType - 1), offerQty,
                        static_cast<TradeSystem::ResourceType>(requestType - 1), requestQty);
                    break;
                }
                case 2:
                    TradeSystem::displayTradeHistory(currentPlayer);
                    cout << endl << "Enter any integer value to exit..." << endl;
                    cin >> dummy;
                    cin.ignore();
                    break;
                    break;
                case 3: {
                    int tradeID;
                    cout << "Enter Trade ID to Accept: ";
                    cin >> tradeID;
                    TradeSystem::acceptTrade(tradeID);
                    break;
                }
                }
                break;
            }
            case 4: { 
                system("cls");
                cout << endl << "=== MILITARY COMMANDS ===" << endl;
                cout << "[1] Move Army" << endl;
                cout << "[2] Attack Player" << endl;
                cout << "[3] View Battle History" << endl;
                cout << "[4] Back\n";
                cout << "Choice: ";

                int militaryChoice;
                cin >> militaryChoice;
                switch (militaryChoice) {
                case 1: {
                    int oldX, oldY, newX, newY;
                    cout << "Current Position (X Y): ";
                    cin >> oldX >> oldY;
                    cout << "New Position (X Y): ";
                    cin >> newX >> newY;
                    if (MultiplayerState::gameMap.moveArmy(currentPlayer, oldX, oldY, newX, newY)) {
                        MultiplayerState::gameMap.updateControl(currentPlayer, newX, newY, player.army);
                    }
                    break;
                }
                case 2: {
                    int targetPlayer;
                    cout << "Target Player: ";
                    cin >> targetPlayer;
                    auto& defender = MultiplayerState::players[targetPlayer - 1];

                    auto outcome = ConflictResolver::resolveBattle(
                        player.army, defender.army,
                        player.leadership, defender.leadership
                    );
                    ConflictResolver::applyBattleEffects(outcome, player.army, defender.army, player.economy);
                    break;
                }
                case 3:
                    ConflictResolver::displayBattleHistory(currentPlayer);
                    cout << endl << "Enter any integer value to exit..." << endl;
                    cin >> dummy;
                    cin.ignore();
                    break;
                    break;
                }
                break;
            }
            case 5: { 
                system("cls");
                cout << endl << "=== COMMUNICATIONS ===" << endl;
                cout << "[1] Send Message" << endl;
                cout << "[2] Read Messages" << endl;
                cout << "[3] Back" << endl;
                cout << "Choice: ";

                int chatChoice;
                cin >> chatChoice;
                switch (chatChoice) {
                case 1: {
                    int targetPlayer;
                    string message;
                    cout << "Recipient (1-4): ";
                    cin >> targetPlayer;
                    cout << "Message: ";
                    cin.ignore();
                    getline(cin, message);
                    NetworkHandler::sendMessage(currentPlayer, targetPlayer - 1, message);
                    break;
                }
                case 2:
                    NetworkHandler::showChatHistory(currentPlayer);
                    cout << endl << "Enter any integar value to exit..." << endl;
                    cin >> dummy;
                    cin.ignore();
                    break;
                }
                break;
            }
            case 6: 
                turnActive = false;
                MultiplayerState::currentTurn =
                    (MultiplayerState::currentTurn + 1) % MultiplayerState::MAX_PLAYERS;
                break;
            case 7: 
                GameState::saveGameMultiplayer();
                multiplayerRunning = false;
                break;
            }
        }
        MultiplayerState::gameMap.processTerrainBonuses(player.resources, currentPlayer);
    }
}

void handleLoadGame() {
    bool isMultiplayer = false;
    Peasant p(0);
    Merchant m(0);
    Noble n(0);
    Population pop(0);
    Army army(0, 0, 0);
    Economy econ(0);
    Resources res(0, 0, 0, 0);
    Leadership lead("");
    KingdomEvent ev(5);
    if (GameState::loadGame(isMultiplayer, econ, army, pop, res, lead, p, m, n, ev)) {
        if (isMultiplayer) {

            multiplayerGame();
        }
        else {
            Bank bank;
            initializeGame(p, m, n, pop, army, econ, res, lead, bank, ev);
            cout << "Loaded single player game!" << endl;
            Sleep(1000);

            bool gameRunning = true;
            while (gameRunning) {
                if (ev.shouldTrigger()) {
                    EventType curr = ev.getRandomEvent();
                    ev.executeEvent(curr, pop, army, econ, res, p, m, n);
                }
                cin.ignore(); cin.clear();
                displayMainMenu();
                int choice; cin >> choice;
                system("cls");
                switch (choice) {
                case 1: {  
                    cout << endl << "=== Kingdom Status ===" << endl;
                    pop.displayPopulation();
                    army.displayArmy();
                    econ.displayEconomy();
                    res.displayResources();
                    lead.displayLeadership();
                    int tmp;
                    cout << endl<<"Enter any integer to exit: ";
                    cin >> tmp;
                } break;
                case 2:
                    armyManagementMenu(army, res);  
                    system("cls");
                    break;
                case 3:
                    populationManagementMenu(pop, res); 
                    break;
                case 4: {  
                    float newRate;
                    cout << "Enter new tax rate (0-0.5): ";
                    cin >> newRate;
                    econ.adjustTaxRate(newRate);
                    cout << "Tax rate updated!" << endl;
                    Sleep(1000);
                    system("cls");
                } break;
                case 5:
                    bankOperationsMenu(bank, econ);  
                    break;
                case 6:
                    processMonth(pop, army, econ, res, lead, p, m, n, ev);
                    break;
                case 7: { 
                    int sc;
                    cout << " [1] Save"<<endl<<" [2] Load ";
                    cout << endl << "Enter your choice : ";
                    cin >> sc;
                    if (sc == 1) {
                        GameState::saveGame(econ, army, pop, res, lead, p, m, n, ev);
                        cout << "Game saved!" << endl;
                    }
                    else {
                        handleLoadGame();  
                    }
                } break;
                case 8:
                    gameRunning = false;  
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    Sleep(1000);
                }
            }
        }
    }
    else {
        cout << "No save game found!" << endl;
        Sleep(1000);
    }
}



int main() {
    color(5, 15);
    bool programRunning = true;
    while (programRunning) {
        system("cls");
        cout << endl<<"=== STRONGHOLD KINGDOM ==="<<endl;
        cout << "[1] New Single Player Game" << endl;
        cout << "[2] New Multiplayer Game" << endl;
        cout << "[3] Load Game" << endl;
        cout << "[4] Exit" << endl;
        cout << "Choice: ";
        int mainChoice;
        cin >> mainChoice;
        cin.ignore();  
        switch (mainChoice) {
           
        case 1: {

            Peasant p(0);
            Merchant m(0);
            Noble n(0);
            Population pop(0);
            Army army(0, 0, 0);
            Economy econ(0);
            Resources res(0, 0, 0, 0);
            Leadership lead("");
            Bank bank;
            KingdomEvent ev(5);

            initializeGame(p, m, n, pop, army, econ, res, lead, bank, ev);

            bool gameRunning = true;
            while (gameRunning) {
                if (ev.shouldTrigger()) {
                    EventType curr = ev.getRandomEvent();
                    ev.executeEvent(curr, pop, army, econ, res, p, m, n);
                }
                cin.ignore(); cin.clear();
                displayMainMenu();
                int choice; cin >> choice;
                system("cls");
                switch (choice) {
                
                case 1: {
                    cout << "\n=== Kingdom Status ===\n";
                    pop.displayPopulation();
                    army.displayArmy();
                    econ.displayEconomy();
                    res.displayResources();
                    lead.displayLeadership();
                    cout << "\nEnter any integer to exit... ";
                    cin >> dummy;
					system("cls");
                } break;
                case 2:
                    armyManagementMenu(army, res);
                    system("cls");
                    break;
                case 3:
                    populationManagementMenu(pop, res);
					system("cls");
                    break;
                case 4: {
                    float newRate;
                    cout << "Enter new tax rate (0-0.5): ";
                    cin >> newRate;
                    econ.adjustTaxRate(newRate);
                    cout << "Tax rate updated!" << endl;
                    Sleep(1000);
                    system("cls");
                } break;
                case 5:
                    bankOperationsMenu(bank, econ);
					system("cls");
                    break;
                case 6:
                    processMonth(pop, army, econ, res, lead, p, m, n, ev);
                    cout << endl << "Enter any integar to exit...";
					cin >> dummy;
                    system("cls");
                    break;
                case 7: {
                    int sc;
                    cout << "[1] Save "<<endl<<"[2] Load: ";
                    cin >> sc;
                    if (sc == 1) {
                        GameState::saveGame(econ, army, pop, res, lead, p, m, n, ev);
                        cout << "Game saved!" << endl;
                    }
                    else {
                        handleLoadGame();
                    }
					system("cls");  
                } break;
                case 8:
                    gameRunning = false;
					system("cls");
                    break;
                default:
                    cout << "Invalid choice!" << endl;
					system("cls");
                    Sleep(1000);
                }
            }
        } break;
        case 2:
            multiplayerGame(); 
            break;
        case 3:
            handleLoadGame();
            break;
        case 4:
            programRunning = false; 
            break;
        default:
            cout << "Invalid choice!" << endl;
            Sleep(1000);
        }
    }

    cout << endl<<"                            === Thanks for playing Stronghold ===" << endl;
    return 0;
}
