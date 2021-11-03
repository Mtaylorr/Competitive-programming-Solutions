//https://codeforces.com/contest/587/problem/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5  +5 ;

int n,m,q,u,v,a;
vector<int> c[N];
vector<int> tree[4*N +2];
int dpth[N], chhead[N], heavyCH[N],par[N];
int ndcnt=0;
int inToNo[N], noToIn[N], sz[N];
vector<int> adj[N];

void calcsz(int u=0, int p=-1,int d=0){
    par[u]=p;
    dpth[u]=d;
    sz[u]=1;
    int mx = -1;
    int mxv=-1;
    heavyCH[u]=-1;
    for(auto v:adj[u]){
        if(v==p)
            continue;
        calcsz(v,u,d+1);
        sz[u]+=sz[v];
        if(sz[v]>mx)
        {
            mx=sz[v];
            mxv=v;
        }
    }
    heavyCH[u]=mxv;

}


void buildHLD(int u=0, int c=0){
    if(u==-1)
        return ;
    chhead[u]=c;
    noToIn[u]=ndcnt;
    inToNo[ndcnt]=u;
    ndcnt++;
    buildHLD(heavyCH[u],c);
    for(auto v:adj[u]){
        if(v==par[u] || v==heavyCH[u])
            continue;
        buildHLD(v,v);
    }
}

void clip(vector<int>&v){
    while(v.size()>10)
        v.pop_back();
}

void mrg(vector<int>& a , vector<int> &b, vector<int>& res){
    res.clear();
    merge(a.begin(), a.end(),
          b.begin(), b.end(),
          inserter(res, res.begin()));
    clip(res);
}

void mrg(vector<int> & a , vector<int> &b){
    vector<int> tmp;
    mrg(a,b,tmp);
    b = tmp;
}

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        tree[id]=c[inToNo[ns]];
        clip(tree[id]);
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    mrg(tree[l], tree[r], tree[id]);
}

void get(int qs, int qe,vector<int> &res, int id=0, int ns=0, int ne=n-1){
    if(qs>ne || ns>qe)
        return ;
    if(qs<=ns && qe>=ne){
        mrg(tree[id],res);
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    get(qs, qe,res, l, ns, md);
    get(qs, qe,res, r, md+1, ne);
}

void getans(int u, int v, int a, vector<int> &res){
    while(chhead[u]!=chhead[v]){
        if(dpth[chhead[u]]<dpth[chhead[v]])
            swap(u,v);
        get(noToIn[chhead[u]], noToIn[u],res);
        u=par[chhead[u]];
    }
    if(dpth[u]>dpth[v])
        swap(u,v);
    get(noToIn[u], noToIn[v],res);
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        --u;--v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for(int i=0;i<m;i++){
        scanf("%d",&u);
        c[--u].pb(i);
    }
    for(int i=0;i<n;i++){
        sort(c[i].begin(), c[i].end());
    }
    calcsz();
    buildHLD();
    build();
    while(q--){
        scanf("%d%d%d",&u,&v,&a);
        --u;--v;
        vector<int> res;
        getans(u,v,a,res);
        int s = min(a,  (int)res.size());
        printf("%d ", s);
        for(int i=0;i<s;i++){
            printf("%d ", res[i]+1);
        }
        puts("");
    }
    return 0;
}
