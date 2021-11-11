//https://codeforces.com/contest/776/problem/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 4e5+5;
const int MOD = 1e9 + 7 ;

#define neig(a,u,v,e) for(int e=a.head[u], v; (~e)&&(v=a.to[e], 1);e=a.nxt[e])

struct Adj{
    int nxt[E], head[N], to[E], edgcnt=0,n;

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
int vis[N],vid=0;
int comp[N], comps, ndcnt, nodes[N],low[N], dfst[N], curt;

void dfs(int u){
    vis[u]=vid;
    comp[u]=-1;
    nodes[ndcnt++]=u;
    dfst[u]=low[u]=curt++;
    neig(adj,u,v,e){
        if(vis[v]!=vid){
            dfs(v);
            low[u]=min(low[u], low[v]);
        }else{
            if(comp[v]==-1){
                low[u]=min( low[u], low[v]);
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
    vid++;
    curt=0;
    comps=0;
    ndcnt=0;
    for(int i=0;i<adj.n;i++){
        if(vis[i]!=vid){
            dfs(i);
        }
    }
}

bool twoSat(){
    tarjan();
    for(int i=0;i<adj.n;i+=2){
        if(comp[i]==comp[i+1]){
            return 0;
        }
    }
    return 1;
}

int var(int x){
    return 2*x;
}

int notvar(int x){
    return x^1;
}

void addor(int x, int y){
    adj.addEdge(notvar(y),x);
    adj.addEdge(notvar(x),y);
}


int n,m,x,y;
int r[N];
vector<int> switches[N];
int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d",&n,&m);
    adj.n = 2*m;
    adj.init();
    for(int i=0;i<n;i++){
        scanf("%d",&r[i]);
    }
    for(int i=0;i<m;i++){
        scanf("%d",&x);
        while(x--){
            scanf("%d",&y);
            switches[--y].pb(i);
        }
    }
    for(int i=0;i<n;i++){
        x = switches[i][0];
        y = switches[i][1];
        if(!r[i]){
            addor(var(x),var(y));
            addor(notvar(var(x)), notvar(var(y)));
        }else{
            addor(var(x), notvar(var(y)));
            addor(notvar(var(x)), var(y));
        }
    }
    bool res = twoSat();
    if(res){
        puts("YES");
    }else{
        puts("NO");
    }
    return 0;
}
