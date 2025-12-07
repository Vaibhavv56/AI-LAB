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

    DFS(sx,sy,gx,gy);


    return 0;
}
