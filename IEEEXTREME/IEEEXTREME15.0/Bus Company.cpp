//10%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 2e5 +5 ;
const int MOD = 1e9 + 7;

int n,q;
vector<int> adj[N];
int a[N];
int u,v;

ll l[2][2], sum[2][2];
int t;
ll d;
int dist[N];
vector<int> path;
ll res[2];
bool vis[N];
int par[N];
void dfs(int u ,int di = 0){
    if(vis[u])
        return ;
    vis[u]=1;
    dist[u]=di;
    for(auto v: adj[u]){
        if(vis[v])
            continue;
        par[v]=u;
        dfs(v,di+1);
    }
}

void getdist(int u, int p, int ty, int di=0){
    l[a[u]][ty]++;
    sum[a[u]][ty]+=di;
    for(auto v: adj[u]){
        if(p==v)
            continue;
        getdist(v,u,ty, di+1);
    }
}

int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        u--;v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d",&t);
        if(t==1){
            scanf("%d",&u);
            u--;
            a[u]=1-a[u];
        }else{
            scanf("%d%d",&u,&v);
            u--;v--;
            d = 0;

            for(int i=0;i<n;i++){
                vis[i]=0;
                par[i]=-1;
            }
            dfs(u);
            d = dist[v];
            int curv = v;
            path.clear();
            while(curv!=u){
                path.pb(curv);
                curv=par[curv];
            }
            memset(l,0,sizeof(l));
            memset(sum,0, sizeof(sum));
            path.pb(u);
            getdist(u,path[path.size()-2],0);
            getdist(v, par[v],1);
            for(int i=0;i<2;i++){
                res[i] = l[i][0]*sum[i][1] + l[i][1]*sum[i][0] + d*l[i][0]*l[i][1];
            }

            ll tot1 = l[0][0]*l[0][1];
            ll tot2 = l[1][0]*l[1][1];
            if(res[0]==res[1] && res[0]==0){
                cout << "TIE\n";
            }else if(res[0]==0){
                cout << "B\n";
            }else if(res[1]==0){
                cout <<"A\n";
            }
            else if(res[0]*tot2<res[1]*tot1){
                cout <<"A\n";
            }else if(res[0]*tot2>res[1]*tot1){
                cout << "B\n";
            }else{
                cout << "TIE\n";
            }
        }
    }

    return 0;
}
