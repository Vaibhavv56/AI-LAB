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

    DLS(sx,sy,gx,gy,limit);

    return 0;
}
