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

}

// Displays credits - Run when the user hits "credits"
void displayCredits()
{

}

// Displays Stats  - Run when the user hits "stats"
// Will probably display stuff like number of times won, deaths, enemies killed, stuff like that idk 
void displayStats()
{

}

