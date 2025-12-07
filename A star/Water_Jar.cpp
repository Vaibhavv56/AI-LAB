#include <bits/stdc++.h>
using namespace std;

struct State {
    int a, b;
    vector<pair<int,int>> path;
    int g, h;
};

int CAP1 = 4;   // Jug1 capacity
int CAP2 = 3;   // Jug2 capacity

/* ---------------- Utility Functions ---------------- */
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

    // Fill jug1
    moves.push_back({CAP1, b});
    // Fill jug2
    moves.push_back({a, CAP2});
    // Empty jug1
    moves.push_back({0, b});
    // Empty jug2
    moves.push_back({a, 0});

    // Pour jug1 -> jug2
    int pour = min(a, CAP2 - b);
    moves.push_back({a - pour, b + pour});

    // Pour jug2 -> jug1
    pour = min(b, CAP1 - a);
    moves.push_back({a + pour, b - pour});

    return moves;
}

/* ===================== A* Search ===================== */
void AStar(int target) {
    auto cmp = [&](State &a, State &b){
        return (a.g + a.h) > (b.g + b.h);
    };

    priority_queue<State, vector<State>, decltype(cmp)> pq(cmp);
    unordered_set<string> closed;
    vector<pair<int,int>> traversal;

    pq.push({0,0,{{0,0}},0,heuristic(0,0,target)});

    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();

        if(closed.count(encode(cur.a,cur.b))) continue;
        closed.insert(encode(cur.a,cur.b));
        traversal.push_back({cur.a,cur.b});

        if(cur.a == target || cur.b == target) {
            cout << "\n===== A* Search =====\nTraversal:\n";
            for(auto &t:traversal) printState(t.first,t.second);

            cout << "\nOptimal Path (g,h,f):\n";

            int g = 0;
            for(auto &p:cur.path) {
                int h = heuristic(p.first,p.second,target);
                cout << "(" << p.first << "," << p.second << ")\n";
                cout << "g = " << g << ", h = " << h << ", f = " << g+h << "\n-----\n";
                g++;
            }
            cout << "END\n";
            return;
        }

        int a = cur.a, b = cur.b;

        for(auto &m : generateMoves(a,b)) {
            auto p = cur.path;
            p.push_back(m);
            pq.push({m.first,m.second,p,cur.g+1,heuristic(m.first,m.second,target)});
        }
    }
}

/* ===================== MAIN ===================== */
int main() {
    int target;
    cout << "Enter target amount: ";
    cin >> target;

    AStar(target);

    return 0;
}
