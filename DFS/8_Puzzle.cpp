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


/* ===================== DFS ===================== */
bool DFSUtil(Board cur, Board goal, unordered_set<string> &vis,
             vector<Board> &path, int &count) {
    count++;
    if(cur == goal) return true;
    vis.insert(toString(cur));

    auto [x,y] = findZero(cur);
    for(int k=0;k<4;k++) {
        int nx=x+dx[k], ny=y+dy[k];
        if(nx>=0 && ny>=0 && nx<3 && ny<3) {
            Board nxt = cur;
            swap(nxt[x][y], nxt[nx][ny]);
            if(!vis.count(toString(nxt))) {
                path.push_back(nxt);
                if(DFSUtil(nxt, goal, vis, path, count))
                    return true;
                path.pop_back();
            }
        }
    }
    return false;
}

void DFS(Board start, Board goal) {
    unordered_set<string> vis;
    vector<Board> path = {start};
    int count = 0;

    DFSUtil(start, goal, vis, path, count);

    cout << "\n===== DFS =====\n";
    cout << "States Traversed: " << count << "\n\nSolution Path:\n";
    for(auto &b : path) printBoard(b);
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

    DFS(start,goal);
   

    return 0;
}
