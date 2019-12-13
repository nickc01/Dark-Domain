#pragma once
#include <string> //Used to gain access to "std::string"
#include <tuple> //Used to gain access to the "std::tuple<>" type
#include "gameEnums.h" //Used to gain access to common game enums, such as "Color", and "Anchor"

//Determines which action to take during a battle
enum class BattleAction
{
	Attack, //Attack the opponent
	Defend //Defend from the opponent
};

//The stats of an opponent in a battle
struct Stats
{
	std::string Name; //The name of the opponent
	int Health; //The health of the opponent
	int MaxHealth; //The maximum health of the opponent
	bool Defending; //Whether the opponent is defending

	//The constructor for easily creating the stats object
	Stats(std::string name, int health) : Name(name), Health(health), MaxHealth(health), Defending(false) {}
};

//The battle object. Used to initiate a battle
class Battle final
{
private:
	Stats playerStats; //The stats of the player
	Stats enemyStats; //The stats of the enemy

	float critChance = 0.10f; //The chance a critical hit can occur
	float missChance = 0.15f; //The chance an attack can miss

	int averageAttackDamage = 25; //The average amount of damage a normal attack can do

	//Draws the battle to the screen
	void Draw();
	//Prepares for the next round
	void Prepare();
	//Gets the action the player wants to take
	BattleAction GetAction();
	//Gets a random actions. Used for enemy logic
	BattleAction RandomAction();
	//Draws a healh area
	void DrawHealthArea(int health, int maxHealth,int size);
	//Draws the line that makes up the health bar
	void DrawHealthBarLine(int health, int maxHealth, int barSize,Anchor anchor,std::tuple<Color, Color> Color);
	//Draws the stats of an opponent to the screen
	void DrawStats(std::string name, int health, int maxHealth,Anchor anchor, Color mainColor,int size = 30);
	//Attacks a specified opponent
	std::string Attack(Stats* sender, Stats* opponent);

public:

	//Constructor for easily creating the Battle Object
	Battle(std::string PlayerName, std::string EnemyName, int PlayerHealth = 100, int EnemyHealth = 75);

	//Plays the battle. Returns true if the player wins, and false otherwise
	bool Play();
};