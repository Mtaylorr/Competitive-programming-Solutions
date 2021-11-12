//https://codeforces.com/problemset/problem/27/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 4e5+5;
const int MOD = 1e9 + 7 ;

#define neig(a,u,v,e) for(int e=a.head[u],v;(~e)&&(v=a.to[e],1);e=a.nxt[e])

struct Adj{
    int n, nxt[E], head[N],to[E], edgcnt;

    void addEdge(int a, int b){
        nxt[edgcnt]=head[a];
        head[a]=edgcnt;
        to[edgcnt]=b;
        edgcnt++;
    }

    void init(){
        edgcnt=0;
        memset(head, -1, n*sizeof(head[0]));
    }
}adj;

int low[N], dfst[N],curt, vid, vis[N], comp[N], comps, nodes[N], ndcnt;
int val[N];
void dfs(int u){
    vis[u]=vid;
    low[u] = dfst[u] = curt++;
    comp[u]=-1;
    nodes[ndcnt++]=u;
    neig(adj, u,v,e){
        if(vis[v]!=vid){
            dfs(v);
            low[u]=min(low[v], low[u]);
        }else{
            if(comp[v]==-1){
                low[u]=min(low[u], low[v]);
            }
        }
    }
    if(dfst[u]==low[u]){
        do{
            comp[nodes[--ndcnt]]=comps;
        }while(nodes[ndcnt]!=u);
        comps++;
    }
}

void tarjan(){
    curt=0;
    vid++;
    comps=0;
    ndcnt=0;
    for(int i=0;i<adj.n;i++){
        if(vis[i]!=vid)
            dfs(i);
    }
}

void getsol(int u){
    if(vis[u]==vid)
        return ;
    vis[u]=vid;
    neig(adj, u,v,e){
        if(vis[v]==vid)
            continue;
        getsol(v);
    }
    if(val[comp[u]]==-1){
        val[comp[u]]=1;
        val[comp[u^1]]=0;
    }
}

bool twoSat(){
    tarjan();
    vid++;
    memset(val, -1, adj.n*sizeof(val[0]));
    for(int i=0;i<adj.n;i+=2){
        getsol(i);
        getsol(i+1);
        if(comp[i]==comp[i+1]){
            return 0;
        }
    }
    return 1;
}
int var(int x){
    return x<<1;
}
int notvar(int x){
    return x^1;
}

void addor(int x, int y){
    adj.addEdge(notvar(x),y);
    adj.addEdge(notvar(y),x);
}

int a,b,c,n,m;
vector<pair<int,int> > paths;

int isin(int a , int x, int y){
    if(a==x || a==y)
        return -1;
    return (a> x && a<y) || (a>y && a<x);
}
int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d",&n,&m);
    adj.n = 2*m;
    adj.init();
    for(int i=0;i<m;i++){
        scanf("%d%d",&a,&b);
        paths.pb({a,b});
    }

    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            if(j==i)
                continue;
            int c1 = isin(paths[i].fi, paths[j].fi, paths[j].se);
            int c2 = isin(paths[i].se, paths[j].fi, paths[j].se);
            if(c1!=c2 && c1>=0 && c2>=0){
                addor(var(i), var(j));
                addor(notvar(var(i)), notvar(var(j)));
            }
        }
    }
    bool res = twoSat();
    if(!res){
        puts("Impossible");
    }
    else{
        for(int i=0;i<adj.n;i+=2){
            cout << "io"[val[comp[i]]];
        }

    }
    return 0;
}
