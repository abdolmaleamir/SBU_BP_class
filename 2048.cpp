#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <fstream>
using namespace std;



const int LEADERBOARD_SIZE = 10;
const string SAVE_FILE = "2048_save.txt";

struct personalinformation {
    string name;
    string lastname;
    int score;
};

personalinformation leaderboard[LEADERBOARD_SIZE] = {{ "", "", 0 }};
const int SIZE = 4;
const int PROBABILITY = 75;

void saveLeaderboard();
void loadLeaderboard();
void saveGame(const int a[SIZE][SIZE], const personalinformation& player);
void loadGame(int a[SIZE][SIZE], personalinformation& player);
void updateLeaderboard(const personalinformation& player);
int calculateScore(const int a[SIZE][SIZE]);
void upmove(int a[SIZE][SIZE]);
void downmove(int a[SIZE][SIZE]);
void leftmove(int a[SIZE][SIZE]);
void rightmove(int a[SIZE][SIZE]);
void printer(int a[SIZE][SIZE]);
void addBlock(int a[SIZE][SIZE]);
void displayBoard(int a[SIZE][SIZE]);
bool isEqual(int tmp[SIZE][SIZE], int a[SIZE][SIZE]);
bool isGameOver(int a[SIZE][SIZE]);
void newgame();
void displayLeaderboard();
void exit();
void menu();

void menu () {

     int a[SIZE][SIZE];  
    personalinformation player; 
    system("cls");
    cout << "Welcome to the game" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Leaderboard" << endl;
    cout << "4. Exit" << endl;
    cout << "Select one of the items : ";
    int choose;
    cin >> choose;
    switch (choose) {
        case 1 :
        newgame ();
        break;
        case 3 :
        displayLeaderboard();
        break;
        case 4 :
        exit();
        break;
        case 2 :
        loadGame(a, player);  
        newgame();  
        break;
        default :
        cout << "Your number is invalid.";
    }
    system("cls");
}

int main () {
    loadLeaderboard();
    menu();

   
return 0;
}

void newgame () {
    system("cls");
    cout << "please enter your Name : " ;
    personalinformation player;
    cin >> player.name;
    cout << "please enter your Lastname : " ;
    cin >> player.lastname;
    system("cls");
        int a[SIZE][SIZE] = {0}, tmp[SIZE][SIZE] = {0};
    srand(static_cast<unsigned>(time(0)));

    int i1 = rand() % SIZE; //initialize the first block
    int i2 = rand() % SIZE;
    int i3, i4;

    do {                    //making sure that the second block is not in the same place as the first block
        i3 = rand() % SIZE;
        i4 = rand() % SIZE;
    } while (i3 == i1 && i4 == i2);

    a[i1][i2] = 2;
    a[i3][i4] = (rand() % 100 < PROBABILITY) ? 2 : 4; //initializing the second block with 75 percent chance of being 2

    displayBoard(a);
    int playerScore = 0; 
    int ch;
    while (true) {
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                tmp[i][j] = a[i][j];  // storing the game in second matrix for comparing .

        ch = _getch();
        system("cls");

        switch (ch) {
            case 'w': 
                upmove(a);
                break;
            case 's': 
                downmove(a);
                break;
            case 'a': 
                leftmove(a);
                break;
            case 'd': 
                rightmove(a);
                 break;
        }

        if (!isEqual(tmp, a)) {
            addBlock(a);
            playerScore = calculateScore(a);
        }
        cout << "\n\t\t\t\tPlayer Score: " << playerScore << "\n";
        displayBoard(a);

        if (!isGameOver(a)) {
            cout << "\n\n\t\t\tGAME OVER!!\n\n\n";
            _getch();
            personalinformation currentPlayer;
            currentPlayer.name = player.name;
            currentPlayer.lastname = player.lastname;
            currentPlayer.score = calculateScore(a);
            updateLeaderboard(currentPlayer);
            menu();
        }
    }

  
}

void exit() {
    system("cls");
    
    cout << "Have a holly jolly day";

}

void upmove(int a[SIZE][SIZE]) {
    for (int j = 0; j < SIZE; ++j) {
        int li = 0, ri = j;
        for (int i = 1; i < SIZE; ++i) {
            if (a[i][j] != 0) {
                if (a[i - 1][j] == 0 || a[i - 1][j] == a[i][j]) {
                    if (a[li][ri] == a[i][j]) {
                        a[li][ri] *= 2;
                        a[i][j] = 0;
                    } else {
                        if (a[li][ri] == 0) {
                            a[li][ri] = a[i][j];
                            a[i][j] = 0;
                        } else {
                            a[++li][ri] = a[i][j];
                            a[i][j] = 0;
                        }
                    }
                } else
                    li++;
            }
        }
    }
}
void downmove (int a[SIZE][SIZE]) {
     for (int j = 0; j < SIZE; ++j) {
        int li = SIZE - 1, ri = j;
        for (int i = SIZE - 2; i >= 0; --i) {
            if (a[i][j] != 0) {
                if (a[i + 1][j] == 0 || a[i + 1][j] == a[i][j]) {
                    if (a[li][ri] == a[i][j]) {
                        a[li][ri] *= 2;
                        a[i][j] = 0;
                    } else {
                        if (a[li][ri] == 0) {
                            a[li][ri] = a[i][j];
                            a[i][j] = 0;
                        } else {
                            a[--li][ri] = a[i][j];
                            a[i][j] = 0;
                        }
                    }
                } else
                    li--;
            }
        }
    }

}
void leftmove(int a[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        int li = i, ri = 0;
        for (int j = 1; j < SIZE; ++j) {
            if (a[i][j] != 0) {
                if (a[i][j - 1] == 0 || a[i][j - 1] == a[i][j]) {
                    if (a[li][ri] == a[i][j]) {
                        a[li][ri] *= 2;
                        a[i][j] = 0;
                    } else {
                        if (a[li][ri] == 0) {
                            a[li][ri] = a[i][j];
                            a[i][j] = 0;
                        } else {
                            a[li][++ri] = a[i][j];
                            a[i][j] = 0;
                        }
                    }
                } else
                    ri++;
            }
        }
    }
}
void rightmove(int a[SIZE][SIZE]) {

    for (int i = 0; i < SIZE; ++i) {
        int li = i, ri = SIZE - 1;
        for (int j = SIZE - 2; j >= 0; --j) {
            if (a[i][j] != 0) {
                if (a[i][j + 1] == 0 || a[i][j + 1] == a[i][j]) {
                    if (a[li][ri] == a[i][j]) {
                        a[li][ri] *= 2;
                        a[i][j] = 0;
                    } else {
                        if (a[li][ri] == 0) {
                            a[li][ri] = a[i][j];
                            a[i][j] = 0;
                        } else {
                            a[li][--ri] = a[i][j];
                            a[i][j] = 0;
                        }
                    }
                } else
                    ri--;
            }
        }
    }
}
void addBlock(int a[SIZE][SIZE]) {
    int li, ri;
    srand(static_cast<unsigned>(time(0)));

    while (1) {
        li = rand() % SIZE;
        ri = rand() % SIZE;

        if (a[li][ri] == 0) {
            a[li][ri] = (rand() % 100 < PROBABILITY) ? 2 : 4;
            break;
        }
    }
}

void displayBoard(int a[SIZE][SIZE]) {
    std::cout << "\n\n\t\t2048 GAME\n\n";

    for (int i = 0; i < SIZE; ++i) {
        std::cout << "\t\t\t\t";
        for (int j = 0; j < SIZE; ++j) {
            std::cout << "┌──────";
        }
        std::cout << "┐\n";

        std::cout << "\t\t\t\t";
        for (int j = 0; j < SIZE; ++j) {
            std::cout << "│";
            if (a[i][j] != 0) {
                int numWidth = 6;  // Adjusting the width based on preference
                std::cout << std::setw(numWidth) << std::right << a[i][j];
            } else {
                std::cout << std::setw(6) << " ";
            }
        }
        std::cout << "│\n";
    }

    std::cout << "\t\t\t\t";
    for (int j = 0; j < SIZE; ++j) {
        std::cout << "└──────";
    }
    std::cout << "┘\n";
}

bool isEqual(int tmp[SIZE][SIZE], int a[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (tmp[i][j] != a[i][j])
                return false;

    return true;
}

bool isGameOver(int a[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (a[i][j] == 0)
                return true;

   for (int i = 0; i < SIZE; ++i)
    for (int j = 0; j < SIZE; ++j)
        if ((i < SIZE - 1 && a[i + 1][j] == a[i][j]) || (j < SIZE - 1 && a[i][j + 1] == a[i][j]))
            return true;


    return false;
}
int calculateScore(const int a[SIZE][SIZE]) {
    int highestNumber = 0;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (a[i][j] > highestNumber) {
                highestNumber = a[i][j];
            }
        }
    }

    return highestNumber;
}

void updateLeaderboard(const personalinformation& player) {
    // Insert the player into the leaderboard if their score is higher
    for (int i = 0; i < LEADERBOARD_SIZE; ++i) {
        if (player.score > leaderboard[i].score) {
            
            for (int j = LEADERBOARD_SIZE - 1; j > i; --j) {
                leaderboard[j] = leaderboard[j - 1];
            }
          
            leaderboard[i] = player;

           
            for (int k = 0; k < LEADERBOARD_SIZE - 1; ++k) {
                for (int l = 0; l < LEADERBOARD_SIZE - k - 1; ++l) {
                    if (leaderboard[l].score < leaderboard[l + 1].score) {
                        
                        swap(leaderboard[l], leaderboard[l + 1]);
                    }
                }
            }

            break;
        }
    }
    saveLeaderboard();
}


void displayLeaderboard() {
    cout << "\n\t\t\t\tLEADERBOARD\n";
    cout << "\t\t\t\t-------------\n";

    for (int i = 0; i < LEADERBOARD_SIZE; ++i) {
        cout << "\t\t\t\t" << i + 1 << ". " << setw(20) << left << leaderboard[i].name
             << " - " << leaderboard[i].score << " points\n";
    }

    cout << "\n";
    _getch();
    menu();
}


void saveGame(const int a[SIZE][SIZE], const personalinformation& player) {
    ofstream saveFile(SAVE_FILE);

    if (saveFile.is_open()) {
        // Save player information
        saveFile << player.name << " " << player.lastname << " " << player.score << "\n";

        // Save game board
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                saveFile << a[i][j] << " ";
            }
            saveFile << "\n";
        }

        saveFile.close();
        cout << "Game saved successfully." << endl;
    } else {
        cout << "Unable to save the game." << endl;
    }
}

// Function to load the game state from a file
void loadGame(int a[SIZE][SIZE], personalinformation& player) {
    ifstream saveFile(SAVE_FILE);

    if (saveFile.is_open()) {
        // Load player information
        saveFile >> player.name >> player.lastname >> player.score;

        // Load game board
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                saveFile >> a[i][j];
            }
        }

        saveFile.close();
        cout << "Game loaded successfully." << endl;
    } else {
        cout << "No saved game found." << endl;
    }
}
void loadLeaderboard() {
    ifstream leaderboardFile("leaderboard.txt");

    if (leaderboardFile.is_open()) {
        for (int i = 0; i < LEADERBOARD_SIZE; ++i) {
            leaderboardFile >> leaderboard[i].name >> leaderboard[i].lastname >> leaderboard[i].score;
        }

        leaderboardFile.close();
    }
}
void saveLeaderboard() {
    ofstream leaderboardFile("leaderboard.txt");

    if (leaderboardFile.is_open()) {
        for (int i = 0; i < LEADERBOARD_SIZE; ++i) {
            leaderboardFile << leaderboard[i].name << " " << leaderboard[i].lastname << " " << leaderboard[i].score << "\n";
        }

        leaderboardFile.close();
    }
}
