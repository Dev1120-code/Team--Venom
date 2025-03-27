#include <bits/stdc++.h>
#include <iomanip>
#include <vector>
#include <random>
#include <conio.h>
#include <fstream>
void red() { printf("\033[1;33m"); }
void yellow() { printf("\033[1;31m"); }
void green() { printf("\033[38;2;255;165;0m"); }
void cyan() { printf("\033[1;36m"); }
void magenta() { printf("\033[1;35m"); }
void blue() { printf("\033[1;34m"); }   
void orange() { printf("\033[38;2;255;140;0m"); }  
void reset() { printf("\033[0m"); }
int score = 0;
int highscore = 0;
const std::string HIGH_SCORE_FILE = "highscore.txt";

const int GRID_WIDTH = 30;    
const int GRID_HEIGHT = 20;   
const int BLOCK_SIZE = 4; 


void loadHighScore() {
    std::ifstream file(HIGH_SCORE_FILE);
    if (file.is_open()) {
        file >> highscore;
        file.close();
    }
}

void saveHighScore() {
    std::ofstream file(HIGH_SCORE_FILE);
    if (file.is_open()) {
        file << highscore;
        file.close();
    }
}

void updateScore(int linesCleared) {
    score += linesCleared * 10;
    if (score > highscore) {
        highscore = score;
        saveHighScore();
    }
}


struct Random
{
    Random(int min, int max)
        : mUniformDistribution(min, max)
    {}

    int operator()()
    {
        return mUniformDistribution(mEngine);
    }

    std::default_random_engine mEngine{ std::random_device()() };
    std::uniform_int_distribution<int> mUniformDistribution;
};

std::vector<std::vector<int>> stage(GRID_HEIGHT + 2, std::vector<int>(GRID_WIDTH + 2, 0));

std::vector<std::vector<int>> block = 
{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
std::vector<std::vector<int>> field(GRID_HEIGHT + 2, std::vector<int>(GRID_WIDTH + 2, 0));

// coordinate
int y = 0; 
int x = GRID_WIDTH/2 - BLOCK_SIZE/2; 
bool gameover = false;
size_t GAMESPEED = 7500; 

Random getRandom{ 0, 6 };

std::vector<std::vector<std::vector<int>>> block_list =
{ 
    {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,}},
    {{0,0,0,0},{ 0,0,1,0},{0,0,1,0},{0,1,1,0}},
    {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
    {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
    {{0,0,0,0},{0,0,0,0},{1,1,1,0},{0,1,0,0}},
    {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
    {{0,0,0,0},{0,1,0,0},{0,1,0,0},{0,1,1,0}},
};

int menu(); 
int gameOver(); 
void title(); 
void gameLoop(); 
void display(); 
bool makeBlocks(); 
void initGame(); 
void moveBlock(int, int); 
void collidable();
bool isCollide(int, int); 
void userInput(); 
bool rotateBolck(); 
void spwanBlock();
void checkfullrows();

int main()
{
    switch (menu())
    {
    case 1:
        gameLoop();
        break;
    case 2:
        return 0;
    case 0:
    magenta();
        std::cerr << "Choose 1~3" << std::endl;
        return -1;
    }
    return 0;
}

void checkfullrows()
{
    int linescleared = 0;
    for (size_t i = 0; i < GRID_HEIGHT; i++)
    {
        bool full = true;
        for (size_t j = 1; j < GRID_WIDTH + 1; j++)
        {
            if (field[i][j] == 0)
            {
                full = false;
                break;
            }
        }
        if (full)
        {
            linescleared++;
            
            for (size_t j = 1; j < GRID_WIDTH + 1; j++)
            {
                field[i][j] = 0;
            }
            
            for (size_t k = i; k > 0; k--)
            {
                for (size_t j = 1; j < GRID_WIDTH + 1; j++)
                {
                    field[k][j] = field[k - 1][j];
                }
            }
            
            for (size_t j = 1; j < GRID_WIDTH + 1; j++)
            {
                field[0][j] = 0;
            }
        }
    }
    if(linescleared > 0)
    {
        updateScore(linescleared);
    }
}
int gameOver()
{
    using namespace std;

    char a;
    magenta();
    cout << " GGGG    AAA    M   M   EEEEE      OOO    V   V    EEEEE   RRRR "<<endl;
    cout << "G       A   A   MM MM   E         O   O   V   V    E       R   R"<<endl;
    cout << "G  GG   AAAAA   M M M   EEEE      O   O   V   V    EEEE    RRRR "<<endl;
    cout << "G   G   A   A   M   M   E         O   O    V V     E       R  R "<<endl;
    cout << " GGGG   A   A   M   M   EEEEE      OOO      V      EEEEE   R   R"<<endl;
    cyan();
    cout << " \n\t  ~ THANK YOU FOR PLAYING! ~    \n";
   
    cin >> a;
    return 0;
}

void gameLoop()
{
    size_t time = 0;
    initGame();

    while (!gameover) 
    { 
        if (kbhit()) 
        {
            userInput();
        }

        if (time < GAMESPEED)
        {
            time++;
        }
        else 
        {
            spwanBlock();
            time = 0;
        }
    }

}

int menu()
{
    title();

    int select_num = 0;

    std::cin >> select_num;

    switch (select_num)
    {
    case 1:
    case 2:
    std::cout<<"High Score: "<<highscore<<std::endl;
        return select_num;
    case 3:
        break;
    default:
        select_num = 0;
        break;
    }

    return select_num;
}

void title()
{
    using namespace std;

    system("cls");
    cyan();
    cout << "\n\t***************************************************\n";
    cout << "\tHello Player! Welcome to the TETRIS GAME by \n\n";
    magenta();
    cout << "                      TEAM VENOM         ";
    cyan();
    cout << "\n";
    cout << "\t***************************************************\n\n";




    
    cout << "MENU:\n";
    cyan(); 
    cout << "1: Start Game\n";
red();
    
    cout << "Choose >> ";
}
void display()
{
    system("cls");
    yellow();
    std::cout << "Score: " << score << "\tHigh Score: " << highscore << std::endl;

    for (size_t i = 0; i < GRID_HEIGHT + 1; i++)  // Changed from 21
    {
        for (size_t j = 0; j < GRID_WIDTH + 2; j++)  // Changed from 12
        {switch (field[i][j]) 
            {
                case 0:
                std::cout << " " << std::flush;
                break;
                case 9:   
                red();
                std::cout << "|" << std::flush;
                break;
            
                default:
                cyan();
                std::cout << "#" << std::flush;
                break;
            }
            
            
        }std::cout << std::endl;
    
    }
    cyan();
    std::cout<<"\nUSE LEFT ARROW TO MOVE LEFT\nUSE RIGHT ARROW TO MOVE RIGHT\nUP ARROW TO ROTATE BLOCK\nUSE DOWN ARROW TO SOFTDROP\nUSE SPACEBAR TO HARDDROP\nEscape TO Pause or Quit\n";


    if (gameover)
    {
        system("cls");
        gameOver();
    }
}


void initGame()
{
    // Replace all numbers with GRID_WIDTH/HEIGHT
    for (size_t i = 0; i <= GRID_HEIGHT; i++)  // Changed from 20
    {
        for (size_t j = 0; j <= GRID_WIDTH + 1; j++)  // Changed from 11
        {
            if ((j == 0) || (j == GRID_WIDTH + 1) || (i == GRID_HEIGHT)) 
            {
                field[i][j] = stage[i][j] = 9;
            }
            else
            {
                field[i][j] = stage[i][j] = 0;
            }
        }
    }
    makeBlocks();
    display();
}
bool makeBlocks()
{
    // 1. Set spawn position (centered horizontally)
    x = GRID_WIDTH / 2 - 2;  // -2 because blocks are 4 units wide (BLOCK_SIZE=4)
    y = 0;  // Always spawn at top

    // 2. Get random block type (0-6)
    int blockType = getRandom();

    // 3. Clear current block data
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            block[i][j] = 0;
            // Load shape from block_list
            block[i][j] = block_list[blockType][i][j];
        }
    }

    // 4. Place block on field with boundary checks
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            // Only modify if within grid bounds
            if (y + i < GRID_HEIGHT + 1 &&       // +1 for bottom wall
                x + j < GRID_WIDTH + 2 &&        // +2 for side walls
                block[i][j] != 0)                // Only place active blocks
            {
                field[y + i][x + j] = stage[y + i][x + j] + block[i][j];
                
                // Collision detection (block overlaps existing blocks)
                if (field[y + i][x + j] > 1) {
                    gameover = true;
                    return true;  // Game over
                }
            }
        }
    }
    return false;  // Block placed successfully
}



void moveBlock(int x2, int y2)
{

    //Remove block
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            field[y + i][x + j] -= block[i][j];
        }
    }
    //Update coordinates
    x = x2;
    y = y2;

    // assign a block with the updated value
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            field[y + i][x + j] += block[i][j];
        }
    }

    display();
}


void collidable()
{
    for (size_t i = 0; i < GRID_HEIGHT + 1; i++)  // Changed from 21
    {
        for (size_t j = 0; j < GRID_WIDTH + 2; j++)  // Changed from 12
        {
            stage[i][j] = field[i][j];
        }
    }
}


bool isCollide(int x2, int y2)
{
    for (size_t i = 0; i < BLOCK_SIZE; i++)
    {
        for (size_t j = 0; j < BLOCK_SIZE; j++)
        {
            // Check if block cell is occupied
            if (block[i][j]) 
            {
                // Calculate position on grid
                int gridX = x2 + j;
                int gridY = y2 + i;
                
                // Boundary checks
                if (gridX < 0 || gridX >= GRID_WIDTH + 2 || 
                    gridY < 0 || gridY >= GRID_HEIGHT + 1)
                {
                    return true;  // Collision with walls
                }
                
                // Collision with existing blocks
                if (stage[gridY][gridX] != 0) 
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool rotateBolck()
{
    std::vector<std::vector<int>> tmp(4, std::vector<int>(4, 0));

    for (size_t i = 0; i < 4; i++)
    { //Save temporarily block
        for (size_t j = 0; j < 4; j++)
        {
            tmp[i][j] = block[i][j];
        }
    }

    for (size_t i = 0; i < 4; i++)
    { //Rotate
        for (size_t j = 0; j < 4; j++)
        {
            block[i][j] = tmp[3 - j][i];
        }
    }

    if (isCollide(x, y))
    { // And stop if it overlaps not be rotated
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                block[i][j] = tmp[i][j];
            }
        }
        return true;
    }

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            field[y + i][x + j] -= tmp[i][j];
            field[y + i][x + j] += block[i][j];
        }
    }

    display();

    return false;
}


void spwanBlock()
{
    if (!isCollide(x, y + 1))
    {
        moveBlock(x, y + 1);
    }
    else
    {
        // Lock the piece only if it's at the bottom or colliding
        if (y == 0 && isCollide(x, y)) 
        {
            gameover = true;
        }
        else
        {
            collidable();
            checkfullrows();
            makeBlocks();
        }
        display();
    }
}

void userInput()
{
    char key = getch();

    switch (key)
    {
    case 75: // Left arrow key
        if (!isCollide(x - 1, y))
        {
            moveBlock(x - 1, y);
        }
        break;
    case 77: // Right arrow key
        if (!isCollide(x + 1, y))
        {
            moveBlock(x + 1, y);
        }
        break;
    case 80: // Down arrow key
        if (!isCollide(x, y + 1))
        {
            moveBlock(x, y + 1);
        }
        break;
    case 72: // Up arrow key
        rotateBolck();
        
        break;
    case 32: // Spacebar
        while (!isCollide(x, y + 1))
        {
            moveBlock(x, y + 1);
        }
        break;
    case 27: // Escape key
        gameover = true;
        break;

    }
}
