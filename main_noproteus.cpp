/* 

    NOTE - EVERYTHING I'M DOING HERE
    IS PURE C++. THIS WONT WORK WITH
    THE PROTEUS. THIS IS BASICALLY
    A CONSOLE VERSION OF THE PROTEUS
    PROGRAM. 

*/

#include <iostream>

using namespace std;

// The player class - What the user plays as 
class Player
{
    public: 

        // This is apparently best practice so here we go 
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

        void setMaxHP(int hp)
        {
            maxHP = hp;
        }   

    private: 

        int currentHP, maxHP, strength, intellect, dexterity, charisma;    
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

        void setHP(int hp)
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
void playGame(Player* player, Enemy* enemy); 
void displayRules();
void displayCredits();
void displayStats();

// Game statistics, displayed when the user hits "STATS" on the main menu
// Todo - Figure out if we need any more statistics 
int gamesPlayed, gamesWon, deaths, monstersDefeated; 

int main(void)
{
    // Defining Intro Screen Variables 
    int touchCount;
    float x,y;
    bool run = true, press = true;
    // Defining Menu Text Labels
    char menu_labels[4][20] = {"START","RULES","CREDITS","STATS"};

    bool exitVar = false;

    // Pure c++ replacement for below code
    while (!exitVar)
    {
        cout << "(1) Play Game" << endl;
        cout << "(2) Display Stats" << endl;
        cout << "(3) Display Rules" << endl;
        cout << "(4) Display Credits" << endl;
    }
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

    cout << "Starting tests fight" << endl;

    // Initializing a Mr. Clingan object (a sentence I never anticipated I'd type) 
    MrClingan clinganEnemy;

    if (battle(&player, &clinganEnemy))
    {
        cout << "You won the battle." << endl;
    }

    else 
    {
        cout << "You lost the battle." << endl;
    }        
}

// Called whenever the user initiates battle with a TA or proteus 
// Todo - Maybe tweak the second parameter b/c it might not always be an enemy idk 
// ? Should this be passing by address? idk if it'll save the value 
// ? What should this return? Maybe a boolean? 
bool battle(Player *player, Enemy *enemy)
{
    /* Note - both player and enemy are pointers in order for their values to persist outside of the individual value - 
        This means their values have to be accessed w/ arrow syntax (->) */

    // Looping until someone's health is less than zero 
    while (player -> currentHP > 0 && enemy -> currentHP > 0)
    {
        /* The player's turn */
        int userChoice, damage;
        bool isValidInput = false, PlayerRan = false; 

        while (!isValidInput && !playerRan)
        {
            cout << "Choose Action: " << endl;
            cout << "(1) Attack (Weapon)" << endl;

            // Todo - I'm trying to say hacking here but code injection sounds cooler and I like extra brownie points 
            cout << "(2) Attack (Code Injection)" << endl; 
            cout << "(3) Run Away" << endl;

            cin >> userChoice;

            switch (userChoice)
            {
                // Attack w/ weapon 
                case 1:
                {
                    isValidInput = true;

                    // Todo - Implement slight randomness 
                    damage = player -> getStrength() * 100;
                    enemy -> currentHP -= damage;            

                    break;
                }

                // Attack w/ code injection
                case 2:
                {
                    isValidInput = true;

                    // Todo - Implement slight randomness 
                    damage = player -> getIntellect() * 100;
                    enemy -> currentHP -= damage;

                    break;
                }

                // Attempt to flee 
                case 3:
                {
                    isValidInput = true;

                    // Todo - Make this decide based on charisma - Involves a random variable probably
                    // Your chance of being able to run is probably just your charisma. Ex. 80 Charisma = 80% chance of being able to run 
                    if (/* Charisma Check or Other Conditional */ )
                    {
                        // Escape the function 
                        playerRan = true;
                    }

                    // In this case, the user fails to run away and they still get hit by the enemy 
                    else 
                    {
                        cout << "Your attempt to run away failed." << endl;
                    }

                    break;
                }

                default:
                {
                    cout << "Input not understood. Please input a valid number." << endl;
                    break;
                }
            }
        }        

        /* The enemy's turn */
        // Checks the HP to make sure that you're never in a place where both the player and enemy die at the same time.
        if (enemy.currentHP > 0)
        {
            // My code editor says damage doesn't exist here but I really don't trust it tbh 
            damage = enemy -> getStrength() * 100;
            player -> currentHP -= damage;           
        }

        // If the fight is over
        else
        {
            break;
        }

    }

    if (player -> currentHP <= 0)
    {
        cout << "You lost the battle. Restarting from previous savepoint." << endl;
        return false;
    }

    else if (enemy -> currentHP <= 0)
    {
        cout << "You won the battle." << endl;
        return true;
    }

    else if (playerRan)
    {
        cout << "You successfully ran from the battle." << endl;
        return false; // ? What should get returned here? See runGame() function or w/e I called it 
    }

    // Debug 
    else
    {
        cout << "Something went wrong with the battle method in the \"who died\" logic." << endl;
        return false;
    }
}

// Displays the rules of the game - Run when the user hits "Rules"
void displayRules()
{
    cout << "The rules are simple - SURVIVE." << endl;

    cout << "There are save points after every encounter and at several other points. If you die, you will restart from the most recent point." << endl;
    cout << "Every monster you kill levels you up, so you are stronger and harder to kill." < endl;
    cout << "Enjoy!" << endl;
}

// Displays credits - Run when the user hits "credits"
void displayCredits()
{
    cout << "Credits: " << endl;

    cout << "Game by Anden Acitelli and Sri Uppalapati." << endl;
    cout << "Shoutout to Clingan and his teaching staff for being subjects of this game, whether or not they knew they were." << endl;
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

}

