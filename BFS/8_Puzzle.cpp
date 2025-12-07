#include <bits/stdc++.h>
using namespace std;

using Board = vector<vector<int>>;

struct State {
    Board board;
    vector<Board> path;
    int g, h;
};

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

/* ----------------- Utilities ----------------- */
void printBoard(const Board &b) {
    for (auto &r : b) {
        for (int x : r) cout << x << " ";
        cout << "\n";
    }
    cout << "------\n";
}

string toString(const Board &b) {
    string s;
    for (auto &r : b)
        for (int x : r)
            s += char(x + '0');
    return s;
}

pair<int,int> findZero(const Board &b) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[i][j] == 0)
                return {i, j};
    return {-1, -1};
}


/* ===================== BFS ===================== */
void BFS(Board start, Board goal) {
    queue<State> q;
    unordered_set<string> visited;
    vector<Board> traversal, solution;

    q.push({start, {start}, 0, 0});
    visited.insert(toString(start));
    int count = 0;

    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        count++;
        traversal.push_back(cur.board);

        if (cur.board == goal) {
            solution = cur.path;
            break;
        }

        auto [x,y] = findZero(cur.board);
        for (int k = 0; k < 4; k++) {
            int nx=x+dx[k], ny=y+dy[k];
            if(nx>=0 && ny>=0 && nx<3 && ny<3) {
                Board nxt = cur.board;
                swap(nxt[x][y], nxt[nx][ny]);
                string key = toString(nxt);
                if(!visited.count(key)) {
                    visited.insert(key);
                    auto p = cur.path;
                    p.push_back(nxt);
                    q.push({nxt, p, 0, 0});
                }
            }
        }
    }

    cout << "\n===== BFS =====\n";
    cout << "States Traversed: " << count << "\n\nTraversal:\n";
    for(auto &b : traversal) printBoard(b);
    cout << "Shortest Path:\n";
    for(auto &b : solution) printBoard(b);
}



/* ===================== MAIN ===================== */
int main() {
    Board start = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };
    Board goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    BFS(start,goal);


    return 0;
}
