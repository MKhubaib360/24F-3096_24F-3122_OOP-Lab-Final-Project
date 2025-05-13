#include "Stronghold.h"
using namespace std;

int dummy;

void displayMainMenu() {
    cout << "\n---StrongHold Kingdom Management---" << endl;
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

void multiplayerGame() {
    MultiplayerState::initializeGame();
    bool multiplayerRunning = true;

    while (multiplayerRunning) {
        int currentPlayer = MultiplayerState::currentTurn;
        auto& player = MultiplayerState::players[currentPlayer];

        bool turnActive = true;
        while (turnActive) {
            system("cls");
            cout << "\n=== PLAYER " << (currentPlayer + 1) << "'s TURN ===" << endl;

            MultiplayerState::gameMap.displayMap();
            AllianceManager::displayAlliances(currentPlayer);

            cout << "\n=== KINGDOM MANAGEMENT ===" << endl;
            cout << "1. Kingdom Operations\n";
            cout << "2. Diplomacy & Alliances\n";
            cout << "3. Trade with Others\n";
            cout << "4. Military Actions\n";
            cout << "5. View Chat\n";
            cout << "6. End Turn\n";
            cout << "7. Save & Exit\n";
            cout << "Choice: ";

            int mainChoice;
            cin >> mainChoice;

            switch (mainChoice) {
            case 1: { 
                bool inKingdomMenu = true;
                while (inKingdomMenu) {
                    system("cls");
                    cout << "\n=== KINGDOM OPERATIONS ===" << endl;
                    cout << "1. View Kingdom Status\n";
                    cout << "2. Manage Army\n";
                    cout << "3. Manage Population & Resources\n";
                    cout << "4. Adjust Taxes\n";
                    cout << "5. Bank Operations\n";
                    cout << "6. Process Next Month\n";
                    cout << "7. Return to Main Menu\n";
                    cout << "Choice: ";

                    int kingdomChoice;
                    cin >> kingdomChoice;

                    switch (kingdomChoice) {
                    case 1: {
                        cout << "\n--- Kingdom Status ---\n";
                        player.population.displayPopulation();
                        player.army.displayArmy();
                        player.economy.displayEconomy();
                        player.resources.displayResources();
                        player.leadership.displayLeadership();
                        cout << "\nPress Enter to continue...";
                        cin.ignore();
                        cin.get();
                        break;
                    }
                    case 2:
                        armyManagementMenu(player.army, player.resources);
                        break;
                    case 3:
                        populationManagementMenu(player.population, player.resources);
                        break;
                    case 4: {
                        float newRate;
                        cout << "Enter new tax rate (0-0.5): ";
                        cin >> newRate;
                        player.economy.adjustTaxRate(newRate);
                        cout << "Tax rate updated!\n";
                        Sleep(1000);
                        break;
                    }
                    case 5:
                        bankOperationsMenu(player.bank, player.economy);
                        break;
                    case 6:
                        processMonth(player.population, player.army, player.economy,
                            player.resources, player.leadership,
                            player.peasants, player.merchants,
                            player.nobles, player.events);
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
                cout << "\n=== DIPLOMACY ===" << endl;
                cout << "1. Propose Treaty\n";
                cout << "2. Break Treaty\n";
                cout << "3. View Alliances\n";
                cout << "4. Back\n";
                cout << "Choice: ";

                int allianceChoice;
                cin >> allianceChoice;
                switch (allianceChoice) {
                case 1: {
                    int targetPlayer;
                    cout << "Target Player (1-4): ";
                    cin >> targetPlayer;
                    cout << "Treaty Type (1-3):\n1. Non-Aggression\n2. Defense Pact\n3. Full Alliance\n";
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
                cout << "\n=== TRADE ===" << endl;
                cout << "1. Propose Trade\n";
                cout << "2. View Trade Offers\n";
                cout << "3. Accept Trade\n";
                cout << "4. Back\n";
                cout << "Choice: ";

                int tradeChoice;
                cin >> tradeChoice;
                switch (tradeChoice) {
                case 1: {
                    int targetPlayer;
                    cout << "Target Player: ";
                    cin >> targetPlayer;

                    cout << "Offer (1-5):\n1.Food 2.Wood 3.Stone 4.Iron 5.Gold\n";
                    int offerType, offerQty;
                    cout << "Type: "; cin >> offerType;
                    cout << "Quantity: "; cin >> offerQty;

                    cout << "Request (1-5):\n1.Food 2.Wood 3.Stone 4.Iron 5.Gold\n";
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
                cout << "\n=== MILITARY COMMANDS ===" << endl;
                cout << "1. Move Army\n";
                cout << "2. Attack Player\n";
                cout << "3. View Battle History\n";
                cout << "4. Back\n";
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
                cout << "\n=== COMMUNICATIONS ===" << endl;
                cout << "1. Send Message\n";
                cout << "2. Read Messages\n";
                cout << "3. Back\n";
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
                    cout << "\n---Kingdom Status---\n";
                    pop.displayPopulation();
                    army.displayArmy();
                    econ.displayEconomy();
                    res.displayResources();
                    lead.displayLeadership();
                    int tmp;
                    cout << "\nEnter any integer to exit: ";
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
                    cout << "1. Save 2. Load: ";
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
    system("cls");
    cout << endl << endl << endl << endl;
    cout << string(140, '*') << endl;
    cout << "***   Welcome to StrongHold   ***" << endl;
    cout << string(140, '*') << endl;

    bool programRunning = true;
    while (programRunning) {

        system("cls");
        cout << "\n=== STRONGHOLD KINGDOM ===\n";
        cout << "1. New Single Player Game\n";
        cout << "2. New Multiplayer Game\n";
        cout << "3. Load Game\n";
        cout << "4. Exit\n";
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
                    cout << "\n---Kingdom Status---\n";
                    pop.displayPopulation();
                    army.displayArmy();
                    econ.displayEconomy();
                    res.displayResources();
                    lead.displayLeadership();
                    int tmp;
                    cout << "\nEnter any integer to exit: ";
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
                    cout << "1. Save 2. Load: ";
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

    cout << "\nThanks for playing Stronghold" << endl;
    return 0;
}
