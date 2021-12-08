//https://www.spoj.com/problems/OPTM/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 30020 , E = 2e6 + 5;
const int MOD = 1e9 + 7 ;
#define neig(u,e,v) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int head[N], nxt[E], to[E],edgcnt=0,cap[E],n, work[N];
int vis[N], vid=0 , dist[N], par[N],src, snk;

void addEdge(int a , int b , int c){
    nxt[edgcnt]=head[a];
    to[edgcnt]=b;
    cap[edgcnt]=c;
    head[a]=edgcnt++;
}

void addAug(int a, int b , int fcp, int rcp=0){
    addEdge(a,b,fcp);
    addEdge(b,a,rcp);
}

void init(){
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
}
bool bfs(){
    queue<int> q;
    dist[src]=0;
    vis[src]=++vid;
    q.push(src);
    while(q.size()){
        int u = q.front();
        q.pop();
        neig(u,e,v){
            if(!cap[e] || vis[v]==vid)
                continue;
            dist[v]=dist[u]+1;
            vis[v]=vid;
            q.push(v);
        }
    }
    return vis[snk]==vid;
}

int dfs(int u=src, int fl=INT_MAX){
    if(u==snk)
        return fl;

    for(int &e=work[u],v;(~e)&&(v=to[e],1);e=nxt[e]){
        if(!cap[e] || dist[v]!=dist[u]+1)
            continue;
        int f = dfs(v, min(cap[e], fl));
        if(f){
            cap[e]-=f;
            cap[e^1]+=f;
            return f;
        }
    }
    return 0;
}

int dinic(){
    int flow=0, f=0;
    while(bfs()){
        memcpy(work , head, n*sizeof(head[0]));
        while(f=dfs()){
            flow+=f;
        }
    }
    return flow;
}
vector<int> adj[N];
int t;
int nodes, m,a,b,k,mark[N];
int res[N];

void solve(int u, int cur){
    if(vis[u]==vid)
        return ;
    vis[u]=vid;
    res[u]+=cur;
    neig(u,e,v){
        if(!cap[e])
            continue;
        solve(v,cur);
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&nodes, &m);
        n=nodes+2;
        for(int i=0;i<nodes;i++){
            adj[i].clear();
            mark[i]=-1;
            res[i]=0;
        }
        res[n-1]=res[n-1]=0;
        for(int i=0;i<m;i++){
            scanf("%d%d",&a,&b);
            --a;--b;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        scanf("%d",&k);
        while(k--){
            scanf("%d%d",&a,&b);
            --a;
            mark[a]=b;
        }
        ll ans=0;
        for(int i=0;i<31;i++){
            init();
            int cur = (1<<i);
            src=n-1;
            snk=n-2;
            for(int u=0;u<nodes;u++){
                if(mark[u]!=-1 &&(mark[u]&(cur))){
                    addAug(src, u,INT_MAX);
                }else if(mark[u]!=-1){
                    addAug(u, snk, INT_MAX);
                }
                for(auto v:adj[u]){
                    addAug(u,v,1);
                }
            }
            int f = dinic();
            vid++;
            solve(src, cur);
            ans+=f*1ll*cur;
        }
        for(int i=0;i<nodes;i++){
            printf("%d\n", res[i]);
        }

    }
    return 0;
}
