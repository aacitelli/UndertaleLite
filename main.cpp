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

