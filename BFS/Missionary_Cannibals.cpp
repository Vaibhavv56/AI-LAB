#include <bits/stdc++.h>
using namespace std;

struct State {
    int M, C, B;  
    vector<tuple<int,int,int>> path;
    int g, h;
};

void printState(const tuple<int,int,int> &s) {
    cout << "(M=" << get<0>(s)
         << ", C=" << get<1>(s)
         << ", B=" << get<2>(s) << ")\n";
}

string encode(int M, int C, int B) {
    return to_string(M) + "," + to_string(C) + "," + to_string(B);
}

bool isValid(int M, int C, int B) {
    if (M < 0 || M > 3 || C < 0 || C > 3) return false;

    int M_r = 3 - M;
    int C_r = 3 - C;

    if (M > 0 && C > M) return false;     
    if (M_r > 0 && C_r > M_r) return false; 

    return true;
}

vector<tuple<int,int,int>> getMoves(int M, int C, int B) {
    vector<tuple<int,int,int>> moves;

    vector<pair<int,int>> actions = {
        {1,0}, {2,0}, {0,1}, {0,2}, {1,1}
    };

    int dir = (B == 0 ? -1 : 1);

    for (auto &act : actions) {
        int m = act.first;
        int c = act.second;
        if (m + c == 0) continue;  
        int nM = M + dir * m;
        int nC = C + dir * c;
        int nB = 1 - B;

        if (isValid(nM, nC, nB))
            moves.push_back({nM, nC, nB});
    }

    return moves;
}

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

int main() {
    BFS();

return 0;
}

