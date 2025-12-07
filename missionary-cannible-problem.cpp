#include <bits/stdc++.h>
using namespace std;

/*
STATE FORMAT:
(M_left, C_left, boat_side)
boat_side = 0 → boat on LEFT bank
boat_side = 1 → boat on RIGHT bank
*/

struct State {
    int M, C, B;   // left missionaries, left cannibals, boat side
    vector<tuple<int,int,int>> path;
    int g, h;
};

/* ------------------ Utility Functions ------------------ */
void printState(const tuple<int,int,int> &s) {
    cout << "(M=" << get<0>(s)
         << ", C=" << get<1>(s)
         << ", B=" << get<2>(s) << ")\n";
}

string encode(int M, int C, int B) {
    return to_string(M) + "," + to_string(C) + "," + to_string(B);
}

/* ------------------ Validity Check ------------------ */
bool isValid(int M, int C, int B) {
    if (M < 0 || M > 3 || C < 0 || C > 3) return false;

    int M_r = 3 - M;
    int C_r = 3 - C;

    if (M > 0 && C > M) return false;     // left side rule
    if (M_r > 0 && C_r > M_r) return false; // right side rule

    return true;
}

/* ------------------ Moves Generator ------------------ */
vector<tuple<int,int,int>> getMoves(int M, int C, int B) {
    vector<tuple<int,int,int>> moves;

    // POSSIBLE ACTIONS (1 or 2 people in boat)
    vector<pair<int,int>> actions = {
        {1,0}, {2,0}, {0,1}, {0,2}, {1,1}
    };

    // Boat direction:
    // If boat is on left (B=0), subtract.
    // If boat is on right (B=1), add.
    int dir = (B == 0 ? -1 : 1);

    for (auto &act : actions) {
        int m = act.first;
        int c = act.second;
  

        int nM = M + dir * m;
        int nC = C + dir * c;
        int nB = 1 - B;

        if (isValid(nM, nC, nB))
            moves.push_back({nM, nC, nB});
    }

    return moves;
}

/* ------------------ Heuristic Function ------------------ */
int heuristic(int M, int C, int B) {
    return M + C;   // # of people still left on starting side
}

/* ========================= BFS ========================= */
void BFS() {
    queue<State> q;
    unordered_set<string> vis;
    vector<tuple<int,int,int>> traversal;

    State start = {3,3,0, {{3,3,0}}, 0, 0};
    q.push(start);
    vis.insert(encode(3,3,0));

    while (!q.empty()) {
        auto cur = q.front(); q.pop();

        traversal.push_back({cur.M,cur.C,cur.B});

        if (cur.M == 0 && cur.C == 0 && cur.B == 1) {
            cout << "\n===== BFS =====\nTraversal:\n";
            for (auto &t : traversal) printState(t);

            cout << "\nSolution Path:\n";
            for (auto &p : cur.path) printState(p);
            cout << "END\n";
            return;
        }

        for (auto &mv : getMoves(cur.M,cur.C,cur.B)) {
            int M = get<0>(mv), C = get<1>(mv), B = get<2>(mv);
            string key = encode(M,C,B);

            if (!vis.count(key)) {
                vis.insert(key);
                auto p = cur.path;
                p.push_back(mv);
                q.push({M,C,B,p,0,0});
            }
        }
    }
}

/* ========================= DFS ========================= */
bool DFSUtil(State cur,
             unordered_set<string> &vis,
             vector<tuple<int,int,int>> &traversal,
             vector<tuple<int,int,int>> &path)
{
    traversal.push_back({cur.M,cur.C,cur.B});

    if (cur.M == 0 && cur.C == 0 && cur.B == 1)
        return true;

    vis.insert(encode(cur.M,cur.C,cur.B));

    for (auto &mv : getMoves(cur.M,cur.C,cur.B)) {
        int M = get<0>(mv), C = get<1>(mv), B = get<2>(mv);

        if (!vis.count(encode(M,C,B))) {
            path.push_back(mv);

            if (DFSUtil({M,C,B,path,0,0}, vis, traversal, path))
                return true;

            path.pop_back();
        }
    }
    return false;
}

void DFS() {
    unordered_set<string> vis;
    vector<tuple<int,int,int>> path = {{3,3,0}};
    vector<tuple<int,int,int>> traversal;

    DFSUtil({3,3,0,path,0,0}, vis, traversal, path);

    cout << "\n===== DFS =====\nTraversal:\n";
    for (auto &t : traversal) printState(t);

    cout << "\nSolution Path:\n";
    for (auto &p : path) printState(p);
    cout << "END\n";
}

/* =================== Depth Limited Search =================== */
bool DLSUtil(State cur, int limit,
             unordered_set<string> &vis,
             vector<tuple<int,int,int>> &traversal,
             vector<tuple<int,int,int>> &path)
{
    traversal.push_back({cur.M,cur.C,cur.B});

    if (cur.M == 0 && cur.C == 0 && cur.B == 1)
        return true;

    if (limit == 0)
        return false;

    vis.insert(encode(cur.M,cur.C,cur.B));

    for (auto &mv : getMoves(cur.M,cur.C,cur.B)) {
        int M = get<0>(mv), C = get<1>(mv), B = get<2>(mv);

        if (!vis.count(encode(M,C,B))) {
            path.push_back(mv);

            if (DLSUtil({M,C,B,path,0,0}, limit - 1, vis, traversal, path))
                return true;

            path.pop_back();
        }
    }
    return false;
}

void DLS(int limit) {
    unordered_set<string> vis;
    vector<tuple<int,int,int>> path = {{3,3,0}};
    vector<tuple<int,int,int>> traversal;

    cout << "\n===== DLS (Limit = " << limit << ") =====\n";

    if (DLSUtil({3,3,0,path,0,0}, limit, vis, traversal, path)) {
        cout << "Traversal:\n";
        for (auto &t : traversal) printState(t);

        cout << "\nSolution Path:\n";
        for (auto &p : path) printState(p);
        cout << "END\n";
    } else {
        cout << "Goal NOT found.\nTraversal:\n";
        for (auto &t : traversal) printState(t);
    }
}

/* ========================= Best First Search ========================= */
void BestFirst() {
    auto cmp = [&](State &a, State &b) {
        return a.h > b.h;
    };

    priority_queue<State, vector<State>, decltype(cmp)> pq(cmp);
    unordered_set<string> vis;
    vector<tuple<int,int,int>> traversal;

    pq.push({3,3,0, {{3,3,0}}, 0, heuristic(3,3,0)});

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();

        if (vis.count(encode(cur.M,cur.C,cur.B))) continue;
        vis.insert(encode(cur.M,cur.C,cur.B));

        traversal.push_back({cur.M,cur.C,cur.B});

        if (cur.M == 0 && cur.C == 0 && cur.B == 1) {
            cout << "\n===== Best First Search =====\nTraversal:\n";
            for (auto &t : traversal) printState(t);

            cout << "\nSolution Path (with h):\n";
            for (auto &p : cur.path) {
                printState(p);
                cout << "h = " << heuristic(get<0>(p),get<1>(p),get<2>(p)) << "\n-----\n";
            }
            cout << "END\n";
            return;
        }

        for (auto &mv : getMoves(cur.M,cur.C,cur.B)) {
            int M = get<0>(mv), C = get<1>(mv), B = get<2>(mv);
            auto p = cur.path;
            p.push_back(mv);
            pq.push({M,C,B,p,0,heuristic(M,C,B)});
        }
    }
}

/* ========================= A* Search ========================= */
void AStar() {
    auto cmp = [&](State &a, State &b){
        return (a.g + a.h) > (b.g + b.h);
    };

    priority_queue<State, vector<State>, decltype(cmp)> pq(cmp);
    unordered_set<string> closed;
    vector<tuple<int,int,int>> traversal;

    pq.push({3,3,0, {{3,3,0}}, 0, heuristic(3,3,0)});

    while(!pq.empty()) {
        auto cur = pq.top(); pq.pop();

        if (closed.count(encode(cur.M,cur.C,cur.B))) continue;
        closed.insert(encode(cur.M,cur.C,cur.B));

        traversal.push_back({cur.M,cur.C,cur.B});

        if (cur.M == 0 && cur.C == 0 && cur.B == 1) {
            cout << "\n===== A* Search =====\nTraversal:\n";
            for (auto &t : traversal) printState(t);

            cout << "\nOptimal Path (g,h,f):\n";

            int g = 0;
            for (auto &p : cur.path) {
                int M = get<0>(p), C = get<1>(p), B = get<2>(p);
                int h = heuristic(M,C,B);
                cout << "(M=" << M << ", C=" << C << ", B=" << B << ")\n";
                cout << "g=" << g << ", h=" << h << ", f=" << g+h << "\n-----\n";
                g++;
            }
            cout << "END\n";
            return;
        }

        for (auto &mv : getMoves(cur.M,cur.C,cur.B)) {
            int M = get<0>(mv), C = get<1>(mv), B = get<2>(mv);
            auto p = cur.path;
            p.push_back(mv);

            pq.push({M,C,B,p,cur.g+1,heuristic(M,C,B)});
        }
    }
}

/* ========================= MAIN ========================= */
int main() {
    BFS();
    DFS();
    DLS(20);
    BestFirst();
    AStar();
    return 0;
}