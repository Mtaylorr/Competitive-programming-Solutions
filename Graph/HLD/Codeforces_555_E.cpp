//https://codeforces.com/contest/555/problem/E

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5  +5 , E=5e5+5;

#define neig(u,v,e) for(int e=head[u],v; (e!=-1) && (v=to[e],1);e=nxt[e])


int nxt[E], head[N], to[E], id[E];
int edgcnt=0;

void addEdge(int a, int b , int i){
    nxt[edgcnt]=head[a];
    head[a]=edgcnt;
    to[edgcnt]=b;
    id[edgcnt]=i;
    edgcnt++;
}

void addBiEdge(int a, int b, int i){
    addEdge(a,b,i);
    addEdge(b,a,i);
}

int n,m,q;
int u,v;
vector<int> adj[N];
int heavych[N], chhead[N], par[N], sz[N], idToNd[N], ndToId[N], dpth[N], ndcnt;
pair<int,int> tree[1<<19], lazy[1<<19];
int timer=0;

int bigcomp[N], lilcomp[N];
bool vis[N];
int disc[N], low[N];
set<int> bridges;
int lilcomps=0;

void dfs(int u, int c){
    vis[u]=1;
    bigcomp[u]=c;
    neig(u,v,e){
        if(vis[v])
            continue;
        dfs(v,c);
    }
}

void findBridges(int u){
    vis[u]=1;
    disc[u]=low[u]=timer++;
    neig(u,v,e){
        if(!vis[v]){
            par[v]=u;
            findBridges(v);
            low[u]=min( low[u], low[v]);
            if(low[v]>disc[u]){
                bridges.insert(id[e]);
            }
        }else if(par[u]!=v){
            low[u]=min( low[u], disc[v]);
        }
    }
}

void calclilcomp(int u, int c){
    vis[u]=1;
    lilcomp[u]=c;
    neig(u,v,e){
        if(bridges.count(id[e]))
            continue;
        if(vis[v])
            continue;
        calclilcomp(v,c);
    }
}

void calcsz(int u, int p=-1, int d=0){
    dpth[u]=d;
    par[u]=p;
    heavych[u]=-1;
    int mxv=-1;
    int mx=-1;
    sz[u]=1;
    vis[u]=1;
    for(auto v:adj[u]){
        if(v==p)
            continue;
        calcsz(v,u,d+1);
        sz[u]+=sz[v];
        if(sz[v]>mx){
            mx=sz[v];
            mxv=v;
        }
    }
    if(2*mx>=sz[u]){
        heavych[u]=mxv;
    }
}

void HLD(int u, int c=0){
    if(u==-1)
        return ;
    vis[u]=1;
    chhead[u]=c;
    ndToId[u]=ndcnt;
    idToNd[ndcnt]=u;
    ndcnt++;
    HLD(heavych[u],c);
    for(auto v:adj[u]){
        if(v==par[u] || v==heavych[u])
            continue;
        HLD(v,v);
    }
}
pair<int,int> mrg(pair<int,int> a, pair<int,int> b){
    return {min(a.fi, b.fi),max(a.se, b.se)};
}

void unlazy(int id , int ns, int ne){
    if(lazy[id].fi==0 && lazy[id].se==0)
        return ;
    tree[id]=mrg(tree[id], lazy[id]);
    if(ns!=ne){
        int l = 2*id+1;
        int r = l+1;
        lazy[l]=mrg(lazy[l], lazy[id]);
        lazy[r]=mrg(lazy[r], lazy[id]);
    }
    lazy[id]={0,0};
}

void upd(int qs, int qe ,int v,  int id=0, int ns=0,int ne=lilcomps){
    unlazy(id , ns,ne);
    if(qs>ne || qe<ns)
        return ;
    if(qs<=ns && qe>=ne){
        lazy[id]=mrg(lazy[id], {v,v});
        unlazy(id, ns, ne);
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns + (ne-ns)/2;
    upd(qs, qe, v, l, ns, md);
    upd(qs, qe, v, r, md+1, ne);
    tree[id]=mrg(tree[l], tree[r]);

}

pair<int,int> get(int qs, int qe, int id=0, int ns=0, int ne=lilcomps){
    unlazy(id , ns, ne);
    if(qs>qe)
        return {0,0};
    if(qs>ne || qe<ns){
        return {0,0};
    }
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns + (ne-ns)/2;
    return mrg(get(qs, qe, l , ns, md), get(qs, qe, r, md+1,ne));
}


int updHLD(int u, int v){
    int cur=1;
    pair<int,int> res;
    while(chhead[u]!=chhead[v]){
        if(dpth[chhead[u]]<dpth[chhead[v]]){
            swap(u,v);
            cur*=-1;
        }
        res=get(ndToId[chhead[u]], ndToId[u]);
        if(res.fi==-cur  || res.se==-cur){
            return -1;
        }
        upd(ndToId[chhead[u]], ndToId[u], cur);
        u=par[chhead[u]];
    }
    cur*=-1;
    if(dpth[u]>dpth[v]){
        swap(u,v);
        cur*=-1;
    }
    res=get(ndToId[u]+1, ndToId[v]);
    if(res.fi==-cur  || res.se==-cur){
        return -1;
    }
    upd(ndToId[u]+1, ndToId[v],cur);
    return 0;
}



int main(){
    freopen("input.txt", "r", stdin);
    memset(head, -1, sizeof(head));
    scanf("%d%d%d",&n,&m,&q);
    for(int i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        --u;--v;
        addBiEdge(u,v,i);
    }
    int c=0;
    for(int i=0;i<n;i++){
        if(!vis[i])
            dfs(i,c++);
    }
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;i++){
        if(vis[i])
            continue;
        findBridges(i);
    }

    memset(vis, 0, sizeof(vis));
    c=0;
    for(int i=0;i<n;i++){
        if(vis[i])
            continue;
        calclilcomp(i,c++);
    }

    lilcomps=c;
    for(int u=0;u<n;u++){
        neig(u,v,e){
            if(lilcomp[u]!=lilcomp[v])
                adj[lilcomp[u]].pb(lilcomp[v]);
        }
    }

    memset(vis,0,sizeof(vis));
    for(int i=0;i<lilcomps;i++){
        if(vis[i])
            continue;
        calcsz(i);
    }
    memset(vis, 0, sizeof(vis));
    for(int i=0;i<lilcomps;i++){
        if(vis[i])
            continue;
        HLD(i,i);
    }
    while(q--){
        scanf("%d%d",&u,&v);
        --u;--v;
        if(bigcomp[u]!=bigcomp[v]){
            cout << "No\n";
            return 0;
        }
        u = lilcomp[u];
        v = lilcomp[v];
        if(u==v)
            continue;
        int res = updHLD(u,v);
        if(res==-1){
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    return 0;
}
