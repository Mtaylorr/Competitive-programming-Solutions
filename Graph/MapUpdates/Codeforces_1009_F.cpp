//https://codeforces.com/problemset/problem/1009/F
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6+5;
const int MOD = 1e9 + 7 ;

int n;
vector<int> adj[N];
int id[N];
map<int,int> freq[N];
int depth[N];
int u,v;
int mxcount[N];
int ans[N];
int sz[N];

void mrg(int u, int v){
    if(sz[id[u]]<sz[id[v]]){
        swap(id[u],id[v]);
    }
    if(mxcount[v]>mxcount[u]){
        ans[u]=ans[v];
        mxcount[u]=mxcount[v];
    }else if(mxcount[u]==mxcount[v]){
        ans[u]=min(ans[u], ans[v]);
    }
    sz[id[u]]+=sz[id[v]];
    for(auto e:freq[id[v]]){
        freq[id[u]][e.fi]+=e.se;
        if(freq[id[u]][e.fi]>mxcount[u]){
            mxcount[u]=freq[id[u]][e.fi];
            ans[u]=e.fi;
        }else if(freq[id[u]][e.fi]==mxcount[u]){
            ans[u]=min(ans[u], e.fi);
        }
    }
}

void dfs(int u, int p=-1, int d=0){
    freq[id[u]][d]++;
    depth[u]=d;
    mxcount[u]=1;
    ans[u]=d;
    sz[u]=1;
    for(auto v:adj[u]){
        if(v==p)
            continue;
        dfs(v,u,d+1);
        mrg(u,v);
    }
}

int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        --u,--v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for(int i=0;i<n;i++){
        id[i]=i;
    }
    dfs(0);
    for(int i=0;i<n;i++){
        cout << ans[i]-depth[i] << endl;
    }
    return 0;
}
