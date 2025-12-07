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

/* ================= BFS ================= */
void BFS(int sx,int sy,int gx,int gy){
    queue<pair<int,int>> q;
    map<pair<int,int>,pair<int,int>> parent;
    vector<pair<int,int>> traversal;
    memset(visited,false,sizeof(visited));

    q.push({sx,sy});
    visited[sx][sy]=true;
    parent[{sx,sy}]={-1,-1};

    while(!q.empty()){
        auto [x,y]=q.front(); q.pop();
        traversal.push_back({x,y});

        if(x==gx && y==gy){
            cout<<"\nBFS Traversal Order:\n"; 
            printPath(traversal);

            vector<pair<int,int>> path;
            pair<int,int> cur={gx,gy};
            while(cur.first!=-1){
                path.push_back(cur);
                cur = parent[cur];
            }
            reverse(path.begin(),path.end());
            cout<<"\nBFS Shortest Path:\n"; 
            printPath(path);
            return;
        }

        for(int i=0;i<4;i++){
            int nx=x+dx[i], ny=y+dy[i];
            if(nx>=0 && ny>=0 && nx<ROWS && ny<COLS && maze[nx][ny]==0 && !visited[nx][ny]){
                visited[nx][ny]=true;
                parent[{nx,ny}]={x,y};
                q.push({nx,ny});
            }
        }
    }
    cout<<"No path found using BFS\n";
}

/* ================= DFS ================= */
bool DFSUtil(int x,int y,int gx,int gy, vector<pair<int,int>> &path, vector<pair<int,int>> &traversal){
    traversal.push_back({x,y});
    if(x==gx && y==gy){ path.push_back({x,y}); return true; }

    visited[x][y]=true;
    path.push_back({x,y});

    for(int i=0;i<4;i++){
        int nx=x+dx[i], ny=y+dy[i];
        if(nx>=0 && ny>=0 && nx<ROWS && ny<COLS && maze[nx][ny]==0 && !visited[nx][ny]){
            if(DFSUtil(nx,ny,gx,gy,path,traversal)) return true;
        }
    }
    path.pop_back();
    return false;
}

void DFS(int sx,int sy,int gx,int gy){
    memset(visited,false,sizeof(visited));
    vector<pair<int,int>> path, traversal;
    if(DFSUtil(sx,sy,gx,gy,path,traversal)){
        cout<<"\nDFS Traversal Order:\n"; printPath(traversal);
        cout<<"\nDFS Path:\n"; printPath(path);
    } else cout<<"No path found using DFS\n";
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

/* ================= A* Search ================= */
struct NodeAStar {
    int x,y,g,h;
    bool operator<(const NodeAStar &other) const { 
        return g+h > other.g+other.h;
    }
};

void AStar(int sx,int sy,int gx,int gy){
    priority_queue<NodeAStar> pq;
    vector<vector<bool>> visited(ROWS, vector<bool>(COLS,false));
    vector<vector<pair<int,int>>> parent(ROWS, vector<pair<int,int>>(COLS,{-1,-1}));
    vector<pair<int,int>> traversal;

    pq.push({sx,sy,0,heuristic(sx,sy,gx,gy)});

    cout << "\n--- A* Search (Printing g, h, f=g+h) ---\n";

    while(!pq.empty()){
        NodeAStar cur = pq.top(); pq.pop();
        if(visited[cur.x][cur.y]) continue;

        visited[cur.x][cur.y] = true;
        traversal.push_back({cur.x,cur.y});

        cout << "Visiting (" << cur.x << "," << cur.y 
             << ")  g=" << cur.g 
             << "  h=" << cur.h 
             << "  f=" << cur.g + cur.h << "\n";

        if(cur.x==gx && cur.y==gy){
            cout<<"\nA* Traversal Order:\n"; printPath(traversal);

            vector<pair<int,int>> path;
            int x=cur.x, y=cur.y;
            while(x!=-1){
                path.push_back({x,y});
                auto p=parent[x][y]; x=p.first; y=p.second;
            }
            reverse(path.begin(),path.end());
            cout<<"\nA* Path:\n"; printPath(path);
            return;
        }

        for(int i=0;i<4;i++){
            int nx=cur.x+dx[i], ny=cur.y+dy[i];
            if(nx>=0 && ny>=0 && nx<ROWS && ny<COLS && maze[nx][ny]==0 && !visited[nx][ny]){
                parent[nx][ny]={cur.x,cur.y};
                pq.push({nx,ny,cur.g+1,heuristic(nx,ny,gx,gy)});
            }
        }
    }
    cout<<"No path found using A*\n";
}

/* ================= Depth-Limited Search ================= */
bool DLSUtil(int x,int y,int gx,int gy,int limit,
             vector<pair<int,int>> &path,
             vector<pair<int,int>> &traversal){

    traversal.push_back({x,y});

    if(x==gx && y==gy){
        path.push_back({x,y});
        return true;
    }

    if(limit==0) return false;

    visited[x][y]=true;
    path.push_back({x,y});

    for(int i=0;i<4;i++){
        int nx=x+dx[i], ny=y+dy[i];
        if(nx>=0 && ny>=0 && nx<ROWS && ny<COLS &&
           maze[nx][ny]==0 && !visited[nx][ny]){

            if(DLSUtil(nx,ny,gx,gy,limit-1,path,traversal))
                return true;
        }
    }

    path.pop_back();
    return false;
}

void DLS(int sx,int sy,int gx,int gy,int limit){
    memset(visited,false,sizeof(visited));
    vector<pair<int,int>> path, traversal;

    if(DLSUtil(sx,sy,gx,gy,limit,path,traversal)){
        cout << "\nDLS Traversal Order (limit="<<limit<<"):\n";
        printPath(traversal);

        cout << "\nDLS Path:\n";
        printPath(path);
    } else {
        cout << "\nGoal NOT found within depth limit " << limit << "\n";
        cout << "Traversal was:\n";
        printPath(traversal);
    }
}

/* ================= MAIN ================= */
int main(){
    int sx,sy,gx,gy,limit;

    cout<<"Enter Start State (row col): ";
    cin>>sx>>sy;

    cout<<"Enter Goal State (row col): ";
    cin>>gx>>gy;

    cout<<"Enter Depth Limit for DLS: ";
    cin>>limit;

    if(maze[sx][sy]==1 || maze[gx][gy]==1){
        cout<<"Start or Goal is a wall!\n";
        return 0;
    }

    BFS(sx,sy,gx,gy);
    DFS(sx,sy,gx,gy);
    BestFirst(sx,sy,gx,gy);
    AStar(sx,sy,gx,gy);
    DLS(sx,sy,gx,gy,limit);

    return 0;
}
