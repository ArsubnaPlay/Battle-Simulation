#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Player {
private:
    string name;
    int health;
    int maxHealth;
    int attackPower;
    int defense;
public:
    Player(string playerName, int playerHealth, int playerAttackPower, int playerDefense)
        : name(playerName), health(playerHealth), maxHealth(playerHealth),
          attackPower(playerAttackPower), defense(playerDefense) {}

    void attack(Player& enemy) {
        int damage = calculateDamage(enemy);
        enemy.health -= damage;
        cout << name << " attacks " << enemy.name << " for " << damage << " damage." << endl;
    }

    int calculateDamage(const Player& enemy) const {
        int baseDamage = rand() % attackPower + 1;
        int reducedDamage = baseDamage - enemy.defense;
        return (reducedDamage > 0) ? reducedDamage : 0;
    }

    void heal(int amount) {
        health += amount;
        if (health > maxHealth)
            health = maxHealth;
        cout << name << " heals for " << amount << " health." << endl;
    }

    bool isAlive() const {
        return health > 0;
    }

    string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    int getMaxHealth() const {
        return maxHealth;
    }

    int getAttackPower() const {
        return attackPower;
    }

    int getDefense() const {
        return defense;
    }
};

void displayPlayerStats(const Player& player) {
    cout << player.getName() << "'s Stats:" << endl;
    cout << "Health: " << player.getHealth() << "/" << player.getMaxHealth() << endl;
    cout << "Attack Power: " << player.getAttackPower() << endl;
    cout << "Defense: " << player.getDefense() << endl;
    cout << endl;
}

int main() {
    srand(time(0));

    Player player1("Player 1", 100, 20, 5);
    Player player2("Player 2", 100, 15, 8);

    Player* currentPlayer = &player1;
    Player* enemyPlayer = &player2;

    while (player1.isAlive() && player2.isAlive()) {
        cout << "----- " << currentPlayer->getName() << "'s Turn -----" << endl;
        displayPlayerStats(*currentPlayer);
        displayPlayerStats(*enemyPlayer);

        int choice;
        cout << "Choose an action:" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Heal" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                currentPlayer->attack(*enemyPlayer);
                break;
            case 2:
                int healAmount;
                cout << "Enter the amount to heal: ";
                cin >> healAmount;
                currentPlayer->heal(healAmount);
                break;
            default:
                cout << "Invalid choice. Skipping turn." << endl;
        }

        // Swap the current player and the enemy player
        swap(currentPlayer, enemyPlayer);

        cout << "----------------------------------" << endl;
    }

    // Determine the winner
    Player& winner = (player1.isAlive()) ? player1 : player2;
    cout << winner.getName() << " wins the battle!" << endl;

    return 0;
}
