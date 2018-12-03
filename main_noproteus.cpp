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

/* 

    BUG LIST

    Monster health is always an overflow value if it is declared as anything BUT a member of the base enemy class.
    For example, using "MrClingan enemy" and then finding its health gives a value of several million. There is some code
    in the game exhibiting this. 

    When you fail a run check, the window clears immediately, or in a manner that doesn't look very good. 

*/

#include <iostream>
#include <time.h> // Needed for randomization 

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

        // Essentially backs up the values so that they can be restored to upon death 
        void setSavePointValues()
        {
            spMaxHP = maxHP;
            spStrength = strength;
            spIntellect = intellect;
            spDexterity = dexterity;
            spCharisma = charisma;
        }

        void restoreSavePointValues()
        {
            maxHP = spMaxHP;
            strength = spStrength;
            intellect = spIntellect;
            dexterity = spDexterity;
            charisma = spCharisma;
        }

        void levelUp()
        {
            currentHP += 10;
            maxHP += 10;
            strength += 5;
            intellect += 5;
            dexterity += 5;
            charisma += 5;
        }

        

    private: 

        // Base values - These can range from 0 to 100 theoretically 
        int currentHP = 100, maxHP = 100, strength = 10, intellect = 10, dexterity = 10, charisma = 50;    
        
        // Save point values
        int spMaxHP = 100, spStrength = 10, spIntellect = 10, spDexterity = 10, spCharisma = 10;
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

        void setMaxHP(int hp)
        {
            maxHP = hp;
        }        

    private: 

        int strength = 5, currentHP, maxHP;
    
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
    setCurrentHP(300);
    setMaxHP(300);
}

// Mr Clingan's very own constructor
MrClingan::MrClingan()
{
    setCurrentHP(500);
    setMaxHP(500);
}

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
    // Todo - Make it so that it clears the window every time for all aspects of the game and doesn't look bad 

    // Clears Console Window
    // Todo - Remove this on proteus version 
    system("cls"); // Windows

    // Seeding the random number generator w/ current time
    // Todo - Shift this to the proteus's time method
    srand(time(0));

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
void playGame()
{
    // Flag is used for loop control a TON 
    bool quit = false, flag = false, justDied = false;
    int savePoint = 0, battleResult, userInput; 

    // Initializing the player
    Player player;

    while (!quit)
    {
        switch(savePoint)
        {
            /* If the user ever dies or has to go back to a previous savepoint, you just break out of the savepoint.
                If you need to break out otherwise (if the user passes a segment) you just update the savepoint, 
                THEN break. */ 


            // Start of the game 
            case 0:
            {
                // No need to initialize save point values b/c that's done in the constructor b/c this is the game start

                // Rest of the code here 

                // Test battle to make sure the program reacts as expected
                MrClingan testEnemy;

                /* This whole structure could probably be simplified using goto statements but those are not good
                    practice in most situations apparently so f*ck that I guess */
                // Doesn't escape this loop until the user wins the battle
                while (!flag)
                {
                    if (justDied)
                    {
                        player.restoreSavePointValues(); // Sets the values to what they were at the last save point 
                        justDied = false;
                    }

                    cout << "Your Choices: " << endl;
                    cout << "(1) Fight Enemy" << endl;
                    cout << "(2) Heal to Full" << endl;

                    cin >> userInput;

                    // I am actually insane
                    // This isn't actually super complicated, it just looks like that 
                    switch(userInput)
                    {
                        case 1:
                        {
                            battleResult = battle(&player, &testEnemy);

                            switch (battleResult)
                            {
                                case 0:
                                {
                                    // Only this one lets you out of the full loop
                                    flag = true;
                                    break;
                                }

                                // Otherwise, the user chooses b/w fighting enemy and healing to full or smth
                                case 1:
                                {
                                    justDied = true;
                                    break;
                                }      

                                case 2:
                                {
                                    break;
                                }       

                                case 3:
                                {
                                    cout << "Battle returned an error. AKA smth screwed up." << endl;
                                    break;
                                }              
                            }

                            break;
                        }

                        case 2:
                        {
                            player.setCurrentHP(player.getMaxHP());
                            break;
                        }
                    }                                   
                }                

                // Updating Save Point b/c the user completed this section 
                savePoint = 1;
                break;
            }

            case 1:
            {
                // Updates save point values at the beginning of every save point so that it can be easily reset 
                player.setSavePointValues();

                // Updating save point b/c the user completed this section 
                savePoint = 2;
                break;
            }

            case 2: 
            {
                player.setSavePointValues();

                // Rest of the code here 

                // Updating save point b/c the user completed this section 
                savePoint = 3;
                break;
            }

            // Adieu
        }
    }
}

/* \


    Using return codes because it's a very customizable way of basically 
    doing a switch statement dependent on the result of a method.

    Return Codes Key:
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
        // Clears the screen every time
        system("cls");

        // Displaying Health for both players
        cout << "Player Health: " << player -> getCurrentHP() << " | Enemy Health: " << enemy -> getCurrentHP() << endl;

        /* Player Action */
        cout << "Options: " << endl;
        cout << "(1) Attack - Weapon" << endl;
        cout << "(2) Attack - Code Injection" << endl;
        cout << "(3) Attempt to Flee (60\% Chance of Success)" << endl;
        cout << "Your Choice: "; 

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
                // Starts at a success chance of 60% and increases by 1% per dexterity point 
                if ((rand() % 100 + 1) + player -> getDexterity() >= 40)
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
            break; // Monster's dead, don't need to continue the battle any more 
        }

        /* Monster Action */

        // Have to make sure the monster isn't dead or the player ran, in which case battle is over and these calculations don't need to happen 
        if (!canExitLoop && !userRan)
        {
            // Same procedure as above, except w/o the choice and switch statement 
            damage = enemy -> getStrength();
            player -> setCurrentHP(player -> getCurrentHP() - damage);

            cout << "The monster did " << damage << " damage to you." << endl;
        }

        // checking if the player is dead
        if (player -> getCurrentHP() <= 0)
        {
            canExitLoop = true;
            break; // You're dead, don't need to continue the battle any more
        }
    }

    /* Displaying result of the game to the user and returning the proper value */
    if (enemy -> getCurrentHP() <= 0)
    {
        cout << "You won the battle." << endl;
        player -> levelUp(); // Level up once per battle 
        return 0; // Return code for a win
    }

    else if (player -> getCurrentHP() <= 0)
    {
        cout << "You lost the battle. Reviving at last savepoint." << endl;
        return 1;
    }

    // Computing the result of the battle
    else if (userRan)
    {
        cout << "You ran from battle successfully." << endl;
        return 2; // Return code for when you run 
    }

    else
    {
        cout << "Battle function exited when it shouldn't have, seeing as both player and enemy have >= 0 health." << endl;
        return 3; // Error code 
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



