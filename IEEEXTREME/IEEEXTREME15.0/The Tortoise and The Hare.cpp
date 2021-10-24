#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


#define neig(u,v,e) for(int e=head[u],v;(e!=-1) && (v=to[e], 1) ; e=nxt[e])

const int N = 1e6 +5 ;

int n,m,s,t;

int head[N], nxt[N], to[N];
int edgcnt=0;
ll cst[N];
void addEdge(int u, int v , int c){
    nxt[edgcnt]=head[u];
    head[u]=edgcnt;
    cst[edgcnt]=c;
    to[edgcnt]=v;
    edgcnt++;
}

void addBiEdge(int u, int v, int c){
    addEdge(u,v,c);
    addEdge(v,u,c);
}

int u,v;
ll c;

ll dist[N];
bool vis[N];
ll dijk(int forb){
    for(int i=0;i<n;i++){
        dist[i]=1e18;
        vis[i]=0;
    }
    dist[s]=0;
    set<pair<ll,int> > pq;
    pq.insert({0,s});
    pair<ll,int> p;
    while(!pq.empty()){
        p=*pq.begin();
        pq.erase(pq.begin());
        int u = p.se;
        ll d = p.fi;
        if(vis[u])
            continue;
        vis[u]=1;
        neig(u,v,e){
            if(vis[v])
                continue;
            if(forb==v)
                continue;
            if(dist[v]>dist[u]+cst[e]){
                dist[v]=dist[u]+cst[e];
                pq.insert({dist[v],v});
            }
        }
    }
    if(dist[t]<1e18){
        return dist[t];
    }
    return -1;

}


int main(){
   // freopen("input.txt", "r", stdin);
    memset(head, -1,sizeof(head));
    scanf("%d%d%d%d",&n,&m,&s,&t);
    s--;t--;
    for(int i=0;i<m;i++){
        scanf("%d%d%lld",&u,&v,&c);
        u--;v--;
        addBiEdge(u,v,c);
    }
    ll ans=0;
    int anscity = -1;
    for(int i=0;i<n;i++){
        if(i==s)
            continue;
        if(i==t)
            continue;
        ll x = dijk(i);
        if(x!=-1 && x>ans){
            ans=x;
            anscity=i;
        }
    }
    if(anscity!=-1){
        cout << anscity+1;
    }else{
        cout << anscity;
    }

    return 0;
}
