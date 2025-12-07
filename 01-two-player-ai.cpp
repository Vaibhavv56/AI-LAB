//ai
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> board(9, 2);
int userSymbol, aiSymbol;

void printboard();
void userMove();
int checkWinner();
bool isMovesLeft();
int minimax(bool isMaximizing);
int findBestMove();

int main() {
    cout << "For X: 3 and for O: 5\n";
    cout << "Choose your symbol (3 for X / 5 for O): ";
    cin >> userSymbol;

    aiSymbol = (userSymbol == 3) ? 5 : 3;

    printboard();

    while (true) {
        userMove();
        printboard();

        if (checkWinner() == userSymbol) {
            cout << "\nYou win!!\n";
            break;
        }
        if (!isMovesLeft()) {
            cout << "\nIt's a draw!\n";
            break;
        }

        cout << "\nComputer's move:\n";
        int bestMove = findBestMove();
        board[bestMove] = aiSymbol;
        printboard();

        if (checkWinner() == aiSymbol) {
            cout << "\nComputer wins!!\n";
            break;
        }
        if (!isMovesLeft()) {
            cout << "\nIt's a draw!\n";
            break;
        }
    }
    return 0;
}

void userMove() {
    int move;
    do {
        cout << "Enter your move (0 to 8): ";
        cin >> move;
    } while (move < 0 || move > 8 || board[move] != 2);

    board[move] = userSymbol;
}

void printboard() {
    for (int i = 0; i < 9; i++) {
        char c = (board[i] == 3) ? 'X' : (board[i] == 5) ? 'O' : ' ';
        cout << " " << c << " ";
        if (i % 3 != 2) cout << "|";
        if (i % 3 == 2 && i != 8) cout << "\n---+---+---\n";
    }
    cout << "\n\n";
}

int checkWinner() {
    int lines[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };

    for (auto &l : lines) {
        if (board[l[0]] != 2 &&
            board[l[0]] == board[l[1]] &&
            board[l[1]] == board[l[2]])
            return board[l[0]];
    }
    return 0;
}

bool isMovesLeft() {
    for (int i : board)
        if (i == 2) return true;
    return false;
}

int minimax(bool isMaximizing) {
    int winner = checkWinner();
    if (winner == aiSymbol) return 10;
    if (winner == userSymbol) return -10;
    if (!isMovesLeft()) return 0;

    if (isMaximizing) {
        int best = INT_MIN;
        for (int i = 0; i < 9; i++) {
            if (board[i] == 2) {
                board[i] = aiSymbol;
                best = max(best, minimax(false)); //recursion
                board[i] = 2;  //reset
            }
        }
        return best;
    }

    int best = INT_MAX;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 2) {
            board[i] = userSymbol;
            best = min(best, minimax(true));
            board[i] = 2;
        }
    }
    return best;
}

int findBestMove() {
    int bestVal = INT_MIN;
    int bestMove = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] == 2) {
            board[i] = aiSymbol;
            int moveVal = minimax(false);
            board[i] = 2;
            if (moveVal > bestVal) {
                bestVal = moveVal;
                bestMove = i;
            }
        }
    }
    return bestMove;
}




//non-ai
#include <iostream>
#include <vector>
using namespace std;

vector<int> board(9, 2);  
int turn = 1;

void user(int q);
void printboard();
void play(int turn);
void Go(int n);
int make2();
int Posswin(int p);
int checkWinner();

int main() {
    int q;
    int winner = 0;

    cout << "For X: 3 and for O: 5\n";
    cout << "Choose your symbol (3 for X / 5 for O): ";
    cin >> q;

    for (int i = 0; i <= 9; i++) {
        if (turn % 2 == 1) {
            // Computer's turn
            cout << "\nTurn = " << turn << " (Computer's move)\n";
            play(turn);
            printboard();

            winner = checkWinner();
            if (winner != 0) {
                if (winner == q)
                    cout << "\nYou win!!" << endl;
                else
                    cout << "\nComputer wins!!" << endl;
                break;
            }
            turn++;
        } else {
            if (turn == 10) break;

            // User's turn
            user(q);
            cout << "\nTurn = " << turn << " (Your move)\n";
            printboard();

            winner = checkWinner();
            if (winner != 0) {
                if (winner == q)
                    cout << "\nYou win!!" << endl;
                else
                    cout << "\nComputer wins!!" << endl;
                break;
            }
            turn++;
        }
    }

    if (winner == 0) {
        cout << "\nIt's a draw!" << endl;
    }

    return 0;
}

void user(int q) {
    int move;
    cout << "Enter your move (0 to 8): ";
    cin >> move;

    if (move >= 0 && move < 9 && board[move] == 2) {
        board[move] = q;
    } else {
        cout << "Invalid move. Try again.\n";
        user(q);
    }
}

void printboard() {
    for (int i = 0; i < 9; ++i) {
        char cell = ' ';
        if (board[i] == 3) cell = 'X';
        else if (board[i] == 5) cell = 'O';

        cout << " " << cell << " ";

        if ((i + 1) % 3 != 0)
            cout << "|";
        else if (i != 8)
            cout << "\n---+---+---\n";
    }
    cout << "\n";
}

int make2() {
    if (board[4] == 2)
        return 4;
    return 1;
}

void Go(int n) {
    if (turn % 2 == 0)
        board[n] = 5;  
    else
        board[n] = 3;
}

int Posswin(int p) {
    int winProd = (p == 3) ? 18 : 50;
    int lines[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };

    for (int i = 0; i < 8; ++i) {
        int prod = board[lines[i][0]] * board[lines[i][1]] * board[lines[i][2]];
        if (prod == winProd) {
            for (int j = 0; j < 3; ++j) {
                if (board[lines[i][j]] == 2)
                    return lines[i][j];
            }
        }
    }
    return 0;
}

int checkWinner() {
    int lines[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };

    for (int i = 0; i < 8; ++i) {
        int a = board[lines[i][0]];
        int b = board[lines[i][1]];
        int c = board[lines[i][2]];
        if (a == b && b == c && a != 2)
            return a;
    }
    return 0;
}

void play(int turn) {
    if (turn == 1) {
        Go(0);
    } else if (turn == 2) {
        if (board[4] == 2) Go(4);
        else Go(0);
    } else if (turn == 3) {
        if (board[8] == 2) Go(8);
        else Go(2);
    } else if (turn == 4) {
        int pos = Posswin(3);
        if (pos != 0) Go(pos);
        else Go(make2());
    } else if (turn == 5) {
        int pos = Posswin(3);
        if (pos != 0) Go(pos);
        else if ((pos = Posswin(5)) != 0) Go(pos);
        else if (board[6] == 2) Go(6);
        else Go(2);
    } else if (turn == 6) {
        int pos = Posswin(5);
        if (pos != 0) Go(pos);
        else if ((pos = Posswin(3)) != 0) Go(pos);
        else Go(make2());
    } else if (turn >= 7 && turn <= 9) {
        int pos = Posswin(5);
        if (pos != 0) Go(pos);
        else if ((pos = Posswin(3)) != 0) Go(pos);
        else {
            for (int i = 0; i < 9; ++i) {
                if (board[i] == 2) {
                    Go(i);
                    break;
                }
            }
        }
    }
}
