//https://codeforces.com/problemset/problem/1475/F
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 4e6 +5 ;
const int MOD = 1e9 + 7;

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

void addImplies(int x, int y){
    adj.addEdge(x,y);
}


int t,n;
char a[1005][1005];
char b[1005][1005];
int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("game.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n;
        adj.n = 4*n;
        adj.init();
        for(int i=0;i<n;i++) {
            cin >> a[i];
        }
        for(int i=0;i<n;i++){
            cin >> b[i];
            for(int j=0;j<n;j++){
                if(b[i][j]==a[i][j]){
                    adj.addEdge(var(i),var(n+j));
                    adj.addEdge(var(j+n),var(i));
                    adj.addEdge(notvar(var(i)),notvar(var(n+j)));
                    adj.addEdge(notvar(var(j+n)),notvar(var(i)));
                }else{
                    addImplies(var(i),notvar(var(n+j)));
                    addImplies(notvar(var(n+j)),var(i));
                    addImplies(var(j+n),notvar(var(i)));
                    addImplies(notvar(var(i)),var(j+n));
                }
            }
        }
        bool res = twoSat();
        if(res){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
    }
    return 0;

}
