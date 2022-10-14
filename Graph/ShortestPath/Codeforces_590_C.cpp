//https://codeforces.com/problemset/problem/590/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;

int id[4];
int n,m;
char grid[1005][1005];
int dist[4][1005][1005];
int mndist[4][4];
bool vis[1005][1005];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};

int getid(int u){
    return (id[u]==u?u:id[u]=getid(id[u]));
}

void uni(int u, int v){
    u=getid(u);
    v=getid(v);
    id[u]=v;
}

bool isstate(int i,int j){
    return grid[i][j]!='.' && grid[i][j]!='#';
}

bool ingrid(int i,int j){
    return (i>=0 && i<n && j>=0 && j<m);
}

void bfs(int c){
    memset(vis, 0, sizeof(vis));
    queue<pair<int,int> > q;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(isstate(i,j) && getid(grid[i][j]-'0')==c){
                vis[i][j]=1;
                dist[c][i][j]=0;
                q.push({i,j});
            }else{
                vis[i][j]=0;
                dist[c][i][j]=1e7;
            }
        }
    }
    pair<int,int > p;
    while(!q.empty()){
        p=q.front();
        q.pop();
        for(int k=0;k<4;k++){
            int ni = p.fi+dx[k];
            int nj = p.se+dy[k];
            if(ingrid(ni,nj) && vis[ni][nj]==0 && grid[ni][nj]!='#'){
                vis[ni][nj]=1;
                dist[c][ni][nj]=dist[c][p.fi][p.se]+1;
                if(isstate(ni,nj)){
                    int d = getid(grid[ni][nj]-'0');
                    mndist[c][d]=min( mndist[c][d],dist[c][ni][nj]);
                }
                q.push({ni,nj});
            }
        }
    }


}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i=1;i<=3;i++){
        id[i]=i;
    }
    for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++){
            mndist[i][j]=1e7;
        }
    }
    for(int i=0;i<n;i++){
        cin >> grid[i];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!isstate(i,j))
                continue;
            for(int k=0;k<4;k++){
                int ni = i+dx[k];
                int nj = j+dy[k];
                if(ingrid(ni,nj) && isstate(ni,nj)){
                    uni(grid[i][j]-'0', grid[ni][nj]-'0');
                }
            }
        }
    }
    vector<int> v;
    for(int i=1;i<=3;i++){
        if(id[i]==i){
            v.pb(i);
        }
    }
    for(auto u:v){
        bfs(u);
    }
    int ans=1e9;
    for(int i=1;i<=3;i++){
        int rs=0;
        for(int j=1;j<=3;j++){
            if(getid(i)==getid(j))
                continue;
            if(getid(j)==j){
                rs+=mndist[getid(i)][j]-1;
            }
        }
        ans=min(ans, rs);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j]=='.'){
                int rs=0;
                for(auto u:v){
                    rs+=dist[u][i][j]-1;
                }
                rs++;
                ans=min(ans, rs);
            }
        }
    }
    if(ans<=n*m){
        cout << ans;
    }else{
        cout << -1;
    }


    return 0;

}
