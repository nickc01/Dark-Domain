#include "Battle.h" //Used to gain access to the battle class. Used to start battles //Used to access the prototypes for the battle class. 
#include "gameFunctions.h" //Used to gain access to common game functions //Used to gain access to common game functions
#include <iostream> //Used to gain access to cout for printing to the console //Used to gain access to cout for printing to the console

using namespace std; //Used to prevent me from having to type "std::cout" everywhere

//AN ascii representation of a zombie
string zombieAscii = R"(
                
      __        
     /..\       
     \__/       
   \  ||  /     
    \ || /      
     \||/       
      ||        
      ||        
     //\\       
    //  \\      
   //    \\     
                
                
)";

//Draws the battle stats to the screen
void Battle::Draw()
{
	//Clear the screen
	ClearConsole();

	//Get the width of the console
	auto width = get<0>(GetConsoleDimensions());

	//Set the text color to light aqua
	SetColor(Color::Black, Color::LightAqua);

	//Print the top title section
	cout << PadOutString("Battle", width, '=') << "\n";
	
	//Draw the enemy's stats
	DrawStats(enemyStats.Name, enemyStats.Health, enemyStats.MaxHealth,Anchor::Right,Color::LightRed);

	//Print out the zombie ascii character
	PrintAnchoredMultiline(zombieAscii, Anchor::Middle, { Color::Black,Color::LightGreen });

	//Draw the player's stats
	DrawStats(playerStats.Name, playerStats.Health, playerStats.MaxHealth, Anchor::Left, Color::LightGreen);

	//Set the text color back to Light Aqua.
	SetColor(Color::Black, Color::LightAqua);

	//Print the bottom battle section
	cout << PadOutString("", width, '=') << "\n";
}

//Prepares the battle for the next turn
void Battle::Prepare()
{
	//Reset the defending variables
	playerStats.Defending = false;
	enemyStats.Defending = false;
}

//Gets the player's action
BattleAction Battle::GetAction()
{
	//Set the text color to light yellow
	SetColor(Color::Black, Color::LightYellow);

	//Tell the player the actions that they can take
	cout << "Enter an action:\n";
	cout << "ATTACK : Attempt to attack " << enemyStats.Name << "\n";
	cout << "DEFEND : Take a defensive stance against " << enemyStats.Name << ". Will reduce damage taken\n";

	//Repeat until the player has entered a valid option
	while (true)
	{
		//Get the player's input
		string input = GetString();
		//Set the color back to normal
		SetColor(Color::Black, Color::BrightWhite);
		//If the input is ATTACK
		if (input == "ATTACK")
		{
			//Return the attack battle action
			return BattleAction::Attack;
		}
		//If the input is DEFEND
		else if (input == "DEFEND")
		{
			//Return the defend battle action
			return BattleAction::Defend;
		}
		//If an invalid option has been entered
		else
		{
			//Tell the player that an invalid option has been entered
			InvalidCommand("Not a valid action. Type in either \"ATTACK\" or \"DEFEND\"");
			//Try getting the player's input again
			continue;
		}
	}
}

//Gets a random action. Used for the enemy logic
BattleAction Battle::RandomAction()
{
	//Get a random selection between 0 and 1
	int randomSelection = rand() % 2;
	//Return a battle action based off of the number selection
	if (randomSelection == 0)
	{
		return BattleAction::Attack;
	}
	else if (randomSelection == 1)
	{
		return BattleAction::Defend;
	}
	//If an invalid option has been entered
	else
	{
		//Throw an exception
		throw exception();
	}
}

//Draws a health area
void Battle::DrawHealthArea(int health, int maxHealth,int size)
{
	//Store the previous color
	auto previousColor = GetColor();

	//Convert the health number to a string
	string healthString = to_string(health);

	//Get the left and right padding for centering the text
	int leftPadding = (size - healthString.length()) / 2;
	int rightPading = size - healthString.length() - leftPadding;

	//Calculate the health percentage
	float healthBarPercent = ((float)health) / (float)maxHealth;

	//Gets the length of the green section of the health bar
	int greenLength = (int)(((float)size) * healthBarPercent);

	//Loop over all the parts of the health bar
	for (int i = 0; i < size; i++)
	{
		//If the current index is not in the green section
		if (i >= greenLength)
		{
			//Set the background color to red
			SetColor(Color::LightRed, Color::Black);
		}
		//If the current index is in the green section
		else
		{
			//Set the background color to green
			SetColor(Color::LightGreen, Color::Black);
		}
		//If the current index is in the left padding area
		if (i >= 0 && i < leftPadding)
		{
			//Print out a space for padding
			cout << " ";
		}
		//If the current index is between the left and right padding area
		else if (i >= leftPadding && i < (leftPadding + healthString.length()))
		{
			//Print the corresponding character in the health string
			cout << healthString[i - leftPadding];
		}
		//If the current index is in the right padding area
		else
		{
			//Print out a space for padding
			cout << " ";
		}
	}
	//Set the color back to the previous
	SetColor(previousColor);
}

//Draws the entire heatlh bar line
void Battle::DrawHealthBarLine(int health, int maxHealth, int barSize, Anchor anchor, std::tuple<Color, Color> Color)
{
	//Store the previous color
	auto previousColor = GetColor();
	//Get the console width
	auto width = get<0>(GetConsoleDimensions());

	//Set the color to the one specified
	SetColor(Color);
	//If the line is to be drawn on the right side of the screen
	if (anchor == Anchor::Right)
	{
		//Print out the necessary padding
		PrintPadding(width - (barSize + 4));
		//Print the opening bracket
		cout << " [";
		//Draw the health bar itself
		DrawHealthArea(health, maxHealth, barSize);
		//Print the closing bracket
		cout << "] ";
	}
	//If the line is to be drawn on the left side of the screen
	else if (anchor == Anchor::Left)
	{
		//Print the opening bracket
		cout << " [";
		//Draw the health bar itself
		DrawHealthArea(health, maxHealth, barSize);
		//Print the closing bracket
		cout << "] ";
		//Print out the necessary padding
		PrintPadding(width - (barSize + 4));
	}
	//If the line is to be drawn in the middle of the screen
	else if (anchor == Anchor::Middle)
	{
		//Get the padding for the left and right sides
		int leftPadding = (width - (barSize + 4)) / 2;
		int rightPadding = width - (barSize + 4) - leftPadding;

		//Print the left padding
		PrintPadding(leftPadding);
		//Print the opening bracket
		cout << " [";
		//Draw the health bar itself
		DrawHealthArea(health, maxHealth, barSize);
		//Print the closing bracket
		cout << "] ";
		//Print the right padding
		PrintPadding(rightPadding);
	}
	//Set the color back to the previous color
	SetColor(previousColor);
	
}

//Draws the statistics of an opponent in the game
void Battle::DrawStats(string name, int health, int maxHealth,Anchor anchor,Color mainColor,int size)
{
	//Create the bars used to seperate elements
	string bar = "  " + string(size,'=') + "  ";

	//Print the top bar
	PrintAnchored(bar, anchor, { Color::Black,mainColor });
	//Print out the name element
	PrintAnchored(" [ " + PadOutString(name, size - 2) + " ] ", anchor, { Color::Black,mainColor });
	//Print the bottom bar
	PrintAnchored(bar, anchor, { Color::Black,mainColor });
	//Print the health bar
	DrawHealthBarLine(health, maxHealth, size,anchor, { Color::Black,mainColor });
	//Go to a new line
	cout << "\n";
}

//Attacks a specified opponent
std::string Battle::Attack(Stats* sender,Stats* receiver)
{
	//Store the output messages
	string outputMessage;
	//Whether the attacker is doing a critical hit or not
	bool crit = false;
	//How much attack damage the attacker is going to deal
	int attackDamage = averageAttackDamage;
	//If the attacker is doing a critical hit
	if (ChanceRandomizer(critChance))
	{
		//Set the flag to true
		crit = true;
		//Double the damage
		attackDamage *= 2;
	}
	//If the receiver is defending
	if (receiver->Defending)
	{
		//Half the damage
		attackDamage /= 2;
	}
	//Vary the attack damage by about +5 or -5
	attackDamage += (rand() % 11) - 5;
	//if the attacker missed
	if (ChanceRandomizer(missChance))
	{
		//Set the damage to zero
		attackDamage = 0;
	}
	//If there is no damage to deal
	if (attackDamage <= 0)
	{
		//Tell the attacker that they missed
		outputMessage += sender->Name + " Missed!\n\n";
	}
	//If there is damage to deal
	else
	{
		//If it's a critical hit
		if (crit)
		{
			//Tell the attacker that it's a critical hit
			outputMessage += "CRITICAL HIT!  ";
		}
		//Print the amount of damage delt to the opponent
		outputMessage += sender->Name + " hit " + receiver->Name + " with " + to_string(attackDamage) + " damage!\n\n";
		//Reduce the health of the opponent
		receiver->Health -= attackDamage;
		//If the health is less than zero, then set it back up to zero
		if (receiver->Health < 0)
		{
			receiver->Health = 0;
		}
	}
	//Return the output messages
	return outputMessage;
}

//Used to easily construct a battle class
Battle::Battle(string PlayerName, string EnemyName, int PlayerHealth, int EnemyHealth) :
	playerStats(PlayerName,PlayerHealth),
	enemyStats(EnemyName,EnemyHealth)
{}

//Plays a battle. Returns true if the player wins, and false if not
bool Battle::Play()
{
	//Store the previous color
	auto previousColor = GetColor();
	//Draw the battle stats
	Draw();
	//Set the text color to aqua
	SetColor(Color::Black, Color::LightAqua);
	//The battle begins!
	cout << "Let the battle begin!\n";

	//Repeat until the battle is over
	while (true)
	{
		//Prepare for the next round
		Prepare();
		//Store the print messages
		string postPrint = "";

		//Get the player's action
		BattleAction action = GetAction();

		//If the player is defending
		if (action == BattleAction::Defend)
		{
			//Set the defending flag to true
			playerStats.Defending = true;
			//Tell the player that they are defending
			postPrint += playerStats.Name + " got into a defensive pose\n\n";
		}

		BattleAction enemyAction = RandomAction();

		if (enemyAction == BattleAction::Defend)
		{
			//Set the defending flag to true
			enemyStats.Defending = true;
			//Tell the enemy that they are defending
			postPrint += enemyStats.Name + " got into a defensive pose\n\n";
		}
		
		//If the player wants to attack
		if (action == BattleAction::Attack)
		{
			//Attack the enemy and store the print messages
			postPrint += Attack(&playerStats, &enemyStats);
		}
		//If the enemy wants to attack
		if (enemyAction == BattleAction::Attack)
		{
			//Attack the player and store the print messages
			postPrint += Attack(&enemyStats, &playerStats);
		}
		//If neither the player nor the enemy attack
		if (action != BattleAction::Attack && enemyAction != BattleAction::Attack)
		{
			//Tell the player that nothing happened
			postPrint += "Nothing Happened\n\n";
		}

		//Redraw the screen
		Draw();

		//Print the post messages for that round
		cout << postPrint;

		//If the player has no more health left
		if (playerStats.Health == 0)
		{
			//Tell the player that they lost
			SetColor(Color::Black,Color::LightYellow);
			cout << playerStats.Name << " died and lost the battle!\n\n";
			SetColor(Color::Black, Color::LightAqua);
			//Wait for player input
			Pause();
			//Return false, signifying a failure
			return false;
		}
		//if the player has health left and the enemy has no health
		else if (enemyStats.Health == 0)
		{
			//Tell th eplayer that they won
			SetColor(Color::Black, Color::LightYellow);
			cout << "The " << enemyStats.Name << " died! You won!\n\n";
			SetColor(Color::Black, Color::LightAqua);
			//Wait for player input
			Pause();
			//Return true signifying a win
			return true;
		}
	}
	//Reset the color
	SetColor(previousColor);
}
