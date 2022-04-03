#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7 ;

int w,h;
char grid[1005][1005];
bool vis[1005][1005];
int cnt[1005];
vector<pair<int,int> > v;
int dx[]={0,0,1,-1,1,1,-1,-1};
int dy[]={1,-1,0,0,-1,1,1,-1};
bool cond;

void dfs(int i, int j){
    if(vis[i][j])
        return;
    if(i==1 || j==1 || i==h || j==w){
        cond=false;
    }
    vis[i][j]=1;
    v.pb({i,j});
    for(int k=0;k<8;k++){
        int ni = i+dx[k];
        int nj = j+dy[k];
        if(ni>=1 && nj>=1 && ni<=h && nj<=w && grid[ni-1][nj-1]=='#'){
            dfs(ni,nj);
        }
    }
}

int testA(){
    pair<int,int> mi = {100000,10000};
    for(auto u:v){
        mi=min(mi,u);
        cnt[u.fi]=0;
    }
    for(auto u:v){
        cnt[u.fi]++;
    }
    set<int> ss;
    for(auto u:v){
        ss.insert(cnt[u.fi]);
    }
    if(ss.size()!=2)
        return 0;
    int s = (*ss.begin());
    if(s%2)
        return 0;
    int x = s/2;
    ss.erase(ss.begin());
    int y = (*ss.begin())-2*x;
    int i = mi.fi;
    int j = mi.se;

    return v.size()==(2*x+y+2)*(2+3*x+2*y)-2*(2*x+y+2)-2*(3*x+2*y)-y*y-(y+x)*y;

}
int testB(){
    pair<int,int> mi = {100000,10000};
    for(auto u:v){
        mi=min(mi,u);
        cnt[u.fi]=0;
    }
    for(auto u:v){
        cnt[u.fi]++;
    }
    set<int> ss;
    for(auto u:v){
        ss.insert(cnt[u.fi]);
    }
    if(ss.size()!=2)
        return 0;
    int s = (*ss.begin());
    if(s%2)
        return 0;
    int x = s/2;

    ss.erase(ss.begin());
    int y = (*ss.begin())-2*x;
    int i = mi.fi;
    int j = mi.se;

    return v.size()==(2*x+y+2)*(2+3*x+2*y)-2*(2*x+y+2)-2*(3*x+2*y)-y*y-(y)*y;

}

int testC(){
    pair<int,int> mi = {100000,10000};
    for(auto u:v){
        mi=min(mi,u);
        cnt[u.fi]=0;
    }
    for(auto u:v){
        cnt[u.fi]++;
    }
    set<int> ss;
    for(auto u:v){
        ss.insert(cnt[u.fi]);
    }
    if(ss.size()!=2)
        return 0;
    int x = (*ss.begin());
    ss.erase(ss.begin());
    int y = (*ss.begin())-2*x;
    if(y<=0)
        return 0;
    int i = mi.fi;
    int j = mi.se;

    return v.size()==(2*x+y+2)*(2+3*x+2*y)-2*(2*x+y+2)-2*(3*x+2*y)-(y+x)*(2*y+x);
}


int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d%d",&w,&h);
    for(int i=0;i<h;i++){
        scanf("%s",&grid[i]);
    }

    int a=0, b=0,c=0;
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            if(vis[i][j])
                continue;
            if(grid[i-1][j-1]=='.')
                continue;
            v.clear();
            cond=true;
            dfs(i,j);
            if(!cond || v.size()==1)
                continue;
            a+=testA();
            b+=testB();
            c+=testC();
        }
    }
    cout << a << " " << b << " " << c << endl;

    return 0;

}
