/* 

    NOTE - EVERYTHING I'M DOING HERE
    IS PURE C++. THIS WONT WORK WITH
    THE PROTEUS. THIS IS BASICALLY
    A CONSOLE VERSION OF THE PROTEUS
    PROGRAM. 

    Basically, the goal is to make a fully 
    funtioning c++ version and just port it 
    over to the proteus. This basically means
    just changing certain function calls
    and implementing the buttons system or 
    w/e we end up doing.

*/

#include <iostream>

using namespace std;

// The player class - What the user plays as 
class Player
{
    public: 

        /* There is zero chance that what I'm about to do is best practice, but here we go nonetheless */ 

        int getCurrentHP()
        {
            return currentHP; 
        }

        int getMaxHP()
        {
            return maxHP;
        }

        int getStrength()
        {
            return strength;
        }

        int getIntellect()
        {
            return intellect;
        }

        int getDexterity()
        {
            return dexterity;
        }

        int getCharisma()
        {
            return charisma;
        }     

        void setCurrentHP(int hp)
        {
            currentHP = hp;
        }

        void setMaxHP(int hp)
        {
            maxHP = hp;
        }   

    private: 

        // Base values - These can range from 0 to 100 theoretically 
        int currentHP = 100, maxHP = 100, strength = 10, intellect = 10, dexterity = 10, charisma = 50;    
};

// Enemy class
class Enemy
{
    public: 

        int getCurrentHP()
        {
            return currentHP; 
        }

        int getMaxHP()
        {
            return maxHP;
        }

        // Determines how hard the enemies hit 
        int getStrength()
        {
            return strength;
        }

        void setCurrentHP(int hp)
        {
            currentHP = hp;
        }

    private: 

        // Defining a max hp lets us add enemy heals more easily (the proteus can repair itself or smth)
        int currentHP, maxHP, strength; 
    
};

// Proteus bot class
class ProteusBot : Enemy
{
    public: 

    private: 

        // This is one of the only values that changes across enemy
        int maxHP = 100;
    
};

// TA class
class TA : Enemy
{
    public: 

    private: 

        int currentHP, maxHP = 200;
    
};

// Clingan class 
class MrClingan : Enemy
{
    public: 

    private: 

        int currentHP, maxHP = 500;
    
};

/* Function Protypes */

// Must be declared after class declarations
void playGame(); 
int battle(Player* player, Enemy* enemy);
void displayRules();
void displayCredits();
void displayStats();

// Game statistics, displayed when the user hits "STATS" on the main menu
// Todo - Figure out if we need any more statistics 
int gamesPlayed, gamesWon, deaths, monstersDefeated; 

int main(void)
{
    bool exitVar = false;
    int userInput;

    // Pure c++ replacement for below code
    while (!exitVar)
    {
        cout << "(1) Play Game" << endl;
        cout << "(2) Display Stats" << endl;
        cout << "(3) Display Rules" << endl;
        cout << "(4) Display Credits" << endl;
        cout << "(5) Quit" << endl; 

        cout << "Your Choice: ";
        cin >> userInput;

        // Spacing
        cout << endl << endl;

        switch (userInput)
        {
            // Play game 
            case 1:
            {
                playGame();
                break;
            }

            // Display Stats
            case 2:
            {
                displayStats();
                break;
            }

            // Display Rules
            case 3:
            {
                displayRules();
                break;
            }

            // Display Credits
            case 4:
            {
                displayCredits();
                break;
            }

            // Quit the game 
            case 5:
            {
                cout << "Hope you had fun! Exiting game." << endl;
                exitVar = true;
                break;
            }
        }
    }

    // If it made it here, no errors happened, so a normal exit code 
    return 0;
}

// Majority of the code - Run whevever the player hits "play game" 
void playGame()
{
    // Todo - Figure out how to only proceed in the story if the battle function returns true, and
    // Todo - Rewind back a little bit if not 

    // Write all the content and actual story stuff here 
    cout << "Example Story Intro" << endl;

    // Initializing the player object 
    Player player; 

    cout << "Starting test fight" << endl;

    // Initializing a Mr. Clingan object (a sentence I never anticipated I'd type) 
    Enemy enemy;

    int battleResult;
    bool wonBattle = false;

    while (!wonBattle)
    {
        battleResult = battle(&player, &enemy);

        switch(battleResult)
        {
            case 0:
            {
                cout << "You won the battle." << endl;
                wonBattle = true;
                break;
            }

            case 1:
            {
                cout << "You lost the battle." << endl;
                break;
            }

            case 2:
            {
                cout << "You ran from the battle." << endl;
                break;
            }
        }  
    }

    cout << "Debug: You won the battle!" << endl;
    
}

/* Using return codes because it's a very customizable way of basically doing a switch statement dependent on if you won the battle. 

    Return Codes:
    0 = Player Won 
    1 = Player Lost
    2 = Player Successfully Ran 
*/
int battle(Player *player, Enemy *enemy)
{
    // This variable gets changed whenever a condition to exit gets tripped 
    bool canExitLoop = false, userRan = false;
    int userChoice, damage; 

    // Loops until somebody dies or the user successfully ran from the battle 
    while (!canExitLoop && !userRan)
    {
        /* Player Action */
        cout << "Options: " << endl;
        cout << "(1) Attack - Weapon" << endl;
        cout << "(2) Attack - Code Injection" << endl;
        cout << "(3) Attempt to Flee" << endl;

        cin >> userChoice;

        switch(userChoice)
        {
            // Normal Attack
            case 1:
            {
                // Determining damage based on player strength 
                damage = player -> getStrength();

                // Actually subtracting that from the monster 
                enemy -> setCurrentHP(enemy -> getCurrentHP() - damage); 
                
                cout << "You did " << damage << " damage to the monster" << endl;
                // Breaking out of switch statement
                break;
            }

            // Code Injection Attack
            case 2:
            {
                // Determining damage based on player intellect
                damage = player -> getIntellect();

                // Actually subtracting that from the monster 
                enemy -> setCurrentHP(enemy -> getCurrentHP() - damage);

                cout << "You did " << damage << " damage to the monster." << endl;

                // Breaking out of switch statement
                break;
            }

            // Flee 
            case 3:
            {
                // Determining if the player successfully fled 
                // This is set to zero for debug purposes
                if (player -> getDexterity() > 0)
                {
                    cout << "You successfully ran from the monster." << endl;
                    userRan = true;
                }

                else
                {
                    cout << "Your attempt to escape failed." << endl;
                }
                
                // Breaking out of switch statement
                break;
            }
        }

        // Checking if the monster is dead 
        if (enemy -> getCurrentHP() <= 0)
        {
            canExitLoop = true;
        }

        /* Monster Action */

        // Have to make sure the monster isn't dead or the player ran, in which case battle is over and these calculations don't need to happen 
        if (!canExitLoop && !userRan)
        {
            // Same procedure as above, except w/o the choice and switch statement 
            damage = enemy -> getStrength();
            player -> setCurrentHP(player -> getCurrentHP() - damage);
        }

        // checking if the player is dead
        if (player -> getCurrentHP() <= 0)
        {
            canExitLoop = true;
        }
    }

    // Computing the result of the battle
    if (userRan)
    {
        cout << "You ran successfully." << endl;

    }
}

// Displays the rules of the game - Run when the user hits "Rules"
void displayRules()
{
    cout << "The rules are simple - SURVIVE." << endl;

    cout << "There are save points after every encounter and at several other points. If you die, you will restart from the most recent point." << endl;
    cout << "Every monster you kill levels you up, so you are stronger and harder to kill." << endl;
    cout << "Enjoy!" << endl;

    // Spacing
    cout << endl;
}

// Displays credits - Run when the user hits "credits"
void displayCredits()
{
    cout << "Credits: " << endl;

    cout << "Game by Anden Acitelli and Sri Uppalapati." << endl;
    cout << "Shoutout to Clingan and his teaching staff for being subjects of this game, whether or not they knew they were." << endl;
    
    // Spacing
    cout << endl;
}

// Displays Stats  - Run when the user hits "stats"
// Will probably display stuff like number of times won, deaths, enemies killed, stuff like that idk 
void displayStats()
{
    cout << "Game Statistics: " << endl;

    cout << "Games Played: " << gamesPlayed << endl;
    cout << "Games Won: " << gamesWon << endl;
    cout << "Monsters Defeated: " << monstersDefeated << endl;
    cout << "Deaths: " << deaths << endl;

    // Spacing 
    cout << endl;
}

