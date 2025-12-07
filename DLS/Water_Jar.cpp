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

/* ===================== DLS ===================== */
bool DLSUtil(int a, int b, int target, int limit,
             unordered_set<string> &vis,
             vector<pair<int,int>> &path,
             vector<pair<int,int>> &traversal) {

    traversal.push_back({a,b});

    if(a == target || b == target) return true;
    if(limit == 0) return false;

    vis.insert(encode(a,b));

    for(auto &m : generateMoves(a,b)) {
        if(!vis.count(encode(m.first,m.second))) {
            path.push_back(m);
            if(DLSUtil(m.first,m.second,target,limit-1,vis,path,traversal))
                return true;
            path.pop_back();
        }
    }

    return false;
}

void DLS(int target, int limit) {
    unordered_set<string> vis;
    vector<pair<int,int>> path = {{0,0}};
    vector<pair<int,int>> traversal;

    cout << "\n===== DLS (Limit = " << limit << ") =====\n";

    if(DLSUtil(0,0,target,limit,vis,path,traversal)) {
        cout << "Traversal:\n";
        for(auto &p:traversal) printState(p.first,p.second);

        cout << "\nSolution Path:\n";
        for(auto &p:path) printState(p.first,p.second);
        cout << "END\n";
    } else {
        cout << "Goal Not Found\nTraversal:\n";
        for(auto &p:traversal) printState(p.first,p.second);
    }
}


/* ===================== MAIN ===================== */
int main() {
    int target;
    cout << "Enter target amount: ";
    cin >> target;

    DLS(target, 3);


    return 0;
}
