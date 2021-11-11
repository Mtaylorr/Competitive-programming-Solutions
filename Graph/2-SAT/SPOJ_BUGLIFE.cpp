//https://www.spoj.com/problems/BUGLIFE/

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5  +5, E = 4e6+5;
const int MOD = 1e9 + 7 ;

#define neig(a, u, e,v) for(int e=a.head[u],v;(~e) &&(v=a.to[e],1);e=a.nxt[e])

struct Adj{
    int head[N], nxt[E], to[E],edgcnt, n;

    void addEdge(int a, int b){
        nxt[edgcnt]=head[a];
        head[a]=edgcnt;
        to[edgcnt++]=b;
    }

    void init(){
        int edgcnt=0;
        memset(head, -1, n*sizeof(head[0]));
    }

}adj;

int vid=0, vis[N], nodes[N], ndcnt=0, comp[N], comps;
int dfst[N], low[N], curt=0;


void dfs(int u){
    vis[u]=vid;
    low[u]=dfst[u]=curt++;
    nodes[ndcnt++]=u;
    comp[u]=-1;
    neig(adj,u,e,v){
        if(vis[v]!=vid){
            dfs(v);
            low[u]=min(low[u], low[v]);
        }else{
            if(comp[v]==-1){
                low[u]=min(low[u],low[v]);
            }
        }
    }
    if(low[u]==dfst[u]){
        do{
            comp[nodes[--ndcnt]]=comps;
        }while(nodes[ndcnt]!=u);
        comps++;
    }
}

void tarjan(){
    ndcnt=0;
    vid++;
    curt=0;
    comps=0;
    for(int i=0;i<adj.n;i++){
        if(vis[i]!=vid)
            dfs(i);
    }
}

int var(int x){
    return 2*x;
}

int notvar(int x){
    return x^1;
}

void addor(int x, int y){
    adj.addEdge(notvar(x), y);
    adj.addEdge(notvar(y), x);
}

bool twoSat(){
    tarjan();
    for(int i=0;i<adj.n;i+=2){
        if(comp[i]==comp[i+1])
            return 0;
    }
    return 1;
}
int t;
int main(){
    freopen("input.txt", "r", stdin);
    int m,n,a,b;
    scanf("%d",&t);
    int ii=0;
    while(t--){
        scanf("%d %d",&n,&m);
        adj.n = 2*n;
        adj.init();
        while(m--){
            scanf("%d%d",&a,&b);
            a--;b--;
            addor(var(a),var(b));
            addor(notvar(var(a)), notvar(var(b)));
        }
        printf("Scenario #%d:\n", ++ii);
        if(twoSat()){
            puts("No suspicious bugs found!");
        }else{
            puts("Suspicious bugs found!");
        }
    }
    return 0;
}
