#include <Rooms/BattleRoom.h> //Used to gain access to the room definition for creating and executing rooms
#include <GameVariables.h> //Used to gain access to common game variables
#include <iostream> //Used to gain access to cout for printing to the console
#include <Rooms/HallwayEndRoom.h> //Used to gain access to the room definition for creating and executing rooms
#include <Battle.h> //Used to gain access to the battle class. Used to start battles
#include <Inventory.h> //Used to gain access to viewing and modifying the inventory
#include <gameFunctions.h> //Used to gain access to common game functions

using namespace std; //Used to prevent me from having to type "std::cout" everywhere

//Called when the room starts
void BattleRoom::OnStart()
{
	//Clear the screen
	ClearConsole();
	//If the zombie has not been defeated yet
	if (!Variables::battledZombie)
	{
		//Print the normal intro
		cout << "You slowly enter the dark hallway. As soon as you enter the room, the large, metal door behind you locks shut.\n";
		cout << "You tried the Small Key you picked up earlier, but it doesn't seem to work.\n";
		cout << "You begin walking slowly down the hallway\n";
		cout << "The hallway then turns into a large room.\n";
		cout << "You see a person standing in the opposite corner of the room.\n";
	}
	//If the zombie has been defeated
	else
	{
		//Print the intro where the zombie is defeated
		cout << "You are back in the large room where you fought the zombie.\n";
	}
}

//Called when a command is entered
void BattleRoom::OnCommand(std::string Command, std::vector<std::string> Arguments)
{
	//if the "GO" command is entered
	if (Command == "GO")
	{
		//If the player wants to go "OUT" of the room
		if (GoCommandShortcut(Arguments, { {"OUT","Go out of the room and back into the hallway"} }) == 0)
		{
			//If the player has battled the zombie and has gotten the silver key
			if (Variables::battledZombie)
			{
				//Go back into the hallway end room
				GoToRoom<HallwayEndRoom>();
			}
			//If the zombie has not been battled yet and the door is still locked
			else
			{
				//Tell the player that they cannot leave yet
				cout << "You can't leave since the door is still locked\n";
			}
		}
	}
	//If an invalid command has been entered
	else
	{
		//Tell the player that an invalid command has been entered
		InvalidCommand();
	}
}

//Called when the player inspects the room
void BattleRoom::Inspect()
{
	//If the zombie has not been defeated yet
	if (!Variables::battledZombie)
	{
		//Print the zombie encounter
		cout << "You get a closer look at the person in the corner.\n";
		cout << "The person suddenly turns around, and you see that it is a zombie!\n";
		cout << "It does not look very happy with you at the moment.\n";

		//Wait for the player's input
		Pause();

		//Create the battle scenario
		Battle ZombieBattle = Battle(Variables::PlayerName, "The Zombie");

		//Begin the battle
		if (ZombieBattle.Play())
		{
			//If the player won the battle

			//Clear the screen
			ClearConsole();

			//Tell the player that they found a silver key
			cout << "You go up to the now dead zombie.\n";
			cout << "You see something in one of it's pockets\n";
			cout << "There was a silver key in the pocket\n";
			//Add the silver key to the inventory
			Inventory::AddItem("Silver Key");

			//Convert the door code to a string and cut out the last two characters
			string secondPart = to_string(Variables::doorCode);
			secondPart.erase(2, 2);
			secondPart += "__";

			//Tell the player that the ripped note was found
			cout << "You also see a ripped note along with it. You attempt to read what it says\n";
			cout << "It says: " << secondPart << "\n";

			//Add the note to the player's inventory
			Inventory::AddItem(string("Ripped Note with code : ") + secondPart);

			//Tell the player that the door is unlocked
			cout << "You try using the key on the door\n";
			cout << "The key was able to unlock the door and you are now able to leave the room\n";
			//Set the battled zombie flag to true
			Variables::battledZombie = true;
		}
		//If the player lost the battle
		else
		{
			//Clear the screen
			ClearConsole();
			//Print the game over screen
			cout << "Game Over!\n\n";
			//Quit the game
			Quit();
		}
	}
	//If the zombie has already been battled
	else
	{
		//Tell the player that they didn't find anything useful
		cout << "After looking around, you don't find anything useful\n";
	}
}

//Returns the name of the room
std::string BattleRoom::GetName() const
{
	//Return the room name
	return "BattleRoom";
}
