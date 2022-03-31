//https://codeforces.com/contest/1486/problem/E
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5, E = 2*2e5 + 5;
const int MOD = 1e9 + 7 ;
#define neig(u,e,v) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])

int n,m;
int nxt[E], head[N], to[E], w[E], edgcnt;
ll dist[N][55];
bool vis[N][55];
int x,y,z;

void addEdge(int u, int v, int we){
    nxt[edgcnt]=head[u];
    head[u]=edgcnt;
    to[edgcnt]=v;
    w[edgcnt]=we;
    edgcnt++;
}
void addBiEdge(int u, int v, int w){
    addEdge(u,v,w);
    addEdge(v,u,w);
}

void dijk(){
    set<pair<ll,pair<int,int> > > pq;
    for(int i=0;i<n;i++){
        for(int j=0;j<=50;j++){
            dist[i][j]=1e18;
        }
    }
    dist[0][0]=0;
    pq.insert({0,{0,0}});
    pair<ll,pair<int,int> > pa;
    while(!pq.empty()){
        pa=*pq.begin();
        pq.erase(pq.begin());
        int u = pa.se.fi;
        ll d = pa.fi;
        int b = pa.se.se;
        if(vis[u][b])
            continue;
        vis[u][b]=1;
        neig(u,e,v){
            int nb = w[e];
            if(b){
                nb=0;
            }
            if(vis[v][nb])
                continue;
            ll nd = d;
            if(b)
                nd += (w[e]+b)*(w[e]+b);
            if(dist[v][nb]>nd){
                dist[v][nb]=nd;
                pq.insert({nd,{v,nb}});
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r",stdin);
    memset(head, -1, sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&x,&y,&z);
        --x;
        --y;
        addBiEdge(x,y,z);
    }
    dijk();
    for(int i=0;i<n;i++){
        if(dist[i][0]>1e15){
            printf("-1 ");
        }else{
            printf("%lld ",dist[i][0]);
        }
    }


    return 0;

}
