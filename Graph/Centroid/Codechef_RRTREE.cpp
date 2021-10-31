//https://www.codechef.com/problems/RRTREE

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 +5 ;

vector<int> adj[N];
int par[N], heavyCH[N], chhead[N], parch[N], dpth[N];
int res;
int n;
bool done[N];
int mxdist[N];
int sz[N];
multiset<int> ss[N];
map<int,int> maa[N];


void init(){
    for(int i=0;i<n;i++){
        adj[i].clear();
        par[i]=-1;
        done[i]=0;
        mxdist[i]=0;
        ss[i].clear();
        maa[i].clear();
    }
    res=0;
}

void dfs(int u=0, int p=-1,int d=0){
    dpth[u]=d;
    heavyCH[u]=-1;
    int mx=-1;
    int mxv=-1;
    sz[u]=1;
    parch[u]=p;
    for(auto v: adj[u]){
        if(v==p)
            continue;
        dfs(v,u,d+1);
        sz[u]+=sz[v];
        if(mx<sz[v]){
            mx=sz[v];
            mxv=v;
        }
    }
    if(2*mx>sz[u])
        heavyCH[u]=mxv;
}
void buildHLD(int u=0, int c=0){
    if(u==-1)
        return ;
    chhead[u]=c;
    buildHLD(heavyCH[u],c);
    for(auto v:adj[u]){
        if(v==parch[u] || v==heavyCH[u])
            continue;
        buildHLD(v,v);

    }
}

int HLD_LCA(int u, int v){
    while(chhead[u]!=chhead[v]){
        if(dpth[chhead[u]]<dpth[chhead[v]]){
            swap(u,v);
        }
        u=parch[chhead[u]];
    }
    if(dpth[u]>dpth[v])
        swap(u,v);
    return u;
}

int getdist(int u, int v){
    int lca = HLD_LCA(u,v);
    return dpth[u]+dpth[v]-2*dpth[lca];
}

void calcsz(int u, int p=-1){
    sz[u]=1;
    for(auto v:adj[u]){
        if(done[v] || p==v)
            continue;
        calcsz(v,u);
        sz[u]+=sz[v];
    }
}

int getcentroid(int u, int cursz, int p=-1){
    for(auto v: adj[u]){
        if(done[v] || p==v)
            continue;
        if(2*sz[v]>cursz)
            return getcentroid(v,cursz, u);
    }
    return u;
}


int buildCentroid(int u){
    calcsz(u);
    int subsz = sz[u];
    int src = getcentroid(u,subsz);
    done[src]=1;

    for(auto v:adj[src]){
        if(done[v])
            continue;
        int x = buildCentroid(v);
        par[x]=src;
    }
    return src;
}

int getmax(int u){
    if(ss[u].size()==0)
        return 0;
    return - *ss[u].begin();
}


void upd(int u){
    int cur=u;
    res=max(res, getmax(u));
    ss[u].insert(0);
    while(par[cur]!=-1){
        int d = getdist(u,par[cur]);
        int x = maa[par[cur]][cur];
        if(x!=0)
            ss[par[cur]].erase(ss[par[cur]].find(-x));
        int y = getmax(par[cur]);
        x=max(x,d);
        y+=x;
        res=max(res, y);
        maa[par[cur]][cur]=x;
        ss[par[cur]].insert(-x);
        cur=par[cur];
    }
}

int t,x;

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        init();
        for(int i=1;i<n;i++){
            scanf("%d",&x);
            --x;
            adj[i].pb(x);
            adj[x].pb(i);
        }

        dfs();
        buildHLD();

        int src = buildCentroid(0);
        for(int i=0;i<n;i++){
            ss[i].insert(1e9);
        }
        upd(0);
        for(int i=1;i<n;i++){
            upd(i);
            cout << res << endl;
        }

    }
    return 0;
}
