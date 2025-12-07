#include <bits/stdc++.h>
using namespace std;

/* ================= Heuristic (SLD) ================= */
unordered_map<string,int> h;

/* ================= Graph ================= */
unordered_map<string, unordered_map<string,int>> g;

void addEdge(string u, string v, int cost){
    g[u][v] = cost;
    g[v][u] = cost;
}

/* ================= Node Structure ================= */
struct Node {
    string city;
    int gCost;   // cost from start
    int fCost;   // evaluation

    Node(string c, int g, int f){
        city = c;
        gCost = g;
        fCost = f;
    }
};

/* ================= BEST FIRST SEARCH ================= */
void BestFirstSearch(string start, string goal){
    cout << "\n===== BEST FIRST SEARCH =====\n";

    auto cmp = [](Node a, Node b){
        return a.fCost > b.fCost;     // f = h
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    unordered_set<string> visited;
    unordered_map<string,string> parent;

    pq.push(Node(start, 0, h[start]));
    parent[start] = "";

    while(!pq.empty()){
        Node cur = pq.top(); pq.pop();

        if(visited.count(cur.city)) continue;
        visited.insert(cur.city);

        if(cur.city == goal){
            vector<string> path;
            string c = goal;
            while(c != ""){
                path.push_back(c);
                c = parent[c];
            }
            reverse(path.begin(), path.end());

            cout << "Path: ";
            for(auto &x : path) cout << x << " ";
            cout << "\n(Note: Cost may NOT be optimal)\n";
            return;
        }

        for(auto &nbr : g[cur.city]){
            if(!visited.count(nbr.first)){
                parent[nbr.first] = cur.city;
                pq.push(Node(nbr.first, 0, h[nbr.first]));
            }
        }
    }
}

/* ================= A* SEARCH ================= */
void AStarSearch(string start, string goal){
    cout << "\n===== A* SEARCH =====\n";

    auto cmp = [](Node a, Node b){
        return a.fCost > b.fCost;   // f = g + h
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    unordered_map<string,int> dist;
    unordered_map<string,string> parent;
    unordered_set<string> visited;

    pq.push(Node(start, 0, h[start]));
    dist[start] = 0;
    parent[start] = "";

    while(!pq.empty()){
        Node cur = pq.top(); pq.pop();

        if(visited.count(cur.city)) continue;
        visited.insert(cur.city);

        if(cur.city == goal){
            vector<string> path;
            string c = goal;
            while(c != ""){
                path.push_back(c);
                c = parent[c];
            }
            reverse(path.begin(), path.end());

            cout << "Path: ";
            for(auto &x : path) cout << x << " ";
            cout << "\nOptimal Cost = " << cur.gCost << endl;
            return;
        }

        for(auto &nbr : g[cur.city]){
            int newG = cur.gCost + nbr.second;
            if(!dist.count(nbr.first) || newG < dist[nbr.first]){
                dist[nbr.first] = newG;
                parent[nbr.first] = cur.city;
                pq.push(Node(nbr.first, newG, newG + h[nbr.first]));
            }
        }
    }
}

/* ================= MAIN ================= */
int main(){

    /* -------- Heuristic Values -------- */
    h["Arad"]=366; h["Bucharest"]=0; h["Craiova"]=160;
    h["Drobeta"]=242; h["Eforie"]=161; h["Fagaras"]=176;
    h["Giurgiu"]=77; h["Hirsova"]=151; h["Iasi"]=226;
    h["Lugoj"]=244; h["Mehadia"]=241; h["Neamt"]=234;
    h["Oradea"]=380; h["Pitesti"]=100; h["RimnicuVilcea"]=193;
    h["Sibiu"]=253; h["Timisoara"]=329; h["Urziceni"]=80;
    h["Vaslui"]=199; h["Zerind"]=374;

    /* -------- Graph Edges -------- */
    addEdge("Arad","Zerind",75);
    addEdge("Arad","Sibiu",140);
    addEdge("Arad","Timisoara",118);
    addEdge("Zerind","Oradea",71);
    addEdge("Oradea","Sibiu",151);
    addEdge("Timisoara","Lugoj",111);
    addEdge("Lugoj","Mehadia",70);
    addEdge("Mehadia","Drobeta",75);
    addEdge("Drobeta","Craiova",120);
    addEdge("Craiova","RimnicuVilcea",146);
    addEdge("Craiova","Pitesti",138);
    addEdge("RimnicuVilcea","Sibiu",80);
    addEdge("RimnicuVilcea","Pitesti",97);
    addEdge("Sibiu","Fagaras",99);
    addEdge("Fagaras","Bucharest",211);
    addEdge("Pitesti","Bucharest",101);

    string start = "Arad";
    string goal  = "Bucharest";

    BestFirstSearch(start, goal);
    AStarSearch(start, goal);

    return 0;
}




//2
#include <bits/stdc++.h>
using namespace std;

const int ROWS = 5;
const int COLS = 5;

// 0 = free, 1 = obstacle
int grid[ROWS][COLS] = {
    {0, 0, 0, 0, 0},
    {1, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0}
};

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Node {
    int x, y;
    int g, h;
    vector<pair<int,int>> path;
};

/* ================= HEURISTIC ================= */
int heuristic(int x, int y, int gx, int gy) {
    return abs(x - gx) + abs(y - gy);
}

/* ================= PRINT PATH ================= */
void printPath(vector<pair<int,int>> &path) {
    for (auto &p : path)
        cout << "(" << p.first << "," << p.second << ") -> ";
    cout << "GOAL\n";
}

/* ================= BEST FIRST SEARCH ================= */
void BestFirst(int sx, int sy, int gx, int gy) {
    cout << "\n===== BEST FIRST SEARCH =====\n";

    auto cmp = [](Node a, Node b) {
        return a.h > b.h;   // f(n) = h(n)
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    bool visited[ROWS][COLS] = {false};

    pq.push({sx, sy, 0, heuristic(sx,sy,gx,gy), {{sx,sy}}});

    while(!pq.empty()) {
        Node cur = pq.top(); pq.pop();

        if (visited[cur.x][cur.y]) continue;
        visited[cur.x][cur.y] = true;

        if (cur.x == gx && cur.y == gy) {
            cout << "Path (Greedy):\n";
            printPath(cur.path);
            return;
        }

        for(int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if(nx>=0 && ny>=0 && nx<ROWS && ny<COLS &&
               grid[nx][ny]==0 && !visited[nx][ny]) {

                auto p = cur.path;
                p.push_back({nx,ny});
                pq.push({nx, ny, 0, heuristic(nx,ny,gx,gy), p});
            }
        }
    }
    cout << "No path found.\n";
}

/* ================= A* SEARCH ================= */
void AStar(int sx, int sy, int gx, int gy) {
    cout << "\n===== A* SEARCH =====\n";

    auto cmp = [](Node a, Node b) {
        return (a.g + a.h) > (b.g + b.h);
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    bool closed[ROWS][COLS] = {false};

    pq.push({sx, sy, 0, heuristic(sx,sy,gx,gy), {{sx,sy}}});

    while(!pq.empty()) {
        Node cur = pq.top(); pq.pop();

        if (closed[cur.x][cur.y]) continue;
        closed[cur.x][cur.y] = true;

        if (cur.x == gx && cur.y == gy) {
            cout << "Optimal Path:\n";
            printPath(cur.path);
            cout << "Total Cost = " << cur.g << endl;
            return;
        }

        for(int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if(nx>=0 && ny>=0 && nx<ROWS && ny<COLS &&
               grid[nx][ny]==0 && !closed[nx][ny]) {

                auto p = cur.path;
                p.push_back({nx,ny});
                pq.push({nx, ny, cur.g+1,
                         heuristic(nx,ny,gx,gy), p});
            }
        }
    }
    cout << "No path found.\n";
}

/* ================= MAIN ================= */
int main() {
    int sx = 0, sy = 0;
    int gx = 4, gy = 4;

    BestFirst(sx, sy, gx, gy);
    AStar(sx, sy, gx, gy);

    return 0;
}
