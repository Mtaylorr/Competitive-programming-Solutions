//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 300 , E = 2e6 + 5;
const int MOD = 1e9 + 7 ;
#define neig(u,e,v) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int head[N], nxt[E], to[E],edgcnt=0,n;
ll cap[E], cst[N];
int src, snk , vis[N], vid=0,par[N];
ll dist[N];
ll fl[N];
void addEdge(int a, int b, ll cs, ll cp){
    nxt[edgcnt]=head[a];
    to[edgcnt]=b;
    cap[edgcnt]=cp;
    cst[edgcnt]=cs;
    head[a]=edgcnt++;
}

void addAug(int a, int b,ll cs,  ll fcp, ll rcp=0){
    addEdge(a,b,cs, fcp);
    addEdge(b,a,-cs, rcp);
}
void init(){
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
}

bool bellmanford(){
    queue<int> q;
    memset(dist, 63, n*sizeof(dist[0]));
    dist[src]=0;
    vis[src]=++vid;
    fl[src]=1e18;
    fl[snk]=0;
    q.push(src);
    while(q.size()){
        int s = q.size();
        while(s--){
            int u = q.front();
            q.pop();
            vis[u]=0;
            neig(u,e,v){
                if(!cap[e])
                    continue;
                ll d = dist[u]+cst[e];
                if(d<dist[v]){
                    dist[v]=d;
                    fl[v]=min(fl[u], cap[e]);
                    par[v]=e;
                    if(vis[v]!=vid){
                        vis[v]=vid;
                        q.push(v);
                    }
                }else if(dist[v]==d && min(fl[u], cap[e])>fl[v]){
                    dist[v]=d;
                    fl[v]=min(fl[u], cap[e]);
                    par[v]=e;
                    if(vis[v]!=vid){
                        vis[v]=vid;
                        q.push(v);
                    }
                }
            }
        }
    }
    return fl[snk]>0;

}

pair<ll,ll> mcmf(){
    ll f=0, c=0;
    while(bellmanford()){
        f+=fl[snk];
        c+=fl[snk]*dist[snk];
        for(int u=snk;u!=src;u=to[par[u]^1]){
            cap[par[u]]-=fl[snk];
            cap[par[u]^1]+=fl[snk];
        }
    }
    return {f,c};
}
int u,v,m,nodes;
ll w;
ll k,d;
int main(){
    freopen("input.txt", "r", stdin);
    while(~scanf("%d%d",&nodes,&m)){
        n = nodes+1;
        src=0;
        snk=n-1;
        init();
        for(int i=0;i<m;i++){
            scanf("%d%d%lld",&u,&v,&w);
            --u;--v;
            addAug(u,v,w,0);
            addAug(v,u,w,0);
        }
        scanf("%lld%lld",&d,&k);
        for(int i=0;i<edgcnt;i+=2){
            cap[i]=k;
        }

        addAug(nodes-1, snk, 0,d);
        auto rs = mcmf();
        if(rs.fi!=d){
            puts("Impossible.");
        }else{
            printf("%lld\n", rs.se);
        }

    }
    return 0;
}
