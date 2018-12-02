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

// Imports for the console version
// Todo - Remove these when porting to proteus 

// Defining Constants 
// These ones just cut down on code we have to write 
#define BLACK FEHLCD::Black
#define WHITE FEHLCD::White

// Function Prototypes
void drawMenu(FEHIcon::Icon *buttons, char labels[][20]);

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

