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
            }

            if(menu[1].Pressed(x,y,0))
            {
                menu[1].WhilePressed(x,y);
                LCD.Clear(BLACK);
                LCD.WriteLine("RULES");
            }

            if(menu[2].Pressed(x,y,0))
            {
                menu[2].WhilePressed(x,y);
                LCD.Clear(BLACK);
                LCD.WriteLine("CREDITS");
            }

            if(menu[3].Pressed(x,y,0))
            {
                menu[3].WhilePressed(x,y);
                LCD.Clear(BLACK);
                LCD.WriteLine("STATS");
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
