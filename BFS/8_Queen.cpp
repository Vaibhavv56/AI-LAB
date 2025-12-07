#include <bits/stdc++.h>
using namespace std;

const int N = 8;

/* ===================== STATE STRUCT ===================== */
struct State {
    vector<int> board;               
    vector<vector<int>> path;        
    int g, h;                        
};

/* ===================== PRINT BOARD ===================== */
void printBoard(const vector<int> &b) {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (r < (int)b.size() && b[r] == c)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << "\n";
    }
    cout << "-------------\n";
}

/* =============== SAFETY CHECK =============== */
bool isSafe(int row, int col, const vector<int> &board) {
    for (int r = 0; r < row; r++) {
        int c = board[r];
        if (c == col) return false;
        if (abs(row - r) == abs(col - c)) return false;
    }
    return true;
}

/* =============== HEURISTIC FUNCTIONS =============== */
// Best First & A*: h = remaining queens
int heuristic(const vector<int> &b) { return N - (int)b.size(); }

/* =============== GENERATE NEXT STATES =============== */
vector<vector<int>> expand(const vector<int> &b) {
    vector<vector<int>> children;
    int row = b.size();
    if (row == N) return children;

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col, b)) {
            vector<int> nxt = b;
            nxt.push_back(col);
            children.push_back(nxt);
        }
    }
    return children;
}

/* ===================== BFS ===================== */
void BFS() {
    cout << "\n========== BFS ==========\n";

    queue<State> q;
    int explored = 0;

    State start{{}, {{}} ,0, heuristic({})};
    q.push(start);

    while (!q.empty()) {
        State cur = q.front(); q.pop();
        explored++;

        if (cur.board.size() == N) {
            cout << "States Explored = " << explored << "\n\n";
            cout << "Solution Path:\n";
            for (auto &b : cur.path) printBoard(b);
            return;
        }

        for (auto &child : expand(cur.board)) {
            State s;
            s.board = child;
            s.path = cur.path;
            s.path.push_back(child);
            q.push(s);
        }
    }
}



/* ===================== MAIN ===================== */
int main() {
    BFS();

    return 0;
}
