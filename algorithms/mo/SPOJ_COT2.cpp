//https://www.spoj.com/problems/COT2/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 +5 ;

vector<int> a;
int tin[N], tout[N];
vector<int> adj[N];
int par[N];
int dpth[N];
int cst[N],n,m,u,v;
int ti=0;
int qs[N], qe[N], qi[N], qans[N], qlca[N];
int heavyCH[N], chhead[N], sz[N];
int ch[N];
int st, en;
int vis[N];
int sum;

void dfs(int u=0, int p=-1, int d=0){
    tin[u]=ti++;
    a.pb(u);
    sz[u]=1;
    par[u]=p;
    dpth[u]=d;
    int mx = -1;
    int mxv=-1;
    heavyCH[u]=-1;
    for(auto v:adj[u]){
        if(v==p)
            continue;
        dfs(v,u,d+1);
        sz[u]+=sz[v];
        if(sz[v]>mx){
            mx=sz[v];
            mxv=v;
        }
    }
    a.pb(u);
    tout[u]=ti++;
    heavyCH[u]=mxv;
}

void buildHLD(int u=0,int c=0){
    if(u==-1)
        return ;
    chhead[u]=c;
    buildHLD(heavyCH[u], c);
    for(auto v: adj[u]){
        if(v==par[u] || v==heavyCH[u])
            continue;
        buildHLD(v,v);
    }
}


bool isancestor(int u, int v){
    return tin[u]<=tin[v] && tout[u]>=tout[v];
}

int HLD_LCA(int u, int v){
    while(chhead[u]!=chhead[v]){
        if(dpth[chhead[u]]<dpth[chhead[v]])
            swap(u,v);
        u=par[chhead[u]];
    }
    if(dpth[u]>dpth[v])
        swap(u,v);
    return u;
}

map<int,int> code;
set<int> ss;
int freq[int(2e5)];

void change(int u){
    sum-=(freq[cst[u]]>0);
    if(vis[u]){
        freq[cst[u]]--;
        vis[u]=0;
    }else{
        freq[cst[u]]++;
        vis[u]=1;
    }
    sum+=(freq[cst[u]]>0);
}

void update(int cur){
    while(st>qs[cur]){
        change(a[--st]);
    }
    while(en<qe[cur]){
        change(a[++en]);
    }

    while(st<qs[cur]){
        change(a[st++]);
    }
    while(en>qe[cur]){
        change(a[en--]);
    }
}

void mo(){
    int B = sqrt(2*n);
    sort(qi,qi+m,[B](int a, int b){return make_pair(qs[a]/B, qe[a])<make_pair(qs[b]/B,qe[b]);});
    st=0;
    en=-1;
    sum=0;
    for(int i=0;i<m;i++){
        int cur = qi[i];
        update(cur);
        if(qlca[cur]!=-1){
            change(qlca[cur]);
        }

        qans[cur]=sum;
        if(qlca[cur]!=-1){
            change(qlca[cur]);
        }
    }
}


int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",&cst[i]);
        ss.insert(cst[i]);
    }
    int cn=1;
    for(auto u:ss){
        code[u]=cn++;
    }
    for(int i=0;i<n;i++){
        cst[i]=code[cst[i]];
    }
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        --u;--v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs();
    buildHLD();
    for(int i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        --u;--v;
        qi[i]=i;
        qlca[i] = HLD_LCA(u,v);
        if(qlca[i]==u || qlca[i]==v)
            qlca[i]=-1;
        if(isancestor(u,v)){
            qs[i] = tout[v];
            qe[i] = tout[u];
        }else if(isancestor(v,u)){
            qs[i] = tout[u];
            qe[i] = tout[v];
        }else{
            if(tin[u]>tin[v])
                swap(u,v);
            qs[i] = tout[u];
            qe[i] = tin[v];
        }
    }
    mo();
    for(int i=0;i<m;i++){
        cout << qans[i] << "\n";
    }

    return 0;
}
