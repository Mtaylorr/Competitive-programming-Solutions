//https://www.spoj.com/problems/LCA/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e3 + 5;
vector<vector<int> > adj;
int par[N], sz[N], dpth[N], pos[N], chhead[N], HeavyCH[N];
int n, CurPos;


void init(){
    adj.clear();
    adj.resize(n);
    CurPos=0;
}

void calcsz(int u){
    HeavyCH[u]=-1;
    sz[u]=1;
    int mx=0, mxv;
    for(auto v:adj[u]){
        if(par[u]==v)
            continue;
        par[v]=u;
        dpth[v]=dpth[u]+1;
        calcsz(v);
        if(sz[v]>mx){
            mx = sz[v];
            mxv = v;
        }
        sz[u]+=sz[v];
    }
    if(mx*2>sz[u]){
        HeavyCH[u]=mxv;
    }
}
void HLD(int u,int c){
    if(u==-1)
        return ;
    pos[CurPos++]=u;
    chhead[u]=c;
    HLD(HeavyCH[u],c);
    for(auto v:adj[u]){
        if(v==par[u])
            continue;
        if(v==HeavyCH[u])
            continue;
        HLD(v,v);
    }
}

int LCA_HLD(int u, int v){
    while(chhead[u]!=chhead[v]){
        if(dpth[chhead[v]]>dpth[chhead[u]])
            swap(u,v);
        u=par[chhead[u]];
    }
    if(dpth[u]>dpth[v])
        swap(u,v);
    return u;
}

int t;
int s, x,y;
int q;

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    int tt=0;
    while(t--){
        scanf("%d",&n);
        init();
        for(int i=0;i<n;i++){
            scanf("%d",&s);
            for(int j=0;j<s;j++){
                scanf("%d",&x);
                --x;
                adj[i].pb(x);
            }
        }
        calcsz(0);
        HLD(0,0);
        scanf("%d",&q);
        printf("Case %d:\n", ++tt);
        while(q--){
            scanf("%d%d",&x,&y);
            --x;--y;
            printf("%d\n",LCA_HLD(x,y)+1);
        }
    }

    return 0;
}
