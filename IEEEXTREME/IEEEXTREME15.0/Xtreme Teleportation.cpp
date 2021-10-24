//50%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

#define neig(u,v,e) for(int e=head[u],v;(e!=-1) &&(v=to[e],1);e=nxt[e])
const int N = 1e6 +5 ;
const int MOD = 998244353;

int head[N], nxt[N], to[N];
ll cst[N];
int n,q;
ll dist[1005][1005];

int edgcnt=0;
void addEdge(int a, int b , int c){
    nxt[edgcnt]=head[a];
    head[a]=edgcnt;
    to[edgcnt]=b;
    cst[edgcnt]=c;
    edgcnt++;
}

void addBiEdge(int a, int b, ll c){
    addEdge(a,b,c);
    addEdge(b,a,c);
}


void calcdist(int u, int p, int src){
    neig(u,v,e){
        if(v==p)
            continue;
        dist[src][v]=dist[src][u]+cst[e];
        calcdist(v, u, src);
    }
}

int x,y,c;
ll midist[1005][1005];
int id[N];
set<int> child[N];

vector<pair<ll,pair<int,int> > > vv;

int getid(int u){
    if(id[u]==u)
        return u;
    child[id[u]].erase(u);
    id[u]=getid(id[u]);
    child[id[u]].insert(u);
    return id[u];
}

bool sameset(int u, int v){
    u=getid(u);
    v=getid(v);
    return u==v;
}

void uni(int u, int v){
    u=getid(u);
    v=getid(v);
    if(u==v)
        return ;
    id[u]=v;
    child[v].insert(u);
}

vector<int> l[2];


void findchild(int u, int bit){
    l[bit].pb(u);
    for(auto v:child[u]){
        findchild(v,bit);
    }
}

int main(){
    //freopen("input.txt", "r", stdin);
    memset(head, -1, sizeof(head));
    scanf("%d%d",&n,&q);
    for(int i=0;i<n-1;i++){
        scanf("%d%d%d",&x,&y,&c);
        x--;y--;
        addBiEdge(x,y,c);
    }
    for(int i=0;i<n;i++){
        calcdist(i,-1,i);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            vv.pb({dist[i][j],{i,j}});
        }
    }
    for(int i=0;i<n;i++){
        id[i]=i;
    }
    sort(vv.rbegin(), vv.rend());
    for(auto p:vv){
        int u = p.se.fi;
        int v = p.se.se;
        ll d = p.fi;
        if(sameset(u,v))
            continue;
        l[0].clear();
        l[1].clear();
        findchild(getid(u), 0);
        findchild(getid(v),1);
        for(auto l1:l[0]){
            for(auto l2:l[1]){
                //cout << l1+1 << " " << l2+1 << " " << d << endl;
                midist[l1][l2]=midist[l2][l1]=d;
            }
        }
        uni(u,v);

    }
    while(q--){
        scanf("%d%d",&x,&y);
        x--;y--;
        cout << midist[x][y] << endl;
    }
    return 0;
}
