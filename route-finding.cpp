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
