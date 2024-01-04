#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int boardSizeX = 50, boardSizeY = boardSizeX / 2;   //board size
bool gameStop;
int snakeX, snakeY, appleX, appleY;
int snakebodyX[boardSizeX*boardSizeY], snakebodyY[boardSizeX * boardSizeY];
int bodynumber=0;
enum Movement {UP, DOWN, LEFT, RIGHT, STOP}; //tracks the direction in which is snake going
Movement direction;

void changeColor(int desiredColor) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}

void Start()
{
    srand(time(NULL));
    gameStop = false;
    direction = STOP;
    snakeX = rand() % (boardSizeX - 2) + 1; //without the first and last line
    snakeY = rand() % (boardSizeY - 2) + 1;
    appleX = rand() % (boardSizeX - 2) + 1;
    appleY = rand() % (boardSizeY - 2) + 1;

}

void Drawing()
{
    system("cls");  //clears the screen before drawing

    for (int x = 0; x <= boardSizeX; x++)
        cout << '#';
    cout << endl;

    for (int y = 1; y < boardSizeY; y ++)   
    {
        for (int x = 0; x <= boardSizeX; x ++)
        {
            if (x == 0 || x == boardSizeX) cout << '#';
            else if (x == snakeX && y == snakeY)
            {
                changeColor(2);
                cout << 'O';
                changeColor(7);
            }
            else if (x == appleX && y == appleY)
            {
                changeColor(12);
                cout << 'A';
                changeColor(7);
            }
            else
            {
                bool body = false;
                
                for (int i = 0; i < bodynumber; i++)
                {
                    if (snakebodyX[i] == x && snakebodyY[i] == y)
                    {
                        changeColor(2);
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
        cout << '#';
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

    for (int i = 1; i < bodynumber; i++)
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

    if (snakeX >= boardSizeX) snakeX = 1;
    if (snakeX <= 0) snakeX = boardSizeX - 1;
    if (snakeY >= boardSizeY) snakeY = 1;
    if (snakeY <= 0) snakeY = boardSizeY - 1;

    if (snakeX == appleX && snakeY == appleY)
    {
        bodynumber++;
        appleX = rand() % (boardSizeX - 2) + 1;
        appleY = rand() % (boardSizeY - 2) + 1;
       
    }

    for (int i = 0; i < bodynumber; i++)    //gameover if snake crosses its tail
        if (snakeX == snakebodyX[i] && snakeY == snakebodyY[i])
            gameStop = true;

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

    
    return 0;
}