#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 10567201 ;

int x[N],y[N];
int t;
int c[N];
vector<pair<int,int> > adj[N];
int xs,ys,xd,yd;
int B;
int l;
int u,v;
int n;
int dist[1005][105];
bool vis[1005][105];

int getDist(int i, int j){
    double r = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
    return ceil(r);
}

void dijk(){
    for(int i=0;i<n;i++){
        for(int j=0;j<=B;j++){
            dist[i][j]=1e9;
        }
    }
    dist[0][0]=0;
    set<pair<int,pair<int,int> > > pq;
    pq.insert({0,{0,0}});
    pair<int,pair<int,int> > cur;
    while(!pq.empty()){
        cur = *pq.begin();
        pq.erase(pq.begin());
        int u = cur.se.fi;
        int d = cur.se.se;
        int cs = cur.fi;
        if(vis[u][d])
            continue;
        vis[u][d]=1;
        for(auto &v:adj[u]){
            int len = getDist(u,v.fi);
            int ncs = cs + len*c[v.se];
            if(len+d<=B && ncs <=dist[v.fi][len+d]){
                dist[v.fi][len+d] = ncs;
                pq.insert({ncs, {v.fi, len+d}});
            }
        }
    }
}

int main()
{
    //freopen("input.txt", "r",stdin);
    scanf("%d%d",&x[0],&y[0]);
    scanf("%d%d",&x[1],&y[1]);
    scanf("%d",&B);
    scanf("%d",&c[0]);
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        scanf("%d",&c[i]);
    }
    scanf("%d",&n);
    n+=2;
    for(int i=2;i<n;i++){
        scanf("%d%d%d",&x[i],&y[i],&l);
        adj[i].pb({1,0});
        while(l--){
            scanf("%d%d",&u,&v);
            u+=2;
            adj[i].pb({u,v});
            adj[u].pb({i,v});
        }
    }
    for(int i=1;i<n;i++){
        adj[0].pb({i,0});
    }
    dijk();
    int rs=1e9;
    for(int i=0;i<=B;i++){
        rs=min(rs, dist[1][i]);
    }
    if(rs<1e9){
        cout << rs;
    }else{
        puts("-1");
    }
    return 0;
}
