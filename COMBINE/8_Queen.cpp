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

/* ===================== DFS ===================== */
bool DFSUtil(State cur, vector<vector<int>> &path, int &explored) {
    explored++;

    if (cur.board.size() == N) return true;

    for (auto &child : expand(cur.board)) {
        path.push_back(child);
        if (DFSUtil({child, path, 0, 0}, path, explored)) return true;
        path.pop_back();
    }
    return false;
}

void DFS() {
    cout << "\n========== DFS ==========\n";

    vector<vector<int>> path = {{}};
    int explored = 0;
    DFSUtil({{}, path, 0, 0}, path, explored);

    cout << "States Explored = " << explored << "\n\n";
    cout << "Solution Path:\n";
    for (auto &b : path) printBoard(b);
}

/* ===================== DLS ===================== */
bool DLSUtil(State cur, int limit, vector<vector<int>> &path, int &explored) {
    explored++;

    if (cur.board.size() == N) return true;
    if (limit == 0) return false;

    for (auto &child : expand(cur.board)) {
        path.push_back(child);
        if (DLSUtil({child, path, 0, 0}, limit - 1, path, explored))
            return true;
        path.pop_back();
    }
    return false;
}

void DLS(int limit) {
    cout << "\n========== DLS (limit=" << limit << ") ==========\n";

    vector<vector<int>> path = {{}};
    int explored = 0;

    if (DLSUtil({{}, path, 0, 0}, limit, path, explored)) {
        cout << "States Explored = " << explored << "\n\n";
        cout << "Solution Path:\n";
        for (auto &b : path) printBoard(b);
    } else {
        cout << "Goal NOT found\n";
        cout << "States Explored = " << explored << "\n";
    }
}

/* ===================== BEST FIRST SEARCH ===================== */
void BestFirst() {
    cout << "\n========== Best First Search ==========\n";

    auto cmp = [&](State &a, State &b) { return a.h > b.h; };
    priority_queue<State, vector<State>, decltype(cmp)> pq(cmp);

    pq.push({{}, {{}}, 0, heuristic({})});
    int explored = 0;

    while (!pq.empty()) {
        State cur = pq.top(); pq.pop();
        explored++;

        if (cur.board.size() == N) {
            cout << "States Explored = " << explored << "\n\n";
            cout << "Solution Path (with h):\n";
            for (auto &b : cur.path) {
                printBoard(b);
                cout << "h = " << heuristic(b) << "\n\n";
            }
            return;
        }

        for (auto &child : expand(cur.board)) {
            auto p = cur.path;
            p.push_back(child);
            pq.push({child, p, 0, heuristic(child)});
        }
    }
}

/* ===================== A* SEARCH ===================== */
void AStar() {
    cout << "\n========== A* Search ==========\n";

    auto cmp = [&](State &a, State &b) {
        return (a.g + a.h) > (b.g + b.h);
    };

    priority_queue<State, vector<State>, decltype(cmp)> pq(cmp);
    int explored = 0;

    pq.push({{}, {{}}, 0, heuristic({})});

    while (!pq.empty()) {
        State cur = pq.top(); pq.pop();
        explored++;

        if (cur.board.size() == N) {
            cout << "States Explored = " << explored << "\n\n";
            cout << "Solution Path (g,h,f):\n";

            int g = 0;
            for (auto &b : cur.path) {
                int h = heuristic(b);
                printBoard(b);
                cout << "g = " << g << ", h = " << h << ", f = " << g + h << "\n\n";
                g++;
            }
            return;
        }

        for (auto &child : expand(cur.board)) {
            auto p = cur.path;
            p.push_back(child);
            pq.push({child, p, cur.g + 1, heuristic(child)});
        }
    }
}

/* ===================== MAIN ===================== */
int main() {
    BFS();
    DFS();
    DLS(3);
    BestFirst();
    AStar();
    return 0;
}
