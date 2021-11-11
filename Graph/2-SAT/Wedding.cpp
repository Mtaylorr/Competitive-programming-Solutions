//https://vjudge.net/problem/UVA-11294

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
    for(int i=0;i<adj.n;i++){
        if(vis[i]!=vid)
            dfs(i);
    }

    for(int u=0;u<adj.n;u++){
        neig(adj, u,e,v){
            int compu = comp[u], compv=comp[v];
            if(compu!=compv){
                notsrc[compv]=vid;
                notsnk[compu]=vid;
            }
        }
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
int val[N];

void getSol(int u){
    if(vis[u]==vid)
        return ;
    vis[u]=vid;
    neig(adj, u,e,v){
        getSol(v);
    }
    if(val[comp[u]]==-1)
    {
        val[comp[u]]=1;
        val[comp[u^1]]=0;
    }
}

bool twoSat(){
    tarjan();
    memset(val, -1, comps*sizeof(val[0]));
    vid++;
    for(int i=0;i<adj.n;i+=2){
        getSol(i);
        getSol(i+1);
        if(comp[i]==comp[i+1])
            return 0;
    }
    return 1;
}


int t;
int main(){
    freopen("input.txt", "r", stdin);
    int m,n,a,b;
    char c1,c2;
    while(1){
        scanf("%d %d",&n,&m);
        if(n==0 && m==0)
            break;
        adj.n = 4*n;
        adj.init();
        for(int i=0;i<n;i++){
            addor(var(i),var(i+n));
            addor(notvar(var(i)), notvar(var(i+n)));
        }
        addor(var(0), var(0));
        while(m--){
            scanf("%d%c %d%c",&a,&c1,&b,&c2);
            if(c1=='h')
                a+=n;
            if(c2=='h')
                b+=n;
            addor(var(a),var(b));
        }

        bool rs = twoSat();
        if(!rs){
            puts("bad luck");
        }else{
            for(int i=1;i<n;i++){
                printf("%d%c%c",i,"hw"[val[comp[var(i)]]], " \n"[i==n-1]);
            }
        }

    }
    return 0;
}
