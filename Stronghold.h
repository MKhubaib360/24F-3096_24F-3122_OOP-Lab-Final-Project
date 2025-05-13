#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class Population;
class Army;
class Economy;
class Resources;
class Leadership;
class Peasant;
class Merchant;
class Noble;
class KingdomEvent;
class MapGrid;

class SocialClass {
	protected:
		string socialName;
		int population;  
		float happiness;
	public:  
		SocialClass(string n, int pop);

		void setHappiness(float h) { happiness = h; }
		void setPopulation(int pop) { population = pop; } 

		int getPopulation() const;
		float getHappiness() const { return happiness; }
		void display() const;
	};

class Peasant : public SocialClass
{
public:
	Peasant(int pop);
	void updatePeasant();
};

class Noble : public SocialClass
{
public:
	Noble(int pop);
	void updateNoble();
};

class Merchant : public SocialClass
{
public:
	Merchant(int pop);
	void updateMerchant();
};

class Resources {
private:
	int food;
	int wood;
	int stone;
	int iron;
public:
	Resources(int f, int w, int s, int i);

	bool consumeFood(int amount);
	bool consumeStone(int amount);
	bool consumeIron(int amount);
	bool consumeWood(int amount);

	void gatherFood(int amount);
	void gatherWood(int amount);
	void gatherStone(int amount);
	void gatherIron(int amount);

	void spoilFood();
	void displayResources() const;

	void setFood(int f) { food = f; }
	void setWood(int w) { wood = w; }
	void setStone(int s) { stone = s; }
	void setIron(int i) { iron = i; }

	int getFood() const { return food; }
	int getWood() const { return wood; }
	int getStone() const { return stone; }   
	int getIron() const { return iron; }     
};

class Population
{
protected:
	int total, ill, births, deaths;
	int shelter;

public:
	Population(int t);
	void updatePopulation(const Resources& res);
	void displayPopulation() const;
	bool isStable();

    void setTotal(int t) { total = t; }
    void setIll(int i) { ill = i; }
    void setBirths(int b) { births = b; }
    void setDeaths(int d) { deaths = d; }
	void setShelter(int s) { shelter = s; }

	int getShelter() const { return shelter; }
	int getTotal() const { return total; }
	int getIll() const { return ill; }
	int getBirths() const { return births; }
	int getDeaths() const { return deaths; }
};

class Army
{
protected:
	int recruit;
	int morale, corruption, trained_soldiers, foodStock, salary_fund;
public:
	Army(int rec, int food, int gold);
	void recruitt(int newRecruit);
	void train(int days);
	void autoFeed(Resources& res);
	void manualFeed(Resources& res);
	void pay(int gold);
	void updateMorale(bool StableLeadership);
	void displayArmy() const;

	void setRecruits(int r) { recruit = r; }
    void setMorale(int m) { morale = m; }
    void setCorruption(int c) { corruption = c; }
    void setTrainedSoldiers(int t) { trained_soldiers = t; }
    void setFoodStock(int f) { foodStock = f; }
    void setSalaryFund(int s) { salary_fund = s; }

	int getMorale() const;
	int getCorruption() const;
	int getRecruits() const { return recruit; }
	int getTrainedSoldiers() const;
	int getFoodStock() const { return foodStock; }
    int getSalaryFund() const { return salary_fund; }
};

class Economy {
	private:
		float treasury;
		float tax_rate;
		float inflation;
	public:
		Economy(float ig);

		void collectTaxes(const Population& pop, const Peasant& peasants, const Merchant& merchants);  
		void payArmy(Army& army); 
		void adjustTaxRate(float newRate);
		void adjustTreasury(int amount);
		void applyInflation();
		void displayEconomy() const;

		void setTreasury(float t) { treasury = t; }
        void setTaxRate(float tr) { tax_rate = tr; }
        void setInflation(float inf) { inflation = inf; }

		float getTaxRate() const { return tax_rate; }
		float getTreasury() const { return treasury; }
        float getInflation() const { return inflation; }
	};

class Leadership {
	private:
		string ruler_name;
		bool isStable;
	public:
		Leadership(string name);
		void displayLeadership() const;

		void setStability(bool s) { isStable = s; }
		bool getStability() const;
	};

class Bank {
	private:
		float interestRate;
		float corruptionLevel;
		float loanDebt;
	public:
		Bank();
		void takeLoan(Economy& economy, float amount);
		void repayLoan(Economy& economy, float amount);
		void conductAudit(Economy& economy);
		void displayBank() const;
	};

enum class EventType { NONE, FAMINE, PLAGUE, FLOOD, TORNADO,ECONOMIC_CRISIS, CORRUPTION, REVOLT };

class KingdomEvent {
private:
	time_t lastTrigger;
	int intervalMinutes;  
	EventType lastEvent;

public:
	KingdomEvent(int minutes);
	time_t getLastTrigger() const { return lastTrigger; }
	int getIntervalMinutes() const { return intervalMinutes; }
	EventType getLastEvent() const { return lastEvent; }
	void setLastTrigger(time_t lt) { lastTrigger = lt; }
	void setIntervalMinutes(int im) { intervalMinutes = im; }
	void setLastEvent(EventType le) { lastEvent = le; }

	bool shouldTrigger();
	EventType getRandomEvent() const;
	void executeEvent(EventType type, Population& pop, Army& army,Economy& econ, Resources& res,Peasant& p, Merchant& m, Noble& n);
	void applyEffects(EventType type, Population& pop, Army& army,Economy& econ, Resources& res, Peasant& p, Merchant& m, Noble& n);
};

class GameState {
private:
	static const string SINGLEPLAYER_SAVE;
	static const string MULTIPLAYER_SAVE;

	static bool fileExists(const string& filename) {
		ifstream f(filename);
		return f.good();
	}

public:

	static void saveGame(const Economy& econ, const Army& army,
		const Population& pop, const Resources& res,
		const Leadership& lead, const Peasant& p,
		const Merchant& m, const Noble& n,
		const KingdomEvent& events);

	static bool loadGame(Economy& econ, Army& army, Population& pop,
		Resources& res, Leadership& lead, Peasant& p,
		Merchant& m, Noble& n, KingdomEvent& events);

	static bool loadGame(bool& isMultiplayer, Economy& econ, Army& army,
		Population& pop, Resources& res, Leadership& lead,
		Peasant& p, Merchant& m, Noble& n, KingdomEvent& events);

	static void saveGameMultiplayer();
};

class NetworkHandler {
private:
	static const string CHAT_FILE;    
	static string messages[4]; 
public:
	static void sendMessage(int senderID, int receiverID, const string& msg);
	static string getMessages(int playerID);
	static void showChatHistory(int playerID);
	static void clearSession();
};

class AllianceManager {
private:
	static const string ALLIANCE_FILE;

public:

	enum TreatyType { NON_AGGRESSION, DEFENSE_PACT, FULL_ALLIANCE };

	static void proposeTreaty(int proposerID, int targetID, TreatyType type);
	static void breakTreaty(int breakerID, int targetID);
	static void displayAlliances(int playerID);
	static bool hasTreaty(int player1, int player2);
};

class TradeSystem {
private:
	static const string TRADE_FILE;

public:
	enum ResourceType { FOOD, WOOD, STONE, IRON, GOLD };

	static void proposeTrade(int senderID, int receiverID,
		ResourceType offerType, int offerQty,
		ResourceType requestType, int requestQty);

	static void displayTradeHistory(int playerID);
	static bool acceptTrade(int tradeID); 
};

class ConflictResolver {
private:
	static const string BATTLE_LOG_FILE;

public:
	enum Outcome { ATTACKER_WINS, DEFENDER_WINS, STALEMATE };

	static Outcome resolveBattle(Army& attackerArmy, Army& defenderArmy,
		const Leadership& attackerLead,
		const Leadership& defenderLead);

	static void displayBattleHistory(int playerID);
	static void applyBattleEffects(Outcome result, Army& winner,
		Army& loser, Economy& economy);
};


class MapGrid {
private:
	static const int GRID_SIZE = 10;
	char grid[GRID_SIZE][GRID_SIZE];
	int controllers[GRID_SIZE][GRID_SIZE]; 

	void applyTerrainBonus(int x, int y, Resources& res);

public:
	MapGrid();

	void initializeMap();
	void displayMap() const;
	bool moveArmy(int playerID, int oldX, int oldY, int newX, int newY);
	void updateControl(int playerID, int x, int y, const Army& army);
	void processTerrainBonuses(Resources& res, int playerID);

	void saveMap(const string& filename) const;
	void loadMap(const string& filename);
};

class MultiplayerState {
public:
	static const int MAX_PLAYERS;
	static const string STATE_FILE;
	static MapGrid gameMap;
	static int currentTurn;

	struct PlayerData {
		KingdomEvent events;
		Economy economy;
		Army army;
		Population population;
		Resources resources;
		Leadership leadership;
		Peasant peasants;
		Merchant merchants;
		Bank bank;
		Noble nobles;
		int mapX, mapY;

		PlayerData(int startPop);
	};

	static PlayerData players[4];

public:
	static void initializeGame();
	static void saveGame();
	static bool loadGame();
	static void processTurn();
	static void showPlayerStatus(int playerID);
};



inline void processMonth(Population& pop, Army& army, Economy& econ,
	Resources& res, Leadership& lead,
	Peasant& p, Merchant& m, Noble& n,
	KingdomEvent& events) {
	system("cls");
	cout << "--- PROCESSING MONTH ---" << endl;

	pop.updatePopulation(res);
	p.updatePeasant();
	m.updateMerchant();
	n.updateNoble();
	econ.collectTaxes(pop, p, m);
	econ.payArmy(army);
	econ.applyInflation();
	army.updateMorale(lead.getStability());	res.spoilFood(); 

	cout <<endl<< "--- MONTHLY REPORT ---" << endl;
	pop.displayPopulation();
	army.displayArmy();
	econ.displayEconomy();
	res.displayResources();
	lead.displayLeadership();
}