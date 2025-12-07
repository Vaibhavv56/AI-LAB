#include <bits/stdc++.h>
using namespace std;

struct State {
    int a, b;
    vector<pair<int,int>> path;
    int g, h;
};

int CAP1 = 4;   // Jug1 capacity
int CAP2 = 3;   // Jug2 capacity

void printState(int a, int b) {
    cout << "(" << a << "," << b << ")\n";
}

string encode(int a, int b) {
    return to_string(a) + "," + to_string(b);
}

int heuristic(int a, int b, int target) {
    return min(abs(a - target), abs(b - target));
}

vector<pair<int,int>> generateMoves(int a, int b) {
    vector<pair<int,int>> moves;

    moves.push_back({CAP1, b});
    moves.push_back({a, CAP2});
    moves.push_back({0, b});
    moves.push_back({a, 0});

    int pour = min(a, CAP2 - b);
    moves.push_back({a - pour, b + pour});

    pour = min(b, CAP1 - a);
    moves.push_back({a + pour, b - pour});

    return moves;
}

/* ===================== BFS ===================== */
void BFS(int target) {
    queue<State> q;
    unordered_set<string> vis;
    vector<pair<int,int>> traversal;

    State start = {0,0, {{0,0}}, 0,0};
    q.push(start);
    vis.insert(encode(0,0));

    while(!q.empty()) {
        auto cur = q.front(); q.pop();

        traversal.push_back({cur.a, cur.b});

        if (cur.a == target || cur.b == target) {
            cout << "\n===== BFS =====\n";
            cout << "Traversal:\n";
            for(auto &t:traversal) printState(t.first,t.second);

            cout << "\nSolution Path:\n";
            for(auto &p:cur.path) printState(p.first,p.second);
            cout << "END\n";
            return;
        }

        for(auto &m : generateMoves(cur.a, cur.b)) {
            if(!vis.count(encode(m.first,m.second))) {
                vis.insert(encode(m.first,m.second));
                auto p = cur.path;
                p.push_back(m);
                q.push({m.first,m.second,p,0,0});
            }
        }
    }
}

int main() {
    int target;
    cout << "Enter target amount: ";
    cin >> target;

    BFS(target);

    return 0;
}
