#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int boardSizeX = 25, boardSizeY = boardSizeX / 2;   //board size
bool gameStop;
int snakeX, snakeY, appleX, appleY, score;
int snakebodyX[boardSizeX*boardSizeY], snakebodyY[boardSizeX * boardSizeY];
int bodynumber=0;
enum Movement {UP, DOWN, LEFT, RIGHT, STOP}; //tracks the direction in which is snake going
Movement direction;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void changeColor(int desiredColor) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}

void Start()
{
    srand(time(NULL));
    gameStop = false;
    direction = STOP;
    snakeX = rand() % (boardSizeX - 2) + 1; //snakes spawns randomly within the boarder
    snakeY = rand() % (boardSizeY - 2) + 1;
    appleX = rand() % (boardSizeX - 2) + 1;
    appleY = rand() % (boardSizeY - 2) + 1;

}

void Drawing()
{

    system("cls");  //clears the screen before drawing

    for (int x = 0; x <= boardSizeX; x++)
        cout << 'X';
    cout << endl;

    for (int y = 1; y < boardSizeY; y ++)   
    {
        for (int x = 0; x <= boardSizeX; x ++)
        {
            if (x == 0 || x == boardSizeX) cout << 'X';
            else if (x == snakeX && y == snakeY)
            {
                changeColor(2);     //draws head of the snake
                cout << 'O';
                changeColor(7);
            }
            else if (x == appleX && y == appleY)
            {
                changeColor(12);        //draws the 'apple'
                cout << '*';
                changeColor(7);
            }
            else
            {
                bool body = false;
                
                for (int i = 0; i < bodynumber; i++)
                {
                    if (snakebodyX[i] == x && snakebodyY[i] == y)
                    {
                        changeColor(2);     //draws the tail of the snake 
                        cout << 'o';
                        body = true;
                        changeColor(7);
                    }
                }
                if (body == false) cout << " ";
                

            }


        }
        cout << endl;
    }

    for (int x = 0; x <= boardSizeX; x++)
        cout << 'X';
    cout << endl;
}

void Controling()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':   direction = UP; break;
        case 's':   direction = DOWN; break;
        case 'a':   direction = LEFT; break;
        case 'd':   direction = RIGHT; break;
        case 'p': gameStop = true;
        }
    }

}

void Gameplay()
{
    
    int lastsnakeX = snakebodyX[0], lastsnakeY = snakebodyY[0];
    int lastsnakeX2, lastsnakeY2;
    snakebodyX[0] = snakeX;
    snakebodyY[0] = snakeY;

    for (int i = 1; i < bodynumber; i++)            //spawning snakes body
    {
        lastsnakeX2 = snakebodyX[i];
        lastsnakeY2 = snakebodyY[i];
        snakebodyX[i] = lastsnakeX;
        snakebodyY[i] = lastsnakeY;
        lastsnakeX = lastsnakeX2;
        lastsnakeY = lastsnakeY2;
    }


    switch (direction)
    {
    case UP:   snakeY-- ; break;
    case DOWN:   snakeY++ ; break;
    case LEFT:   snakeX-- ; break;
    case RIGHT:   snakeX++; break;
    default: break;
    }

    if (snakeX >= boardSizeX) snakeX = 1;       //going into the boarder
    if (snakeX <= 0) snakeX = boardSizeX - 1;
    if (snakeY >= boardSizeY) snakeY = 1;
    if (snakeY <= 0) snakeY = boardSizeY - 1;

    if (snakeX == appleX && snakeY == appleY)       //spawning apple
    {
        bodynumber++;
        appleX = rand() % (boardSizeX - 2) + 1;
        appleY = rand() % (boardSizeY - 2) + 1;
        score++;
       
    }

    for (int i = 0; i < bodynumber; i++)    //gameover if snake crosses its tail
    {
        if (snakeX == snakebodyX[i] && snakeY == snakebodyY[i])
            gameStop = true;
        if (snakebodyX[i] == appleX && snakebodyY[i] == appleY) //if the apple spawns in snakes body it respawns somwhere else
        {
            appleX = rand() % (boardSizeX - 2) + 1;
            appleY = rand() % (boardSizeY - 2) + 1;
        }
    }

}

int main()
{
      
    Start();
    while (gameStop != true)
    {
        Drawing();
        Controling();
        Gameplay();
        Sleep(70);  //function to make the snake slower
    }
    
    cout << "\n\n\tYour score: " << score << "\n\n";

    
    return 0; 
}