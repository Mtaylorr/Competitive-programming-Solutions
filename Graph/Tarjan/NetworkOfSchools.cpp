//https://vjudge.net/problem/OpenJ_Bailian-1236
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5  +5, E = 2e5+5;
const int MOD = 1e9 + 7 ;

#define neig(a, u, e,v) for(int e=a.head[u],v;(~e) &&(v=a.to[e],1);e=a.nxt[e])

int n;
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

}adj , radj;

int vid=0, vis[N], nodes[N], ndcnt=0, comp[N], comps, notsrc[N], notsnk[N];
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
    for(int i=0;i<n;i++){
        if(vis[i]!=vid)
            dfs(i);
    }

    for(int u=0;u<n;u++){
        neig(adj, u,e,v){
            int compu = comp[u], compv=comp[v];
            if(compu!=compv){
                notsrc[compv]=vid;
                notsnk[compu]=vid;
            }
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&n);
    adj.n=radj.n = n;
    adj.init();
    radj.init();
    int x;
    for(int i=0;i<n;i++){
        while(1){
            cin >> x;
            if(!x)
                break;
            adj.addEdge(i,x-1);
            radj.addEdge(x-1,i);
        }
    }
    tarjan();
    int src=0, snk=0;
    for(int i=0;i<comps;i++){
        if(notsrc[i]!=vid)
            src++;
        if(notsnk[i]!=vid)
            snk++;
    }
    printf("%d\n", src);
    if(comps==1){
        printf("0\n");
    }else{
        printf("%d\n", max(src, snk));
    }
    return 0;
}
