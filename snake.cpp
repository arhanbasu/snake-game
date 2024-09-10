#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#define SNAKE_ARRAY_SIZE 310


#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define UP_ARROW  'A'
#define LEFT_ARROW  'D'
#define RIGHT_ARROW  'C'
#define DOWN_ARROW 'B'
#define ENTER_KEY 10

const char SNAKE_HEAD = '@';
const char SNAKE_BODY = '*';
const char WALL = '|';
const char CEIL = '-';
const char FOOD = 'X';
const char BLANK = ' ';

void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}


int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

char getch()
{
    char c;
    system("stty raw");
    c= getchar();
    system("stty sane");
    return(c);
}

void clrscr()
{
    system("clear");
    return;
}


#define EXIT_BUTTON 27 
#define PAUSE_BUTTON 112 

char waitForAnyKey(void)
{
int pressed;

while(!kbhit());

pressed = getch();
return((char)pressed);
}

int getGameSpeed()
{
int speed = 1;
clrscr();

while(speed < 1 || speed > 9){
        return(speed);
}
return 1;
}




int checkKeysPressed(int direction)
{
int pressed;

if(kbhit()) 
{
    pressed=getch();
    if (direction != pressed)
    {
        if(pressed == DOWN_ARROW && direction != UP_ARROW)
            direction = pressed;
        else if (pressed == UP_ARROW && direction != DOWN_ARROW)
            direction = pressed;
        else if (pressed == LEFT_ARROW && direction != RIGHT_ARROW)
            direction = pressed;
        else if (pressed == RIGHT_ARROW && direction != LEFT_ARROW)
            direction = pressed;
    }
}
return(direction);
}

int collisionSnake (int x, int y, int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength, int detect)
{
int i;
for (i = detect; i < snakeLength; i++) //Checks if the snake collided with itself
{
    if ( x == snakeXY[0][i] && y == snakeXY[1][i])
        return(1);
}
return(0);
}

int generateFood(int foodXY[], int width, int height, int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength)
{

do
{
    srand ( time(NULL) );
    foodXY[0] = rand() % (width-2) + 2;
    srand ( time(NULL) );
    foodXY[1] = rand() % (height-6) + 2;
} while (collisionSnake(foodXY[0], foodXY[1], snakeXY, snakeLength, 0)); 

gotoxy(foodXY[0] ,foodXY[1]);
printf("%c", FOOD);

return(0);
}


void moveSnakeArray(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength, int direction)
{
int i;
for( i = snakeLength-1; i >= 1; i-- )
{
    snakeXY[0][i] = snakeXY[0][i-1];
    snakeXY[1][i] = snakeXY[1][i-1];
}

switch(direction)
{
    case DOWN_ARROW:
        snakeXY[1][0]++;
        break;
    case RIGHT_ARROW:
        snakeXY[0][0]++;
        break;
    case UP_ARROW:
        snakeXY[1][0]--;
        break;
    case LEFT_ARROW:
        snakeXY[0][0]--;
        break;
}

return;
}

void move(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength, int direction)
{
int x;
int y;

x = snakeXY[0][snakeLength-1];
y = snakeXY[1][snakeLength-1];

gotoxy(x,y);
printf("%c",BLANK);

gotoxy(snakeXY[0][0],snakeXY[1][0]);
printf("%c", SNAKE_BODY);

moveSnakeArray(snakeXY, snakeLength, direction);

gotoxy(snakeXY[0][0],snakeXY[1][0]);
printf("%c",SNAKE_HEAD);

gotoxy(1,1); 

return;
}

int eatFood(int snakeXY[][SNAKE_ARRAY_SIZE], int foodXY[])
{
if (snakeXY[0][0] == foodXY[0] && snakeXY[1][0] == foodXY[1])
{
    foodXY[0] = 0;
    foodXY[1] = 0; 

    printf("\7"); 
    return(1);
}

return(0);
}

int collisionDetection(int snakeXY[][SNAKE_ARRAY_SIZE], int consoleWidth, int consoleHeight, int snakeLength ) 
{
int colision = 0;
if ((snakeXY[0][0] == 1) || (snakeXY[1][0] == 1) || (snakeXY[0][0] == consoleWidth) || (snakeXY[1][0] == consoleHeight - 4)) 
    colision = 1;
else
    if (collisionSnake(snakeXY[0][0], snakeXY[1][0], snakeXY, snakeLength, 1)) 
        colision = 1;

return(colision);
}

void refreshInfoBar(int score, int speed)
{
gotoxy(5,23);
printf("Score: %d", score);

gotoxy(5,24);
printf("Speed: %d", speed);

gotoxy(52,23);
printf("CodeBy : Arhan");

gotoxy(52,24);
printf("Version: 0.1");

return;
}


void gameOverScreen(void)
{
int x = 17, y = 3;

gotoxy(x,y++);
printf(":'######::::::'###::::'##::::'##:'########:\n");
gotoxy(x,y++);
printf("'##... ##::::'## ##::: ###::'###: ##.....::\n");
gotoxy(x,y++);
printf(" ##:::..::::'##:. ##:: ####'####: ##:::::::\n");
gotoxy(x,y++);
printf(" ##::'####:'##:::. ##: ## ### ##: ######:::\n");
gotoxy(x,y++);
printf(" ##::: ##:: #########: ##. #: ##: ##...::::\n");
gotoxy(x,y++);
printf(" ##::: ##:: ##.... ##: ##:.:: ##: ##:::::::\n");
gotoxy(x,y++);
printf(". ######::: ##:::: ##: ##:::: ##: ########:\n");
gotoxy(x,y++);
printf(":......::::..:::::..::..:::::..::........::\n");
gotoxy(x,y++);
printf(":'#######::'##::::'##:'########:'########::'####:\n");
gotoxy(x,y++);
printf("'##.... ##: ##:::: ##: ##.....:: ##.... ##: ####:\n");
gotoxy(x,y++);
printf(" ##:::: ##: ##:::: ##: ##::::::: ##:::: ##: ####:\n");
gotoxy(x,y++);
printf(" ##:::: ##: ##:::: ##: ######::: ########::: ##::\n");
gotoxy(x,y++);
printf(" ##:::: ##:. ##:: ##:: ##...:::: ##.. ##::::..:::\n");
gotoxy(x,y++);
printf(" ##:::: ##::. ## ##::: ##::::::: ##::. ##::'####:\n");
gotoxy(x,y++);
printf(". #######::::. ###:::: ########: ##:::. ##: ####:\n");
gotoxy(x,y++);
printf(":.......::::::...:::::........::..:::::..::....::\n");

waitForAnyKey();
clrscr(); 
return;
}


void startGame( int snakeXY[][SNAKE_ARRAY_SIZE], int foodXY[], int consoleWidth, int consoleHeight, int snakeLength, int direction, int score, int speed)
{
int gameOver = 0;
clock_t endWait;


int waitMili = CLOCKS_PER_SEC-(speed)*(CLOCKS_PER_SEC/10);  
int tempScore = 10*speed;
int oldDirection;
int canChangeDirection = 1;


endWait = clock() + waitMili;

do
{
    if(canChangeDirection)
    {
        oldDirection = direction;
        direction = checkKeysPressed(direction);
    }

    if(oldDirection != direction)
        canChangeDirection = 0;

    if(clock() >= endWait) 
    {

        move(snakeXY, snakeLength, direction);
        canChangeDirection = 1;


        if(eatFood(snakeXY, foodXY))
        {
            generateFood( foodXY, consoleWidth, consoleHeight, snakeXY, snakeLength);
            snakeLength++;
            score+=10;

            if( score >= 10*speed+tempScore)
            {
                speed++;
                tempScore = score;

                if(speed <= 9)
                    waitMili = waitMili - (CLOCKS_PER_SEC/10);
                else
                {
                    if(waitMili >= 40) 
                        waitMili = waitMili - (CLOCKS_PER_SEC/200);

                }

            }

            refreshInfoBar(score, speed);
        }

        endWait = clock() + waitMili; 
    }

    gameOver = collisionDetection(snakeXY, consoleWidth, consoleHeight, snakeLength);

    if(snakeLength >= SNAKE_ARRAY_SIZE-5) 
    {
        gameOver = 2;
        score+=1500; 
    }

} while (!gameOver);

switch(gameOver)
{
    case 1:
        printf("\7"); 
        printf("\7"); 

        gameOverScreen();
        break;
}

return;
}


void loadEnviroment(int consoleWidth, int consoleHeight)
{

int x = 1, y = 1;
int rectangleHeight = consoleHeight - 4;
clrscr(); 

gotoxy(x,y); 

for (; y < rectangleHeight; y++)
{
    gotoxy(x, y); 
    printf("%c",WALL);

    gotoxy(consoleWidth, y); 
    printf("%c",WALL);
}

y = 1;
for (; x < consoleWidth+1; x++)
{
    gotoxy(x, y); 
    printf("%c",WALL);

    gotoxy(x, rectangleHeight); 
    printf("%c",WALL);
}

return;
}


void loadSnake(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength)
{
int i;

for (i = 0; i < snakeLength; i++)
{
    gotoxy(snakeXY[0][i], snakeXY[1][i]);
    printf("%c", SNAKE_BODY); 
}

return;
}


void prepairSnakeArray(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength)
{
int i;
int snakeX = snakeXY[0][0];
int snakeY = snakeXY[1][0];



for(i = 1; i <= snakeLength; i++)
{
    snakeXY[0][i] = snakeX + i;
    snakeXY[1][i] = snakeY;
}

return;
}

//This function loads the environment, snake, etc
void loadGame(void)
{
int snakeXY[2][SNAKE_ARRAY_SIZE]; 

int snakeLength = 2; 

int direction = LEFT_ARROW; 

int foodXY[] = {5,5};

int score = 0;
int consoleWidth = 80;
int consoleHeight = 25;

int speed = getGameSpeed();

snakeXY[0][0] = 40;
snakeXY[1][0] = 10;

loadEnviroment(consoleWidth, consoleHeight); 
prepairSnakeArray(snakeXY, snakeLength);
loadSnake(snakeXY, snakeLength);
generateFood( foodXY, consoleWidth, consoleHeight, snakeXY, snakeLength);
refreshInfoBar(score, speed); 
startGame(snakeXY, foodXY, consoleWidth, consoleHeight, snakeLength, direction, score, speed);

return;
}


int main() 
{
  loadGame();

  return(0);
}



