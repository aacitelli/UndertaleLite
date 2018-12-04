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

#include <time.h> // Needed for seeding randomization 
#include <stdlib.h> // Needed for randomization 

using namespace std;

// Imports for the console version
// Todo - Remove these when porting to proteus 

// Defining Constants 
// These ones just cut down on code we have to write 
#define BLACK FEHLCD::Black
#define WHITE FEHLCD::White
#define SLEEP_TIME 5.0 // Time to sleep in between lines

/* TODO IN CLASS

    Make sure everything works, bug-free, b/c I did most of this based off of memory and I could have screwed some small stuff up 

*/

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

        player();   

    private: 

        // Base values - These can range from 0 to 100 theoretically 
        int currentHP, maxHP, strength, intellect;
        int currentLevel;    
        
        // Save point values
        int spMaxHP, spStrength, spIntellect;
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

        void setStrength(int parameter)
        {
            strength = parameter;
        }            

    private: 

        int strength, currentHP, maxHP;
    
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

// Player constructor
Player::Player()
{
    // Base values - These can range from 0 to 100 theoretically 
    currentHP = 300, maxHP = 300, strength = 10, intellect = 10;
    currentLevel = 1;    
    
    // Save point values
    spMaxHP = 300, spStrength = 10, spIntellect = 10;
}

// Generic enemy constructor 
Enemy::Enemy()
{
    strength = 50;
}

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
    char menu_labels[4][20] = {"START", "RULES", "CREDITS", "STATS"};

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
bool playGame()
{
    gamesPlayed++;
    int battleResult, userInput; 

    // Initializing the player
    Player player;

    /* Exposition */
    LCD.WriteLine("Tonight was the night that it would all change.");
    Sleep(SLEEP_TIME); // Sleep for 1k milliseconds 

    LCD.WriteLine("It all started that fateful night, many years ago. The FEH program had existed peacefully, as it had for years, serving as a haven for exploration and learning.");
    Sleep(SLEEP_TIME); // Sleep for 1k milliseconds

    LCD.WriteLine("And then that peace had been torn to shreds by Clingan and his conspirators that fateful day. Clingan and his teaching staff had risen up, and now held control of the FEH program. They had stormed Hitchcock at night, and held the rest of the teaching staff captive.");
    Sleep(SLEEP_TIME); // Sleep for specified time in ms

    LCD.WriteLine("Tonight was the night that we, the Anti-Clingan Freedom Front (ACFF), would take back Hitchcock.") LCD.WriteLine("");
    Sleep(SLEEP_TIME); // Sleep for specified time in ms
    
    LCD.WriteLine("You pass underneath the Tom W. Davis Clocktower. Do you pray for guidance?");

    LCD.WriteLine("(Touch Left Side) Yes");
    LCD.WriteLine("(Touch Right Side) No");
    LCD.Write("Your Choice:");

    bool flag = false; // Input validation GOD 
    float x, y;

    while (!Touch(&x, &y) && !flag) 
    {
        if (Touch(&x, &y))
        {
            // Left side of screen 
            if (x >= 0 && x <= 150)
            {
                LCD.WriteLine("Tom W. Davis bestows his wisdom upon you.");
                LCD.WriteLine("Strength and Intellect Increased by 5. Current and Max HP increased by 10.");

                player.setStrength(player.getStrength() + 5);
                player.setIntellect(player.getIntellect() + 5);

                player.setMaxHP(player.getMaxHP() + 10);
                player.setCurrentHP(player.getCurrentHP() + 10);

                flag = true;
            }

            // Right side of screen 
            else 
            {
                LCD.WriteLine("You are a deplorable human being if you choose to not worship the clocktower.");
                LCD.WriteLine("Sense of time decreased by 5. You now have no clue what time it is.");

                flag = true;
            }
        }       
    }    

    // Choice 2 - Determines Stats 
    LCD.WriteLine("You stop for a bite to eat right before the righteous crusade.");
    LCD.WriteLine("Which station at Scott do you stop?");

    LCD.WriteLine("Options: ") ;
    LCD.WriteLine("(Tap Left Side) Mongolian (Strength Up)");
    LCD.WriteLine("(Tap Right Side) Breakfast Station (Intellect Up)");              
    
    LCD.WriteLine("Your Choice: ");

    // Waiting for input
    flag = false;
    while (!Touch(&x, &y) && !flag)
    {
        if (Touch(&x, &y))
        {     
            if (x >= 0 && x <= 150)
            {
                LCD.WriteLine("Waiting for Wok...");

                // Todo - Make this a longer wait time than the rest 

                LCD.WriteLine("You had a hearty Mongolian meal. Strength increased by 5.");
                
                player.setStrength(player.getStrength() + 5);
                flag = true;
            }

            else 
            {
                LCD.WriteLine("You had a hearty breakfast. Intellect increased by 5.");

                player.setIntellect(player.getIntellect() + 5);

                flag = true;
                break;
            }    
        }
    }       
    
    // This loop dictates whether or not they are done fighting proteii 
    bool doneFightingRobots = false;
    while (!doneFightingRobots)
    {
        player.setSavePointValues();

        LCD.WriteLine("Fight a proteus robot to gain more XP and raise your stats?");
        LCD.WriteLine("(Touch Left Side) Yes");
        LCD.WriteLine("(Touch Right Side) No");

        LCD.WriteLine("Your Choice: ");

        // Waiting for input 
        flag = false;
        while (Touch(&x, *y) && !flag)
        {
            if (&Touch(&x, &y))
            {
                // Left side of screen 
                if (x >= 0 && x <= 150)
                {
                    ProteusBot enemy;

                    // C++ doesn't like when names aren't constants, but C does, for whatever reason, so this is the workaround 
                    char const *enemyName = "Proteus Bot";
                    battleResult = battle(&player, &enemy, enemyName);

                    switch (battleResult)
                    {
                        case 1:
                        {
                            player.restoreSavePointValues();
                        }
                    }
                }

                // Right side of screen 
                else
                {
                    flag = true;                    
                }
            }            
        }       
    }
    
    
    /* Begin TA Fights */
    flag = false;
    while (!flag)
    {
        player.setSavePointValues();

        flag2 = false;
        while (!flag2)
        {
            LCD.WriteLine("Jane Fight: ");

            TA enemy;
            const char *enemyName = "Jane";
            battleResult = battle(&player, &enemy, enemyName);

            switch (battleResult)
            {
                // Player win 
                case 0:
                {
                    flag2 = true;
                    break;
                }

                // Player loss 
                case 1:
                {
                    player.restoreSavePointValues(); // Resets values and the player faces jane again 
                    break;
                }

                // Debug state 
                default:
                {
                    LCD.WriteLine("Something screwed up in Jane fight.");

                    break;
                }
            }
            
        }

        player.setSavePointValues();

        flag2 = false;
        while (!flag2)
        {
            LCD.WriteLine("Aidan Fight: ");

            TA enemy;
            const char *enemyName = "Aidan";
            battleResult = battle(&player, &enemy, enemyName);

            switch (battleResult)
            {
                // Player win 
                case 0:
                {
                    flag2 = true;
                    break;
                }

                // Player loss 
                case 1:
                {
                    player.restoreSavePointValues();
                    break;
                }

                // Debug state 
                default:
                {
                    LCD.WriteLine("Something screwed up in Aidan fight.");

                    break;
                }
            }            
        }

        player.setSavePointValues();

        flag2 = false;
        while (!flag2)
        { 
            LCD.WriteLine("Barley Fight: ");

            TA enemy;
            const char *enemyName = "Barley";
            battleResult = battle(&player, &enemy, enemyName);

            switch (battleResult)
            {
                // Player win 
                case 0:
                {
                    flag2 = true;
                    break;
                }

                // Player loss 
                case 1:
                {
                    player.restoreSavePointValues();
                    break;
                }

                // Debug state 
                default:
                {
                    LCD.WriteLine("Something screwed up in Barley fight.");
                    break;
                }
            }              
        }

        player.setSavePointValues();

        flag2 = false;
        while (!flag2)
        {    
            LCD.WriteLine("Erma Fight: ");

            TA enemy;
            const char *enemyName = "Erma";
            battleResult = battle(&player, &enemy, enemyName);

            switch (battleResult)
            {
                // Player win 
                case 0:
                {
                    flag2 = true;
                    flag = true;
                    break;
                }

                // Player loss 
                case 1:
                {
                    player.restoreSavePointValues();
                    break;
                }

                // Debug state 
                default:
                {
                    LCD.WriteLine("Something screwed up in Erma fight.");
                    break;
                }
            }           
        }
    }

    
    flag = false;
    while (!flag)
    {
        LCD.WriteLine("Clingan Fight: ");

        MrClingan enemy;
        battleResult = battle(&player, &enemy, "Mr. Clingan");
        
        switch (battleResult)
        {
            case 0:
            {
                flag = true;
                break;
            }

            case 1:
            {
                break;
            }

            default: 
            {
                LCD.WriteLine("Yo, Mr. Clingan control loop is screwed up");
            }
        }
    }

    LCD.WriteLine("Congratulations! You Win!");
    gamesWon++;
}

/* \


    Using return codes because it's a very customizable way of basically 
    doing a switch statement dependent on the result of a method.

    Return Codes Key:
    0 = Player Won 
    1 = Player Lost

    This sign convention is literally the opposite of what's used in programming
    pretty much everywhere, but it's too late to go back now. 

*/
int battle(Player *player, Enemy *enemy, const char *name)
{gh
    // This variable gets changed whenever a condition to exit gets tripped 
    bool canExitLoop = false;
    int userChoice, playerDamage, monsterDamage, playerHeal;

    bool flag, isFirstTurn = true;

    // I know what I'm doing, trust me 
    while (true)
    {     
        // Outputting results of last turn
        if (!isFirstTurn)
        {
            LCD.Write("You did "); LCD.Write(playerDamage); LCD.WriteLine(" damage that turn");
            LCD.Write("You did "); LCD.Write(playerHeal); LCD.WriteLine(" healing that turn.");
            LCD.Write("The enemy did "); LCD.Write(monsterDamage); LCD.WriteLine(" damage that turn.");
        }

        else
        {
            isFirstTurn = false;
        }

        // Displaying Health for both players
        LCD.Write("Current Enemy: "); LCD.Write(name); LCD.WriteLine("");
        LCD.Write("Player Health: "); LCD.Write(player -> getCurrentHP()); LCD.Write(" | Enemy Health: "); LCD.Write(enemy -> getCurrentHP()); LCD.WriteLine(""); LCD.WriteLine(""); // This was a fun line and I'm only putting this comment inline to make it even longer 

        /* Player Action */      
        LCD.WriteLine("Options: ");
        LCD.WriteLine("(1) Attack - Weapon");
        LCD.WriteLine("(2) Attack - Code Injection");
        LCD.WriteLine("(3) Heal");
        LCD.Write("Your Choice: ");

        // Todo - Figure out how we're going to do input on the proteus 
        cin >> userChoice;          

        /* User's turn */
        flag = false;
        while (!flag)
        {   
            /* The user's turn */
            switch(userChoice)
            {
                // Normal Attack
                case 1:
                {
                    // Determining damage based on player strength 
                    playerDamage = (rand() % 10 + 1) * player -> getStrength() / 5;
                    playerHeal = 0;

                    // Actually subtracting that from the monster 
                    enemy -> setCurrentHP(enemy -> getCurrentHP() - playerDamage); 

                    // Breaking out of switch statement
                    flag = true;
                    break;
                }

                // Code Injection Attack
                case 2:
                {
                    // Determining damage based on player intellect
                    playerDamage = (rand() % 10 + 1) * player -> getIntellect() / 5;
                    playerHeal = 0;

                    // Actually subtracting that from the monster 
                    enemy -> setCurrentHP(enemy -> getCurrentHP() - playerDamage);

                    // Breaking out of switch statement
                    flag = true;
                    break;
                }

                // Healing 
                case 3:
                {                    
                    playerHeal = 30;
                    playerDamage = 0;

                    player -> heal();

                    flag = true;
                    break;
                }
                
                // Input validation 
                default:
                {
                    LCD.WriteLine("Illegitimate Input");
                }
            }            
        }       

        // Checking if the monster is dead 
        if (enemy -> getCurrentHP() <= 0)
        {
            LCD.WriteLine("You KilLCD The Enemy! Level Up!");

            player -> levelUp();
            monstersDefeated++;
            return 0;
            break; // Monster's dead, don't need to continue the battle any more 
        }

        /* Monster's turn */
        monsterDamage = (rand() % 10 + 1) * enemy -> getStrength() / 12;
        player -> setCurrentHP(player -> getCurrentHP() - monsterDamage);
     
        LCD.Write("The monster did "); LCD.Write(monsterDamage); LCD.WriteLine(" damage to you.");

        // Checking if the player is dead
        if (player -> getCurrentHP() <= 0)
        {
            LCD.WriteLine("The enemy kilLCD you. Starting from most recent save point.");

            deaths++;
            return 1;
            break; // You're dead, don't need to continue the battle any more
        }          
    }
}

// Displays the rules of the game - Run when the user hits "Rules"
void displayRules()
{
    LCD.WriteLine("The rules are simple - SURVIVE, AND GET VENGEANCE.");

    LCD.WriteLine("There are save points after every encounter and at several other points. If you die, you will restart from the most recent point.");
    LCD.WriteLine("Every monster you kill levels you up, so you are stronger and harder to kill.");
    LCD.WriteLine("Enjoy!");

    // Spacing
    LCD.WriteLine("");
}

// Displays credits - Run when the user hits "credits"
void displayCredits()
{
    LCD.WriteLine("Credits: ");

    LCD.WriteLine("Game by Anden Acitelli and Sri Uppalapati.");
    LCD.WriteLine("Shoutout to Clingan and his teaching staff for being subjects of this game, whether or not they knew they were.");
    
    // Spacing
    LCD.WriteLine("");
}

// Displays Stats  - Run when the user hits "stats"
// Will probably display stuff like number of times won, deaths, enemies kilLCD, stuff like that idk 
void displayStats()
{
    LCD.WriteLine("Game Statistics: ");

    // Aaaaand the proteus got annoying. 
    // LCD.Write("") serves as a newline character.
    LCD.Write("Games Played: "); LCD.Write(gamesPlayed); LCD.WriteLine("");
    LCD.Write("Games Won: "); LCD.Write(gamesWon); LCD.WriteLine("");
    LCD.Write("Enemies Defeated: "); LCD.Write(monstersDefeated); LCD.WriteLine("");
    LCD.Write("Deaths: "); LCD.Write(deaths); LCD.WriteLine();
    LCD.Write("Highest Level: "); LCD.Write(highestLevel); LCD.WriteLine();

    // Spacing 
    LCD.WriteLine();
}

