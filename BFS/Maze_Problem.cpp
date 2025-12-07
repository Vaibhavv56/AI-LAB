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


    return 0;
}
