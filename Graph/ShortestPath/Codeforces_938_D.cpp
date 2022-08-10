//https://codeforces.com/problemset/problem/938/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 2*(2e5 + 5);
const int MOD = 1e9 + 7;

#define neig(u,e,v) for(int e=head[u], v;(~e)&&(v=to[e],1);e=nxt[e])
int nxt[E], head[N],to[E], edgcnt=0;
ll cst[E], a[N];
int n,m;

void addEdege(int u, int v, ll c){
    nxt[edgcnt]=head[u];
    to[edgcnt]=v;
    cst[edgcnt]=c;
    head[u]=edgcnt++;
}
void addBiEdge(int u, int v, ll c){
    addEdege(u,v,c);
    addEdege(v,u,c);
}
ll dist[N];
bool vis[N];
void dijk(){

    set<pair<ll,int> > ss;
    for(int i=0;i<n;i++){
        dist[i]=a[i];
        ss.insert({dist[i],i});
    }
    pair<ll,int> p;
    while(!ss.empty()){
        p=*ss.begin();
        ss.erase(ss.begin());
        int u = p.se;
        ll w = p.fi;
        if(vis[u])
            continue;
        vis[u]=1;
        neig(u,e,v){
            if(dist[v]>w+2*cst[e]){
                dist[v]=w+2*cst[e];
                ss.insert({dist[v],v});
            }
        }
    }
}

int u,v;
ll c;

int main() {
    freopen("input.txt", "r", stdin);
    memset(head, -1, sizeof(head));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> u >> v >> c;
        u--;v--;
        addBiEdge(u,v,c);
    }
    for(int i=0;i<n;i++)
        cin >> a[i];

    dijk();
    for(int i=0;i<n;i++){
        cout << dist[i]<< " ";
    }

    return 0;

}
