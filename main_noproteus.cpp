
/*

    TODO 

    Make the output look better and reset more consistently 

    Convert to Proteus Code (doesn't come until end)

*/

#include <iostream>
#include <time.h> // Needed for randomization 

using namespace std;

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

/* Function Protypes - Must be declared after class declarations */
bool playGame(); 
int battle(Player* player, Enemy* enemy, const char *name);
void displayRules();
void displayCredits();
void displayStats();

int main(void)
{
    system("cls"); // Clearing window 

    // Seeding the random number generator w/ current time
    srand(time(0));

    bool exitVar = false;
    int userInput;

    // Pure c++ replacement for below code
    while (!exitVar)
    {
        cout << "Welcome to Undertale Lite!" << endl << endl;
        cout << "Options: " << endl;
        cout << "(1) Play Game" << endl;
        cout << "(2) Display Stats" << endl;
        cout << "(3) Display Rules" << endl;
        cout << "(4) Display Credits" << endl;
        cout << "(5) Quit" << endl; 

        cout << "Your Choice: ";
        cin >> userInput;

        // Spacing
        cout << endl;

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
bool playGame()
{
    gamesPlayed++;
    int battleResult, userInput; 

    // Initializing the player
    Player player;

    /* Exposition */
    cout << "Tonight was the night that it would all change." << endl;

    cout << "It all started that fateful night, many years ago. The FEH program had "; 
    cout << "Existed peacefully, as it had for years, serving as a haven for exploration ";
    cout << "and learning." << endl;

    cout << "And then that peace had been torn to shreds by Clingan and his conspirators that ";
    cout << "fateful day. Clingan and his teaching staff had risen up, and now held control of ";
    cout << "The FEH program. They had stormed Hitchcock at night, and held the rest of the ";
    cout << "Teaching staff captive." << endl;

    cout << "Tonight was the night that we, the Anti-Clingan Freedom Front (ACFF), would take ";
    cout << "back Hitchcock." << endl << endl;
    
    cout << "You pass underneath the Tom W. Davis Clocktower. Do you pray for guidance?" << endl; 
    cout << "(1) Yes" << endl;
    cout << "(2) No" << endl;
    cout << "Your Choice: ";

    cin >> userInput;

    bool flag = false; // Input validation GOD 
    while (!flag)
    {
        // Choice 1 - Determines Stats
        switch (userInput)
        {
            case 1:
            {
                cout << "Tom W. Davis bestows his wisdom upon you." << endl;
                cout << "Strength and Intellect Increased by 5. Current and Max HP increased by 10." << endl;

                player.setStrength(player.getStrength() + 5);
                player.setIntellect(player.getIntellect() + 5);

                player.setMaxHP(player.getMaxHP() + 10);
                player.setCurrentHP(player.getCurrentHP() + 10);

                flag = true;
                break;
            }

            case 2:
            {
                cout << "You are a deplorable human being if you choose to not worship the clocktower." << endl;
                cout << "Sense of time decreased by 5. You now have no clue what time it is." << endl;

                flag = true;
                break;
            }

            default: 
            {
                cout << "Invalid selection. Please enter a valid input." << endl;

                break;
            }                       
        }
    }       

    // Choice 2 - Determines Stats 
    cout << "You stop for a bite to eat right before the righteous crusade." << endl;
    cout << "Which station at Scott do you stop?" << endl;    

    cout << "Options: " << endl;
    cout << "(1) Mongolian (Strength Up)" << endl;
    cout << "(2) Breakfast Station (Intellect Up)" << endl;                      
    
    flag = false; // Input validation 
    while (!flag)
    {
        cout << "Your choice: ";
        cin >> userInput; 

        switch (userInput)
        {
            case 1: 
            {
                cout << "Waiting for Wok...." << endl;

                // Todo - Insert 5 second wait time 
                cout << "You had a hearty Mongolian meal. Strength increased by 5." << endl;
                
                player.setStrength(player.getStrength() + 5);

                flag = true;
                break;                        
            }

            case 2:
            {
                cout << "You had a hearty breakfast. Intellect increased by 5." << endl;
                player.setIntellect(player.getIntellect() + 5);

                flag = true;
                break;
            }

            default:
            {
                cout << "Invalid selection. Please enter a valid input." << endl;
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

        cout << "Fight a proteus robot to gain more XP and raise your stats?" << endl;          
        cout << "(1) Yes" << endl;
        cout << "(2) No" << endl;  

        cout << "Your Choice: ";
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
                cout << "Did not understand input. Please enter something that isn't as stupid as whatever you entered." << endl;
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
            cout << "Jane Fight: " << endl;

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
                    cout << "Smth screwed up in Jane fight." << endl;
                    break;
                }
            }
            
        }

        player.setSavePointValues();

        flag2 = false;
        while (!flag2)
        {
            cout << "Aidan Fight: " << endl;

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
                    cout << "Smth screwed up in Jane fight." << endl;
                    break;
                }
            }            
        }

        player.setSavePointValues();

        flag2 = false;
        while (!flag2)
        {
            cout << "Barley Fight" << endl;  

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
                    cout << "Smth screwed up in Jane fight." << endl;
                    break;
                }
            }              
        }

        player.setSavePointValues();

        flag2 = false;
        while (!flag2)
        {
            cout << "Erma Fight" << endl;     

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
                    cout << "Smth screwed up in Jane fight." << endl;
                    break;
                }
            }           
        }
    }

    
    flag = false;
    while (!flag)
    {
        cout << "Clingan Fight: " << endl;


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
                cout << "Unintented program behavior in Mr. Clingan switch statement." << endl;
            }
        }
    }

    cout << "Congratulations! You win!" << endl;
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
        system("cls");

        // Outputting results of last turn
        if (!isFirstTurn)
        {
            cout << "You did " << playerDamage << " damage that turn." << endl;
            cout << "You did " << playerHeal << " healing that turn." << endl;
            cout << "The monster did " << monsterDamage << " damage that turn." << endl << endl;
        }

        else
        {
            isFirstTurn = false;
        }

        // Displaying Health for both players
        cout << "Current Enemy: " << name << endl;
        cout << "Player Health: " << player -> getCurrentHP() << " | Enemy Health: " << enemy -> getCurrentHP() << endl << endl;

        /* Player Action */
        cout << "Options: " << endl;
        cout << "(1) Attack - Weapon" << endl;
        cout << "(2) Attack - Code Injection" << endl;
        cout << "(3) Heal" << endl;
        cout << "Your Choice: ";         

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
                    cout << "Illegitimate input." << endl;
                }
            }            
        }       

        // Checking if the monster is dead 
        if (enemy -> getCurrentHP() <= 0)
        {
            cout << "You killed the enemy! Level up!" << endl;
            player -> levelUp();
            monstersDefeated++;
            return 0;
            break; // Monster's dead, don't need to continue the battle any more 
        }

        /* Monster's turn */
        monsterDamage = (rand() % 10 + 1) * enemy -> getStrength() / 12;
        player -> setCurrentHP(player -> getCurrentHP() - monsterDamage);

        cout << "The monster did " << monsterDamage << " damage to you." << endl;      

        // Checking if the player is dead
        if (player -> getCurrentHP() <= 0)
        {
            cout << "The enemy killed you. Starting from most recent save point." << endl;
            deaths++;
            return 1;
            break; // You're dead, don't need to continue the battle any more
        }          
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
    cout << "Highest Level: " << highestLevel << endl;

    // Spacing 
    cout << endl;
}



