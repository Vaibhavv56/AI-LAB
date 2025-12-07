#include <bits/stdc++.h>
using namespace std;

const int N = 8;
int board[N];
int stateCount = 0;

/* ================= PRINT CURRENT STATE ================= */
void printState(int uptoRow) {
    cout << "\nState " << ++stateCount << ":\n";
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (r <= uptoRow && board[r] == c)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << "\n";
    }
}

/* ================= PRINT FINAL SOLUTION ================= */
void printSolution() {
    cout << "\n===== FINAL SOLUTION =====\n";
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            cout << (board[r] == c ? "Q " : ". ");
        }
        cout << "\n";
    }
}

/* ================= CONSTRAINT CHECK ================= */
bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col) return false;                       // same column
        if (abs(board[i] - col) == abs(i - row)) return false;   // diagonal
    }
    return true;
}

/* ================= CSP BACKTRACKING ================= */
bool solveCSP(int row) {

    if (row == N)
        return true;   // all queens placed

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row] = col;     // assign
            printState(row);      // print every state explored

            if (solveCSP(row + 1))
                return true;
        }
    }
    return false;  // backtrack
}

/* ================= MAIN ================= */
int main() {
    if (solveCSP(0)) {
        printSolution();
    } else {
        cout << "No solution found\n";
    }

    cout << "\nTotal States Explored = " << stateCount << endl;
    return 0;
}
