/* 

    NOTE - EVERYTHING I'M DOING HERE
    IS PURE C++. THIS WONT WORK WITH
    THE PROTEUS. THIS IS BASICALLY
    A CONSOLE VERSION OF THE PROTEUS
    PROGRAM. 

*/

// Including requisite libraries 
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

// Imports for the console version
// Todo - Remove these when porting to proteus 

// Defining Constants 
// These ones just cut down on code we have to write 
#define BLACK FEHLCD::Black
#define WHITE FEHLCD::White

// Function Prototypes
void drawMenu(FEHIcon::Icon *buttons, char labels[][20]);
void playGame();
void displayRules();
void displayCredits();
void displayStats();

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

        int getStrength()
        {
            return strength;
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
    
};

// TA class
class TA : Enemy
{
    public: 

    private: 
    
};

// Clingan class 
class MrClingan : Enemy
{
    public: 

    private: 
    
};

// Game statistics, displayed when the user hits "STATS" on the main menu
// Todo - Figure out if we need any more statistics 
int gamesPlayed, gamesWon, deaths, monstersDefeated; 

int main(void)
{
    /*Clear screen, and set screen for writing*/
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);

    // Defining Intro Screen Variables 
    int touchCount;
    float x,y;
    bool run = true, press = true;

    // Declaring Icon Array
    FEHIcon::Icon menu[4];

    // Defining Menu Text Labels
    char menu_labels[4][20] = {"START","RULES","CREDITS","STATS"};

    // Draws the menu screen 
    while (run)
    {
        drawMenu(menu, menu_labels);

        if(LCD.Touch(&x,&y))
        {
            if(menu[0].Pressed(x,y,0))
            {
                menu[1].WhilePressed(x,y);
                LCD.Clear(BLACK);
                LCD.WriteLine("PLAYING");

                // Calls the game method 
                playGame();
            }

            if(menu[1].Pressed(x,y,0))
            {
                menu[1].WhilePressed(x,y);
                LCD.Clear(BLACK);
                LCD.WriteLine("RULES");

                // Calls the rules method 
                displayRules();
            }

            if(menu[2].Pressed(x,y,0))
            {
                menu[2].WhilePressed(x,y);
                LCD.Clear(BLACK);
                LCD.WriteLine("CREDITS");

                // Calls the credits method 
                displayCredits();
            }

            if(menu[3].Pressed(x,y,0))
            {
                menu[3].WhilePressed(x,y);
                LCD.Clear(BLACK);
                LCD.WriteLine("STATS");

                // Calls the stats method 
                displayStats();
            }
        }
    }
}

void drawMenu(FEHIcon::Icon *buttons, char labels[][20])
{
    // draw the menu in a 2 by 2 array with top and bottom
    // margins of 10 and left and right margins of 5
    // with the menu labels, gold borders, and green text
    FEHIcon::DrawIconArray(buttons, 2, 2, 10, 10, 5, 5, labels, GOLD, GREEN);
}

// Majority of the code - Run whevever the player hits "play game" 
void playGame()
{
    // Todo - Figure out how to only proceed in the story if the battle function returns true, and
    // Todo - Rewind back a little bit if not 

    // Write all the content and actual story stuff here 
        
}

// Called whenever the user initiates battle with a TA or proteus 
// Todo - Maybe tweak the second parameter b/c it might not always be an enemy idk 
// ? Should this be passing by address? idk if it'll save the value 
// ? What should this return? Maybe a boolean? 
bool battle(Player player, Enemy enemy)
{
    while (player.currentHP > 0 && enemy.currentHP > 0)
    {
        /* The player's turn */
        int userChoice;
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

                    // Todo - Code here 

                    break;
                }

                // Attack w/ code injection
                case 2:
                {
                    isValidInput = true;

                    // Todo - Code here 

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
            
        }

        // If the fight is over
        else
        {
            break;
        }

    }

    if (player.currentHP <= 0)
    {
        cout << "You lost the battle. Restarting from previous savepoint." << endl;
        return false;
    }

    else if (enemy.currentHP <= 0)
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

