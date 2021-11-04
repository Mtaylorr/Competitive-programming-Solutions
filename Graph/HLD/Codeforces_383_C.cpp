//https://codeforces.com/contest/383/problem/C

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5  +5 ;

vector<int> adj[N];
int n,m,a[N];
int chhead[N], heavych[N], dpth[N], sz[N], par[N];
int tree[N], idToNd[N], ndToIn[N];
int ndcnt=1;
int u,v,ty;

void upd(int x, int v){
    for(;x<=n;x+=(x)&(-x)){
        tree[x]+=v;
    }
}

int getprefix(int x){
    if(x<=0)
        return 0;
    int res=0;
    for(;x;x-=(x)&(-x))
        res+=tree[x];
    return res;
}

int get(int qs, int qe){
    return getprefix(qe)-getprefix(qs-1);
}


void calcsz(int u=0){
    heavych[u]=-1;
    sz[u]=1;
    int mxv=-1;
    int mx=-1;
    for(auto v:adj[u]){
        if(v==par[u])
            continue;
        dpth[v]=dpth[u]+1;
        par[v]=u;
        calcsz(v);
        sz[u]+=sz[v];
        if(mx<sz[v]){
            mx=sz[v];
            mxv=v;
        }
    }
    if(2*mx>sz[u]){
        heavych[u]=mxv;
    }
}

void buildHLD(int u=0, int c=0){
    if(u==-1)
        return ;
    ndToIn[u]=ndcnt++;
    chhead[u]=c;
    buildHLD(heavych[u], c);
    for(auto v:adj[u]){
        if(v==par[u]|| v==heavych[u])
            continue;
        buildHLD(v,v);
    }
}
int getans(int u){
    int res=0;
    while(u!=-1){
        res+=get(ndToIn[chhead[u]], ndToIn[u]);
        u=par[chhead[u]];
    }
    return res;
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        --u;--v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    par[0]=-1;
    dpth[0]=0;
    calcsz();
    buildHLD();
    while(m--){
        scanf("%d",&ty);
        if(ty==1){
            scanf("%d%d",&u,&v);
            --u;
            if(dpth[u]%2){
                upd(ndToIn[u], v);
            }else{
                upd(ndToIn[u], -v);
            }
        }else{
            scanf("%d",&u);
            --u;
            int res = getans(u);
            if(dpth[u]%2){
                printf("%d\n",a[u]+res);
            }else{
                printf("%d\n",a[u]-res);
            }
        }
    }
    return 0;
}
