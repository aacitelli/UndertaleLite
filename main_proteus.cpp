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

#include <time.h> // Needed for randomization 

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
    // cout << "Tonight was the night that it would all change." << endl;
    LED.WriteLine("Tonight was the night that it would all change.");

    // cout << "It all started that fateful night, many years ago. The FEH program had "; 
    // cout << "existed peacefully, as it had for years, serving as a haven for exploration ";
    // cout << "and learning." << endl;
    LED.WriteLine("It all started that fateful night, many years ago. The FEH program had existed peacefully, as it had for years, serving as a haven for exploration and learning.");
    LED.WriteLine("");
    LED.WriteLine("");

    // cout << "And then that peace had been torn to shreds by Clingan and his conspirators that ";
    // cout << "fateful day. Clingan and his teaching staff had risen up, and now held control of ";
    // cout << "the FEH program. They had stormed Hitchcock at night, and held the rest of the ";
    // cout << "teaching staff captive." << endl;
    LED.WriteLine("And then that peace had been torn to shreds by Clingan and his conspirators that fateful day. Clingan and his teaching staff had risen up, and now held control of the FEH program. They had stormed Hitchcock at night, and held the rest of the teaching staff captive.");

    // cout << "Tonight was the night that we, the Anti-Clingan Freedom Front (ACFF), would take ";
    // cout << "back Hitchcock." << endl << endl;
    LED.WriteLine("Tonight was the night that we, the Anti-Clingan Freedom Front (ACFF), would take back Hitchcock.") LED.WriteLine("");
    
    // cout << "You pass underneath the Tom W. Davis Clocktower. Do you pray for guidance?" << endl;
    LED.WriteLine("You pass underneath the Tom W. Davis Clocktower. Do you pray for guidance?");

    // cout << "(1) Yes" << endl;
    // cout << "(2) No" << endl;
    // cout << "Your Choice: ";
    LED.WriteLine("(1) Yes");
    LED.WriteLine("(2) No");
    LED.Write("Your Choice:");

    cin >> userInput;

    bool flag = false; // Input validation GOD 
    while (!flag)
    {
        // Choice 1 - Determines Stats
        switch (userInput)
        {
            case 1:
            {
                // cout << "Tom W. Davis bestows his wisdom upon you." << endl;
                // cout << "Strength and Intellect Increased by 5. Current and Max HP increased by 10." << endl;
                LED.WriteLine("Tom W. Davis bestows his wisdom upon you.");
                LED.WriteLine("Strength and Intellect Increased by 5. Current and Max HP increased by 10.");

                player.setStrength(player.getStrength() + 5);
                player.setIntellect(player.getIntellect() + 5);

                player.setMaxHP(player.getMaxHP() + 10);
                player.setCurrentHP(player.getCurrentHP() + 10);

                flag = true;
                break;
            }

            case 2:
            {
                // cout << "You are a deplorable human being if you choose to not worship the clocktower." << endl;
                // cout << "Sense of time decreased by 5. You now have no clue what time it is." << endl;
                LED.WriteLine("You are a deplorable human being if you choose to not worship the clocktower.");
                LED.WriteLine("Sense of time decreased by 5. You now have no clue what time it is.");

                flag = true;
                break;
            }

            default: 
            {                
                // cout << "Invalid selection. Please enter a valid input." << endl;
                LED.WriteLine("Invalid Selection. Please enter a valid input.");

                break;
            }                       
        }
    }       

    // Choice 2 - Determines Stats 
    // cout << "You stop for a bite to eat right before the righteous crusade." << endl;
    // cout << "Which station at Scott do you stop?" << endl;   
    LED.WriteLine("You stop for a bite to eat right before the righteous crusade.");
    LED.WriteLine("Which station at Scott do you stop?");

    // cout << "Options: " << endl;
    // cout << "(1) Mongolian (Strength Up)" << endl;
    // cout << "(2) Breakfast Station (Intellect Up)" << endl;   
    LED.WriteLine("Options: ") ;
    LED.WriteLine("(1) Mongolian (Strength Up)");
    LED.WriteLine("(2) Breakfast Station (Intellect Up)");              
    
    flag = false; // Input validation 
    while (!flag)
    {
        // cout << "Your choice: ";
        LED.WriteLine("Your Choice: ");

        cin >> userInput; 

        switch (userInput)
        {
            case 1: 
            {                
                // cout << "Waiting for Wok...." << endl;
                LED.WriteLine("Waiting for Wok...");

                // Todo - Insert 5 second wait time 
                // cout << "You had a hearty Mongolian meal. Strength increased by 5." << endl;
                LED.WriteLine("You had a hearty Mongolian meal. Strength increased by 5.");
                
                player.setStrength(player.getStrength() + 5);

                flag = true;
                break;                        
            }

            case 2:
            {
                // cout << "You had a hearty breakfast. Intellect increased by 5." << endl;
                LED.WriteLine("You had a hearty breakfast. Intellect increased by 5.");

                player.setIntellect(player.getIntellect() + 5);

                flag = true;
                break;
            }

            default:
            {
                // cout << "Invalid selection. Please enter a valid input." << endl;
                LED.WriteLine("Invalid selection. Please enter a valid input.");
                break;
            }
        }   
    }

    player.setSavePointValues();

    /* Begin Proteus fights */
    bool flag2; // I'm very good at descriptive variable names if you couldn't tell 
    flag = false;
    
    // This loop dictates whether or not they are done fighting proteii 
    while (!flag)
    {
        player.setSavePointValues();

        // cout << "Fight a proteus robot to gain more XP and raise your stats?" << endl;          
        // cout << "(1) Yes" << endl;
        // cout << "(2) No" << endl;  
        LED.WriteLine("Fight a proteus robot to gain more XP and raise your stats?");
        LED.WriteLine("(1) Yes");
        LED.WriteLine("(2) No");

        // cout << "Your Choice: ";
        LED.WriteLine("Your Choice: ");

        cin >> userInput; 

        switch (userInput)
        {
            // If the user wants to battle 
            case 1:
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

                break;
            }

            // Skip the proteus step and break out of both loops basically
            case 2:
            {
                flag = true;
                break;
            }

            // Input Validation
            default:
            {
                // cout << "Did not understand input. Please enter something that isn't as stupid as whatever you entered." << endl;
                LED.WriteLine("Did not understand input. Please enter something that isn't as stupid as whatever you entered.");

                break;
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
            // cout << "Jane Fight: " << endl;
            LED.WriteLine("Jane Fight: ");

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
                    // cout << "Smth screwed up in Jane fight." << endl;
                    LED.WriteLine("Something screwed up in Jane fight.");

                    break;
                }
            }
            
        }

        player.setSavePointValues();

        flag2 = false;
        while (!flag2)
        {
            // cout << "Aidan Fight: " << endl;
            LED.WriteLine("Aidan Fight: ");

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
                    // cout << "Smth screwed up in Jane fight." << endl;
                    LED.WriteLine("Something screwed up in Aidan fight.");

                    break;
                }
            }            
        }

        player.setSavePointValues();

        flag2 = false;
        while (!flag2)
        {
            // cout << "Barley Fight" << endl;  
            LED.WriteLine("Barley Fight: ");

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
                    // cout << "Smth screwed up in Jane fight." << endl;
                    LED.WriteLine("Something screwed up in Barley fight.");
                    break;
                }
            }              
        }

        player.setSavePointValues();

        flag2 = false;
        while (!flag2)
        {
            // cout << "Erma Fight" << endl;     
            LED.WriteLine("Erma Fight: ");

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
                    // cout << "Smth screwed up in Jane fight." << endl;
                    LED.WriteLine("Something screwed up in Erma fight.");
                    break;
                }
            }           
        }
    }

    
    flag = false;
    while (!flag)
    {
        // cout << "Clingan Fight: " << endl;
        LED.WriteLine("Clingan Fight: ");

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
                // cout << "Unintented program behavior in Mr. Clingan switch statement." << endl;
                LED.WriteLine("Yo, Mr. Clingan control loop is screwed up");
            }
        }
    }

    // cout << "Congratulations! You win!" << endl;
    LED.WriteLine("Congratulations! You Win!");
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
{
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
            // cout << "You did " << playerDamage << " damage that turn." << endl;
            // cout << "You did " << playerHeal << " healing that turn." << endl;
            // cout << "The monster did " << monsterDamage << " damage that turn." << endl << endl;

            LCD.Write("You did "); LCD.Write(playerDamage); LCD.WriteLine(" damage that turn");
            LCD.Write("You did "); LCD.Write(playerHeal); LCD.WriteLine(" healing that turn.");
            LCD.Write("The enemy did "); LCD.Write(monsterDamage); LCD.WriteLine(" damage that turn.");
        }

        else
        {
            isFirstTurn = false;
        }

        // Displaying Health for both players
        // cout << "Current Enemy: " << name << endl;
        // cout << "Player Health: " << player -> getCurrentHP() << " | Enemy Health: " << enemy -> getCurrentHP() << endl << endl;
        LCD.Write("Current Enemy: "); LCD.Write(name); LCD.WriteLine("");
        LCD.Write("Player Health: "); LCD.Write(player -> getCurrentHP()); LCD.Write(" | Enemy Health: "); LCD.Write(enemy -> getCurrentHP()); LCD.WriteLine(""); LCD.WriteLine(""); // This was a fun line and I'm only putting this comment inline to make it even longer 

        /* Player Action */
        // cout << "Options: " << endl;
        // cout << "(1) Attack - Weapon" << endl;
        // cout << "(2) Attack - Code Injection" << endl;
        // cout << "(3) Heal" << endl;
        // cout << "Your Choice: ";         
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
                    // cout << "Illegitimate input." << endl;
                    LED.WriteLine("Illegitimate Input");
                }
            }            
        }       

        // Checking if the monster is dead 
        if (enemy -> getCurrentHP() <= 0)
        {
            // cout << "You killed the enemy! Level up!" << endl;
            LED.WriteLine("You Killed The Enemy! Level Up!");

            player -> levelUp();
            monstersDefeated++;
            return 0;
            break; // Monster's dead, don't need to continue the battle any more 
        }

        /* Monster's turn */
        monsterDamage = (rand() % 10 + 1) * enemy -> getStrength() / 12;
        player -> setCurrentHP(player -> getCurrentHP() - monsterDamage);

        // cout << "The monster did " << monsterDamage << " damage to you." << endl;      
        LED.Write("The monster did "); LED.Write(monsterDamage); LED.WriteLine(" damage to you.");

        // Checking if the player is dead
        if (player -> getCurrentHP() <= 0)
        {
            // cout << "The enemy killed you. Starting from most recent save point." << endl;
            LED.WriteLine("The enemy killed you. Starting from most recent save point.");

            deaths++;
            return 1;
            break; // You're dead, don't need to continue the battle any more
        }          
    }
}

// Displays the rules of the game - Run when the user hits "Rules"
void displayRules()
{
    // cout << "The rules are simple - SURVIVE." << endl;
    LCD.WriteLine("The rules are simple - SURVIVE, AND GET VENGEANCE.");

    // cout << "There are save points after every encounter and at several other points. If you die, you will restart from the most recent point." << endl;
    // cout << "Every monster you kill levels you up, so you are stronger and harder to kill." << endl;
    // cout << "Enjoy!" << endl;
    LCD.WriteLine("There are save points after every encounter and at several other points. If you die, you will restart from the most recent point.");
    LCD.WriteLine("Every monster you kill levels you up, so you are stronger and harder to kill.");
    LCD.WriteLine("Enjoy!");

    // Spacing
    // cout << endl;
    LCD.WriteLine("");
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

