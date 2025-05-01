
# 🏰 StrongHold - Kingdom Management Simulation

**StrongHold** is a text-based simulation game where you manage the economy, military, population, and resources of a medieval kingdom. You take the role of a ruler and make strategic decisions to grow and maintain the stability of your kingdom through events, seasons, and crises.

---

## 🧩 Features

- 👥 **Population System**: Manage peasants, merchants, and nobles with housing and shelter management.
- 🛠️ **Resource Management**: Gather and consume food, wood, stone, and iron.
- 🪖 **Army Mechanics**: Recruit, train, feed, and pay your soldiers while maintaining morale and reducing corruption.
- 💰 **Economy and Taxation**: Adjust tax rates, manage inflation, and oversee your treasury.
- 🏦 **Bank System**: Take loans, repay debts, and conduct audits with risks of corruption.
- 👑 **Leadership & Stability**: The ruler's stability affects morale and resilience against disasters.
- 🌪️ **Random Events**: Famine, plagues, floods, and more will challenge your leadership.
- 💾 **Save & Load**: Persist your progress between sessions.

---

## 🛠️ Requirements

- C++17 or higher
- Windows OS (uses `windows.h` for some UI functionality)
- A terminal/console that supports system commands like `cls`

---

## 🚀 How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/stronghold.git
   cd stronghold
   ```

2. Compile the program:
   ```bash
   g++ Main.cpp -o Stronghold.exe
   ```

3. Run the game:
   ```bash
   ./Stronghold.exe
   ```

---

## 📁 File Structure

- `Main.cpp` - Game loop and UI menus
- `Stronghold.h` - Class definitions for game components like population, army, economy, etc.
- `stronghold_save.txt` - Auto-generated file to save game state

---

## 🎮 Controls

- Navigate menus using number keys
- Use `Enter` to confirm and continue
- Modify tax rates, resources, and army operations from respective menus

---

## 📝 Notes

- Save files are stored locally in the same directory
- Designed for educational and entertainment purposes

---

## 📌 TODO / Future Work

- Add GUI using SFML or SDL
- Include diplomacy and trade systems
- Add custom event scripting

---

## 📄 License

This project is licensed under the MIT License.
