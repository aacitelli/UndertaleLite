/* 

    This is the version of the code that works
    with the proteus. Odds are, this will lag
    behind the other cpp file most of the time, 
    because it's easier to write the other file
    whenever you don't have access to a proteus.

*/

// Including requisite libraries 
// These are just commented out b/c this is a pure c++ version 
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include <iostream>

using namespace std;

// Imports for the console version
// Todo - Remove these when porting to proteus 

// Defining Constants 
// These ones just cut down on code we have to write 
#define BLACK FEHLCD::Black
#define WHITE FEHLCD::White

// Game Statistics 
int gamesPlayed, gamesWon, monstersDefeated, deaths, highestLevel;

// The player class - What the user plays as 
class Player
{
    public: 

        /* There is zero chance that what I'm about to do is best practice, but here we go nonetheless */ 

        /* Retrieval Methods */
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

        /* Assignment Methods */
        void setCurrentHP(int hp)
        {
            currentHP = hp;
        }

        void setMaxHP(int hp)
        {
            maxHP = hp;
        }   

        int setStrength(int parameter)
        {
            strength = parameter;
        }  

        int setIntellect(int parameter)
        {
            intellect = parameter;
        }

        void heal()
        {
            if (maxHP - currentHP < 30)
            {
                currentHP = maxHP;
            }

            else
            {
                currentHP += 30;
            }
        }

        /* Save Point Methods */       

        // Backs up values so they can be restored to upon death 
        void setSavePointValues()
        {
            spMaxHP = maxHP;
            spStrength = strength;
            spIntellect = intellect;
        }

        void restoreSavePointValues()
        {
            currentHP = maxHP;
            maxHP = spMaxHP;
            strength = spStrength;
            intellect = spIntellect;
        }

        void levelUp()
        {
            cout << "Leveled Up." << endl;

            // Turns out with how I did scaling making current hp go up every level is a little op and means you literally can't die even if you try 
            maxHP += 10;
            strength += 2;
            intellect += 2;
            currentLevel++;

            // Stats tracking 
            if (currentLevel > highestLevel)
            {
                highestLevel = currentLevel;
            }
        }        

    private: 

        // Base values - These can range from 0 to 100 theoretically 
        int currentHP = 300, maxHP = 300, strength = 10, intellect = 10;
        int currentLevel = 1;    
        
        // Save point values
        int spMaxHP = 300, spStrength = 10, spIntellect = 10;
};

// Enemy class
class Enemy
{
    public: 

        /* Retrieval Functions */

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

        /* Assignment Functions */

        void setCurrentHP(int hp)
        {
            currentHP = hp;
        }

        void setMaxHP(int hp)
        {
            maxHP = hp;
        }                

    private: 

        int strength = 50, currentHP, maxHP;
    
};

// Proteus bot class
class ProteusBot : public Enemy
{
    public: 

        // Declaring the constructor
        ProteusBot();

    private:   
};

// TA class
class TA : public Enemy
{
    public: 

        // Declaring the constructor
        TA();

    private:     
};

// Clingan class 
class MrClingan : public Enemy
{
    public: 

        // Declaring the constructor 
        MrClingan();

    private: 
    
};

// Proteus bot constructor 
ProteusBot::ProteusBot()
{
    setCurrentHP(100);
    setMaxHP(100);
}

// TA constructor
TA::TA()
{
    setCurrentHP(250);
    setMaxHP(250);
}

// Mr Clingan's very own constructor
MrClingan::MrClingan()
{
    setCurrentHP(400);
    setMaxHP(400);
}

// Function Prototypes
void drawMenu(FEHIcon::Icon *buttons, char labels[][20]);
bool playGame(); 
int battle(Player* player, Enemy* enemy, const char *name);
void displayRules();
void displayCredits();
void displayStats();

int main(void)
{
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);

    // Declaring Icon Array
    FEHIcon::Icon menu[4];

    // Defining Menu Text Labels
    char menu_labels[4][20] = {"START","RULES","CREDITS","STATS"};

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
            }

            if(menu[1].Pressed(x,y,0))
            {
                menu[1].WhilePressed(x,y);
                LCD.Clear(BLACK);
                LCD.WriteLine("RULES");

                // Calls the rules method 
            }

            if(menu[2].Pressed(x,y,0))
            {
                menu[2].WhilePressed(x,y);
                LCD.Clear(BLACK);
                LCD.WriteLine("CREDITS");

                // Calls the credits method 
            }

            if(menu[3].Pressed(x,y,0))
            {
                menu[3].WhilePressed(x,y); 
                LCD.Clear(BLACK);
                LCD.WriteLine("STATS");

                // Calls the stats method 
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
    // cout << "Credits: " << endl;
    LCD.WriteLine("Credits: ");

    // cout << "Game by Anden Acitelli and Sri Uppalapati." << endl;
    // cout << "Shoutout to Clingan and his teaching staff for being subjects of this game, whether or not they knew they were." << endl;
    LCD.WriteLine("Game by Anden Acitelli and Sri Uppalapati.");
    LCD.WriteLine("Shoutout to Clingan and his teaching staff for being subjects of this game, whether or not they knew they were.");
    
    // Spacing
    // cout << endl;
    LCD.WriteLine("");
}

// Displays Stats  - Run when the user hits "stats"
// Will probably display stuff like number of times won, deaths, enemies killed, stuff like that idk 
void displayStats()
{
    // cout << "Game Statistics: " << endl;
    LCD.WriteLine("Game Statistics: ");

    /*
    cout << "Games Played: " << gamesPlayed << endl;
    cout << "Games Won: " << gamesWon << endl;
    cout << "Monsters Defeated: " << monstersDefeated << endl;
    cout << "Deaths: " << deaths << endl;
    cout << "Highest Level: " << highestLevel << endl;
    */

    // Aaaaand the proteus got annoying. 
    // LCD.Write("") serves as a newline character.
    LCD.Write("Games Played: "); LCD.Write(gamesPlayed); LCD.WriteLine("");
    LCD.Write("Games Won: "); LCD.Write(gamesWon); LCD.WriteLine("");
    LCD.Write("Enemies Defeated: "); LCD.Write(monstersDefeated); LCD.WriteLine("");
    LCD.Write("Deaths: "); LCD.Write(deaths); LCD.WriteLine();
    LCD.Write("Highest Level: "); LCD.Write(highestLevel); LCD.WriteLine();

    // Spacing 
    // cout << endl;
    LCD.WriteLine();
}

