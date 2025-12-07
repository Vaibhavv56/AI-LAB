#include <bits/stdc++.h>
using namespace std;

const int ROWS = 4;
const int COLS = 4;

// Maze: 0 = free, 1 = wall
int maze[ROWS][COLS] = {
    {0, 1, 0, 0},
    {0, 0, 0, 1},
    {1, 0, 1, 0},
    {0, 0, 0, 0}

};

bool visited[ROWS][COLS];
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

void printPath(vector<pair<int,int>> &path){
    for(auto &p: path)
        cout << "(" << p.first << "," << p.second << ") -> ";
    cout << "END\n";
}


/* ================= Heuristic ================= */
int heuristic(int x,int y,int gx,int gy){
    return abs(x-gx)+abs(y-gy); // Manhattan Distance
}

/* ================= Best-First Search ================= */
struct NodeBFS {
    int x,y,h;
    bool operator<(const NodeBFS &other) const { return h > other.h; }
};

void BestFirst(int sx,int sy,int gx,int gy){
    priority_queue<NodeBFS> pq;
    vector<vector<bool>> visited(ROWS, vector<bool>(COLS,false));
    vector<vector<pair<int,int>>> parent(ROWS, vector<pair<int,int>>(COLS,{-1,-1}));
    vector<pair<int,int>> traversal;

    pq.push({sx,sy,heuristic(sx,sy,gx,gy)});
    visited[sx][sy]=true;

    cout << "\n--- Best First Search (Printing Heuristic h) ---\n";

    while(!pq.empty()){
        NodeBFS cur=pq.top(); pq.pop();

        cout << "Visiting (" << cur.x << "," << cur.y << ")  h=" << cur.h << "\n";

        traversal.push_back({cur.x,cur.y});

        if(cur.x==gx && cur.y==gy){
            cout<<"\nBest-First Traversal Order:\n"; printPath(traversal);

            vector<pair<int,int>> path;
            int x=cur.x,y=cur.y;
            while(x!=-1){
                path.push_back({x,y});
                auto p=parent[x][y]; x=p.first; y=p.second;
            }
            reverse(path.begin(),path.end());
            cout<<"\nBest-First Path:\n"; printPath(path);
            return;
        }

        for(int i=0;i<4;i++){
            int nx=cur.x+dx[i], ny=cur.y+dy[i];
            if(nx>=0 && ny>=0 && nx<ROWS && ny<COLS && maze[nx][ny]==0 && !visited[nx][ny]){
                visited[nx][ny]=true;
                parent[nx][ny]={cur.x,cur.y};
                pq.push({nx,ny,heuristic(nx,ny,gx,gy)});
            }
        }
    }
    cout<<"No path found using Best-First\n";
}


/* ================= MAIN ================= */
int main(){
    int sx,sy,gx,gy,limit;

    cout<<"Enter Start State (row col): ";
    cin>>sx>>sy;

    cout<<"Enter Goal State (row col): ";
    cin>>gx>>gy;


    if(maze[sx][sy]==1 || maze[gx][gy]==1){
        cout<<"Start or Goal is a wall!\n";
        return 0;
    }

    BestFirst(sx,sy,gx,gy);


    return 0;
}
