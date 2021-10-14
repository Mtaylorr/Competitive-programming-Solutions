//https://www.spoj.com/problems/QTREE5/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e5+5, Q = 1e5+5;
vector<int> adj[N], indexToNode;
int nodeToIndex[N], dpth[N], spt[20][5*N];
int par[N], done[N], szs[N], nb=0;
int lg[4*N];
multiset<int> ms[N];

void dfs(int u=0, int p=0, int d=0){
    nodeToIndex[u]=indexToNode.size();
    indexToNode.pb(u);
    dpth[u]=d;
    for(auto v:adj[u]){
        if(v==p)
            continue;
        dfs(v,u,d+1);
        indexToNode.pb(u);
    }
}

void buildspt(){
    lg[1]=0;
    int m = indexToNode.size();
    for(int i=2;i<=m;i++)
        lg[i]=1+lg[i/2];
    for(int i=0;i<m;i++){
        spt[0][i]=indexToNode[i];
    }
    int cur=1;
    for(int x=1;(1<<x)<=m;x++){
        cur*=2;
        for(int i=0;i<m;i++){
            if(i+cur-1>=m)
                continue;
            int lf = spt[x-1][i];
            int rg = spt[x-1][i+(cur/2)];
            if(dpth[lf]>dpth[rg])
                swap(lf, rg);
            spt[x][i]=lf;
        }
    }
}

int getminspt(int x, int y){
    if(x>y)
        swap(x,y);
    int l = lg[y-x+1];
    int lf = spt[l][x];
    int rg = spt[l][y-(1<<l)+1];
    if(dpth[lf]>dpth[rg])
        swap(lf, rg);
    return lf;
}

int sptLCA(int a, int b){
    return getminspt(nodeToIndex[a], nodeToIndex[b]);
}

int getDist(int a, int b){
    return dpth[a]+dpth[b]-2*dpth[sptLCA(a,b)];
}

int calcsz(int u, int p){
    szs[u]=1;
    for(auto v:adj[u]){
        if(v==p || done[v])
            continue;
        szs[u]+=calcsz(v,u);
    }
    return szs[u];
}

int getcenter(int u, int p, int sz){
    for(auto v:adj[u]){
        if(v==p || done[v])
            continue;
        if(2*szs[v]>sz)
            return getcenter(v, u, sz);
    }
    return u;
}


int BuildCentroid(int src=0){
    int sz = calcsz(src,src);
    int center = getcenter(src,src, sz);
    done[center]=1;
    for(auto v:adj[center]){
        if(done[v])
            continue;
        par[BuildCentroid(v)]=center;
    }
    return center;
}

void add(int a){
    int cur=a;
    while(cur!=-1){
        ms[cur].insert(getDist(a,cur));
        cur = par[cur];
    }
}

void rem(int a){
    int cur=a;
    while(cur!=-1){
        ms[cur].erase(ms[cur].find(getDist(a,cur)));
        cur = par[cur];
    }
}
int getans(int a){
    int res=1e9;
    int cur=a;
    while(cur!=-1){
        if(!ms[cur].empty())
            res=min(res, (*ms[cur].begin())+getDist(a,cur));
        cur= par[cur];
    }
    return res;
}

int q;
int col[N];
int n;
int u,v;

int main(){
    freopen("input.txt", "r", stdin);
    memset(par, -1, sizeof(par));
    scanf("%d",&n);
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        u--;v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs();
    buildspt();
    BuildCentroid();
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&u,&v);
        v--;
        if(u==0){
            if(col[v]==0)
                add(v);
            else
                rem(v);
            nb-=col[v];
            col[v] = 1-col[v];
            nb+=col[v];
        }else{
            if(nb==0){
                puts("-1");
            }else{
                printf("%d\n", getans(v));
            }
        }
    }
    return 0;
}
