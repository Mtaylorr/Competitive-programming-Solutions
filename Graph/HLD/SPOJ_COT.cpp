//https://www.spoj.com/problems/COT/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

#define neig(u,v,e) for(int e=head[u], v; ~e&&(v=to[e], 1); e=nxt[e])

const int N = 1e6 + 5, E=1e6+5;

int vl[N], pos[N], indexToNode[N],par[N], chhead[N], heavyCH[N], sz[N];
int dpth[N];
int head[E], nxt[E], to[E];
int curpos,edgcnt;
int n;

vector<int> seg[N];

void addEdge(int u, int v){
    nxt[edgcnt] = head[u];
    head[u]=edgcnt;
    to[edgcnt]=v;
    edgcnt++;
}

void addBiEdge(int u, int v){
    addEdge(u,v);
    addEdge(v,u);
}

void init(){
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
    curpos=0;
    par[0]=-1;
}

void calcsz(int u=0){
    sz[u]=1;
    int mxv=0, mx=-1;
    heavyCH[u]=-1;
    neig(u,v,e){
        if(v==par[u])
            continue;
        par[v]=u;
        dpth[v]=dpth[u]+1;
        calcsz(v);
        if(sz[v]>mxv){
            mxv=sz[v];
            mx=v;
        }
        sz[u]+=sz[v];
    }
    if(mx!=-1)
        heavyCH[u]=mx;

}

void HLD(int u=0, int c=0){
    if(u==-1)
        return ;
    chhead[u]=c;
    indexToNode[pos[u]=curpos++] = u;
    HLD(heavyCH[u],c);
    neig(u,v,e){
        if(v==par[u] || v==heavyCH[u])
            continue;
        HLD(v,v);
    }
}

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        seg[id] = {vl[indexToNode[ns]]};
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    merge(seg[l].begin(), seg[l].end(),
          seg[r].begin(), seg[r].end(),
          inserter(seg[id], seg[id].begin()));
}

int get(int qs, int qe, ll qv , int id=0, int ns=0, int ne=n-1){
    if(ns>qe || ne<qs){
        return 0;
    }
    if(qs<=ns && qe>=ne){
        return lower_bound(seg[id].begin(), seg[id].end(), qv+1)-seg[id].begin();
    }
    int l = 2*id +1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return get(qs, qe, qv,l, ns, md)+get(qs, qe, qv, r, md+1, ne);
}

int getLess(int u, int v, ll k){
    int res=0;
    while(chhead[u]!=chhead[v]){
        if(dpth[chhead[v]]>dpth[chhead[u]]){
            swap(u,v);
        }
        res+=get(pos[chhead[u]], pos[u],k);
        u=par[chhead[u]];
    }
    if(dpth[u]>dpth[v]){
        swap(u,v);
    }
    res+=get(pos[u], pos[v],k);
    return res;
}

ll getAns(int u, int v , int k){
    ll l = -1e18, r = 1e18;
    while(l<r){
        ll md = (l+r)/2;
        if(getLess(u,v,md)<k){
            l=md+1;
        }else{
            r=md;
        }
    }
    return l;
}
int q;
int x,y,k;
int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d",&n,&q);
    init();
    for(int i=0;i<n;i++)
        scanf("%d",&vl[i]);

    for(int i=0;i<n-1;i++){
        scanf("%d%d",&x,&y);
        --x;--y;
        addBiEdge(x,y);
    }
    calcsz();
    HLD();
    build();
    while(q--){
        scanf("%d%d%d",&x,&y,&k);
        printf("%lld\n", getAns(--x,--y, k));
    }




    return 0;
}
