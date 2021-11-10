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

void dfs1(int u){
    if(vis[u]==vid)
        return;
    vis[u]=vid;
    neig(adj,u,e,v){
        dfs1(v);
    }
    nodes[ndcnt++]=u;
}

void dfs2(int u, int id){
    if(vis[u]==vid){
        return ;
    }
    vis[u]=vid;
    comp[u]=id;
    neig(radj, u,e,v){
        dfs2(v,id);
    }
}

void kosaraju(){
    ndcnt=0;
    vid++;
    for(int i=0;i<n;i++){
        if(vis[i]!=vid)
            dfs1(i);
    }
    vid++;
    comps=0;
    while(ndcnt--){
        if(vis[nodes[ndcnt]]!=vid)
            dfs2(nodes[ndcnt],comps++);
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
    kosaraju();
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
