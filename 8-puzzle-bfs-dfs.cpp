#include <bits/stdc++.h>
using namespace std;

using Board = vector<vector<int>>;

struct State {
    Board board;
    vector<Board> path;
};

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

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

/* ======================= BFS ======================= */
void BFS(Board start, Board goal) {
    queue<State> q;
    unordered_set<string> visited;
    vector<Board> traversal;
    vector<Board> shortestPath;

    q.push({start, {start}});
    visited.insert(toString(start));

    int cnt = 0;

    while (!q.empty()) {
        State curr = q.front(); q.pop();
        cnt++;
        traversal.push_back(curr.board);

        if (curr.board == goal) {
            shortestPath = curr.path;
            break;
        }

        auto [x, y] = findZero(curr.board);

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && ny >= 0 && nx < 3 && ny < 3) {
                Board next = curr.board;
                swap(next[x][y], next[nx][ny]);

                if (!visited.count(toString(next))) {
                    visited.insert(toString(next));
                    auto newPath = curr.path;
                    newPath.push_back(next);
                    q.push({next, newPath});
                }
            }
        }
    }

    cout << "\n===== BFS =====\n";
    cout << "TOTAL STATES EXPLORED: " << cnt << "\n";

    cout << "\nBFS TRAVERSAL:\n";
    for (auto &b : traversal)
        printBoard(b);

    cout << "\nBFS SHORTEST PATH:\n";
    for (auto &b : shortestPath)
        printBoard(b);
}

/* ======================= DFS ======================= */
bool DFSUtil(Board curr, Board goal,
             unordered_set<string> &visited,
             vector<Board> &traversal,
             vector<Board> &solutionPath,
             int depth,
             int &cnt) {

    cnt++;
    traversal.push_back(curr);

    if (curr == goal)
        return true;

    if (depth == 0)
        return false;

    visited.insert(toString(curr));
    auto [x, y] = findZero(curr);

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx >= 0 && ny >= 0 && nx < 3 && ny < 3) {
            Board next = curr;
            swap(next[x][y], next[nx][ny]);

            if (!visited.count(toString(next))) {
                solutionPath.push_back(next);
                if (DFSUtil(next, goal, visited, traversal, solutionPath, depth - 1, cnt))
                    return true;
                solutionPath.pop_back();
            }
        }
    }
    return false;
}

void DFS(Board start, Board goal) {
    unordered_set<string> visited;
    vector<Board> traversal;
    vector<Board> solutionPath = {start};

    int cnt = 0;
    DFSUtil(start, goal, visited, traversal, solutionPath, 20, cnt);

    cout << "\n===== DFS =====\n";
    cout << "TOTAL STATES EXPLORED: " << cnt << "\n";

    cout << "\nDFS TRAVERSAL:\n";
    for (auto &b : traversal)
        printBoard(b);

    cout << "\nDFS SOLUTION PATH:\n";
    for (auto &b : solutionPath)
        printBoard(b);
}

/* ======================= MAIN ======================= */
int main() {
    Board start = {
        {1, 2, 3},
        {4, 0, 5},
        {6, 7, 8}
    };

    Board goal = {
        {1, 2, 3},
        {4, 5, 0},
        {6, 7, 8}
    };

    BFS(start, goal);
    DFS(start, goal);

    return 0;
}
