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

int heuristic(int M, int C, int B) {
    return M + C;   
}



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



int main() {

    BestFirst();

return 0;
}

