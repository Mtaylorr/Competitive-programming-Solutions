//https://codeforces.com/contest/22/problem/E

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5  +5 ;

int f[N],n;
int par[N];
bool vis[N];
int knows[N];
vector<int> adj[N];
vector<int> ord;
vector<int> leafs[N];
int cand[N];
vector<pair<int,int> > ans;

void dfs(int u=0){
    vis[u]=1;
    for(auto v:adj[u]){
        if(vis[v])
            continue;
        dfs(v);
    }
    ord.pb(u);
}

void setpar(int u){
    vis[u]=1;
    int nb=0;
    for(auto v:adj[u]){
        if(vis[v])
            continue;
        nb++;
        par[v]=par[u];
        setpar(v);
    }
    if(nb==0){
        cand[par[u]]=u;
    }
}


int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&n);
    int x = 0;
    for(int i=0;i<n;i++){
        scanf("%d",&f[i]);
        f[i]--;
        knows[f[i]]=1;
        x=f[i];
        adj[f[i]].pb(i);
    }

    for(int i=0;i<n;i++){
        if(!vis[i]){
            dfs(i);
        }
    }
    memset(vis, 0, sizeof(vis));
    reverse(ord.begin(),ord.end());
    for(auto u:ord){
        if(vis[u])
            continue;
        par[u]=u;
        setpar(u);
    }
    vector<int> pars ;
    for(int i=0;i<n;i++){
        if(par[i]==i){
            pars.pb(i);
        }
    }
    for(int i=0;i<n;i++){
        if(knows[i]==0){
            leafs[par[i]].pb(i);
        }
    }
    for(int i=0;i<pars.size();i++){
        int cur = pars[i];
        int nex = pars[(i+1)%pars.size()];
        if(leafs[nex].size()!=0)
            for(auto v:leafs[nex]){
               ans.pb({cur+1, v+1});
            }
        else{
            if(nex!=cur)
                ans.pb({cur+1, cand[nex]+1});
        }
    }
    cout << ans.size() << endl;
    for(auto u:ans){
        cout << u.fi << " " << u.se << endl;
    }


    return 0;
}
