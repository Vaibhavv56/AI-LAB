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


int main() {

    DLS(3);
  
return 0;
}

