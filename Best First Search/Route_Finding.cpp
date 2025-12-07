#include <bits/stdc++.h>
using namespace std;

struct Node {
    string city;
    int h;
    vector<string> path;
    bool operator<(Node const &other) const {
        return h > other.h;
    }
};

int main() {
    int n;
    cin >> n;

    vector<string> cities(n);
    for (int i = 0; i < n; i++) cin >> cities[i];

    unordered_map<string, vector<pair<string,int>>> graph;

    int r;
    cin >> r;
    for (int i = 0; i < r; i++) {
        string a,b;
        int d;
        cin >> a >> b >> d;
        graph[a].push_back({b,d});
        graph[b].push_back({a,d});
    }

    string start, goal;
    cin >> start >> goal;

    unordered_map<string,int> heuristic;
    for (auto &c : cities) {
        int x;
        cin >> x;
        heuristic[c] = x;
    }

    priority_queue<Node> pq;
    set<string> visited;

    pq.push({start, heuristic[start], {start}});
    visited.insert(start);

    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();

        cout << "At: " << cur.city << " h=" << cur.h << "\n";

        if (cur.city == goal) {
            cout << "Path: ";
            for (auto &p : cur.path) cout << p << " ";
            cout << "\n";
            return 0;
        }

        for (auto &nbr : graph[cur.city]) {
            string next = nbr.first;

            if (!visited.count(next)) {
                visited.insert(next);
                vector<string> newPath = cur.path;
                newPath.push_back(next);
                pq.push({next, heuristic[next], newPath});
            }
        }
    }

    cout << "No route\n";
    return 0;
}
