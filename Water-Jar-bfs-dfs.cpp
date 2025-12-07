#include <bits/stdc++.h>
using namespace std;

struct State {
    int jug1, jug2;
    vector<pair<int,int>> path;
};

void printPath(const vector<pair<int,int>>& path) {
    for (auto &p : path) {
        cout << "(" << p.first << ", " << p.second << ") -> ";
    }
    cout << "Goal Reached\n";
}

void BFS(int cap1, int cap2, int target) {
    queue<State> q;
    set<pair<int,int>> visited;

    q.push({0, 0, {{0, 0}}});
    visited.insert({0, 0});

    cout << "BFS Traversal:\n";

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        int x = curr.jug1;
        int y = curr.jug2;

        cout << "(" << x << ", " << y << ") ";

        if (x == target || y == target) {
            cout << "\n\nBFS Shortest Path:\n";
            printPath(curr.path);
            return;
        }

        vector<pair<int,int>> nextStates = {
            {cap1, y},
            {x, cap2},
            {0, y},
            {x, 0},
            {max(0, x - (cap2 - y)), min(cap2, x + y)},
            {min(cap1, x + y), max(0, y - (cap1 - x))}
        };

        for (auto &ns : nextStates) {
            if (!visited.count(ns)) {
                visited.insert(ns);
                auto newPath = curr.path;
                newPath.push_back(ns);
                q.push({ns.first, ns.second, newPath});
            }
        }
    }

    cout << "\nNo solution found using BFS.\n";
}

bool DFSUtil(int cap1, int cap2, int target,
             pair<int,int> state,
             set<pair<int,int>> &visited,
             vector<pair<int,int>> &path) {

    cout << "(" << state.first << ", " << state.second << ") ";

    if (state.first == target || state.second == target) {
        cout << "\n\nDFS Solution Path:\n";
        printPath(path);
        return true;
    }

    visited.insert(state);

    vector<pair<int,int>> nextStates = {
        {cap1, state.second},
        {state.first, cap2},
        {0, state.second},
        {state.first, 0},
        {max(0, state.first - (cap2 - state.second)),
         min(cap2, state.first + state.second)},
        {min(cap1, state.first + state.second),
         max(0, state.second - (cap1 - state.first))}
    };

    for (auto &ns : nextStates) {
        if (!visited.count(ns)) {
            path.push_back(ns);
            if (DFSUtil(cap1, cap2, target, ns, visited, path))
                return true;
            path.pop_back();
        }
    }
    return false;
}


void DFS(int cap1, int cap2, int target) {
    set<pair<int,int>> visited;
    vector<pair<int,int>> path = {{0,0}};
    if (!DFSUtil(cap1, cap2, target, {0,0}, visited, path)) {
        cout << "No solution found using DFS.\n";
    }
}

int main() {
    int cap1 = 4, cap2 = 3, target = 2;
    BFS(cap1, cap2, target);
    DFS(cap1, cap2, target);
    return 0;
}

