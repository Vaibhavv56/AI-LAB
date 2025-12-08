#include <bits/stdc++.h>
using namespace std;

const int N = 4;     // number of vertices
const int M = 3;     // number of colors

//adjacency matrix
int graph[N][N] = {
    {0, 1, 1, 1},
    {1, 0, 1, 0},
    {1, 1, 0, 1},
    {1, 0, 1, 0}
};

int color[N];        // color[i] = color index of vertex i
int states = 0;

string colorName[M+1] = {"", "Red", "Green", "Blue"};

/* ================= PRINT CURRENT STATE ================= */
void printState(int uptoVertex) {
    cout << "State " << states << ": ";
    for (int i = 0; i <= uptoVertex; i++) {
        cout << "V" << i << "=" << colorName[color[i]] << "  ";
    }
    cout << endl;
}

/* ================= SAFETY CHECK ================= */
bool isSafe(int v, int c) {
    for (int i = 0; i < N; i++) {
        if (graph[v][i] && color[i] == c)
            return false;
    }
    return true;
}

/* ================= BACKTRACKING ================= */
bool solve(int v) {
    states++;

    if (v == N)
        return true;

    for (int c = 1; c <= M; c++) {
        if (isSafe(v, c)) {
            color[v] = c;
            printState(v);     // PRINT TRAVERSAL STATE

            if (solve(v + 1))
                return true;
            //backtracking step
            color[v] = 0;      // BACKTRACK
        }
    }
    return false;
}

/* ================= PRINT FINAL SOLUTION ================= */
void printSolution() {
    cout << "\n===== FINAL SOLUTION =====\n";
    for (int i = 0; i < N; i++) {
        cout << "Vertex " << i << " -> " << colorName[color[i]] << endl;
    }
}

/* ================= MAIN ================= */
int main() {
    memset(color, 0, sizeof(color));

    if (solve(0)) {
        printSolution();
    } else {
        cout << "No solution exists\n";
    }

    cout << "\nTotal States Explored = " << states << endl;
    return 0;
}
