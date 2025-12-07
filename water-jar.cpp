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

/* ===================== DFS ===================== */
bool DFSUtil(int a, int b, int target,
             unordered_set<string> &vis,
             vector<pair<int,int>> &path,
             vector<pair<int,int>> &traversal) {

    traversal.push_back({a,b});

    if(a == target || b == target) return true;

    vis.insert(encode(a,b));

    for(auto &m : generateMoves(a,b)) {
        if(!vis.count(encode(m.first,m.second))) {
            path.push_back(m);
            if(DFSUtil(m.first,m.second,target,vis,path,traversal))
                return true;
            path.pop_back();
        }
    }
    return false;
}

void DFS(int target) {
    unordered_set<string> vis;
    vector<pair<int,int>> path = {{0,0}};
    vector<pair<int,int>> traversal;

    DFSUtil(0,0,target,vis,path,traversal);

    cout << "\n===== DFS =====\nTraversal:\n";
    for(auto &p:traversal) printState(p.first,p.second);

    cout << "\nSolution Path:\n";
    for(auto &p:path) printState(p.first,p.second);
    cout << "END\n";
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

/* ===================== Best First Search ===================== */
void BestFirst(int target) {
    auto cmp = [&](State &a, State &b){
        return a.h > b.h;
    };

    priority_queue<State, vector<State>, decltype(cmp)> pq(cmp);
    unordered_set<string> vis;
    vector<pair<int,int>> traversal;

    pq.push({0,0,{{0,0}},0,heuristic(0,0,target)});

    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();

        if(vis.count(encode(cur.a,cur.b))) continue;
        vis.insert(encode(cur.a,cur.b));
        traversal.push_back({cur.a,cur.b});

        if(cur.a == target || cur.b == target) {
            cout << "\n===== Best First Search =====\nTraversal:\n";
            for(auto &t:traversal) printState(t.first,t.second);

            cout << "\nSolution Path (with h):\n";
            for(auto &p:cur.path) {
                printState(p.first,p.second);
                cout << "h = " << heuristic(p.first,p.second,target) << "\n-----\n";
            }
            cout << "END\n";
            return;
        }

        for(auto &m : generateMoves(cur.a, cur.b)) {
            auto p = cur.path;
            p.push_back(m);
            pq.push({m.first,m.second,p,0,heuristic(m.first,m.second,target)});
        }
    }
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

    BFS(target);
    DFS(target);
    DLS(target, 3);
    BestFirst(target);
    AStar(target);

    return 0;
}