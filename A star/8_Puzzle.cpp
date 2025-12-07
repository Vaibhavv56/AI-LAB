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

// Manhattan distance heuristic
int heuristic(const Board &b, const Board &goal) {
    int h = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == 0) continue;
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    if (goal[x][y] == b[i][j])
                        h += abs(i - x) + abs(j - y);
        }
    return h;
}


/* ===================== A* ===================== */
void AStar(Board start, Board goal) {
    auto cmp = [](State &a, State &b){
        return (a.g + a.h) > (b.g + b.h);
    };
    priority_queue<State, vector<State>, decltype(cmp)> pq(cmp);
    unordered_set<string> closed;
    vector<Board> traversal;

    pq.push({start, {start}, 0, heuristic(start,goal)});
    int count = 0;

    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        string key = toString(cur.board);
        if(closed.count(key)) continue;

        closed.insert(key);
        traversal.push_back(cur.board);
        count++;

        if(cur.board == goal) {
            cout << "\n===== A* Search =====\n";
            cout << "States Traversed: " << count << "\n\nTraversal:\n";
            for(auto &b:traversal) printBoard(b);

            cout << "Optimal Path (with g, h, f):\n";
            int g = 0;
            for(auto &b:cur.path) {
                printBoard(b);
                int h = heuristic(b, goal);
                int f = g + h;
                cout << "g = " << g << ", h = " << h << ", f = " << f << "\n";
                cout << "------\n";
                g++; // cost per move = 1
            }
            return;
        }

        auto [x,y] = findZero(cur.board);
        for(int k=0;k<4;k++) {
            int nx=x+dx[k], ny=y+dy[k];
            if(nx>=0 && ny>=0 && nx<3 && ny<3) {
                Board nxt = cur.board;
                swap(nxt[x][y], nxt[nx][ny]);
                auto p = cur.path;
                p.push_back(nxt);
                pq.push({nxt, p, cur.g+1, heuristic(nxt,goal)});
            }
        }
    }
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

    AStar(start,goal);

    return 0;
}
