//https://www.spoj.com/problems/OTOCI/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

#define neig(u, v, e) for(int e=head[u], v; ~e&&(v=to[e], 1); e=nxt[e])

const int N = 1e5+5, E=1e5+5, Q=3e5+5;
int head[N], nxt[E], to[E],edgcnt;
int id[N], dpth[N], sz[N],par[N],heavyCH[N], chhead[N], inToNo[N], noToIn[N];
int curpos;
int n;
int a[N];
bool vis[N];
int seg[1<<16];

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        seg[id]=a[inToNo[ns]];
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    seg[id]=seg[l]+seg[r];
}

void upd(int qp, int qv, int id=0, int ns=0, int ne=n-1){
    if(ns>qp || ne<qp)
        return ;
    if(ns==ne){
        seg[id]=qv;
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qp, qv,l, ns, md);
    upd(qp, qv,r, md+1, ne);
    seg[id]=seg[l]+seg[r];
}

int get(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    if(qs>ne || qe<ns){
        return 0;
    }
    if(qs<=ns && qe>=ne)
        return seg[id];
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return get(qs, qe, l, ns, md) + get(qs, qe, r, md+1,ne);

}

int getid(int u){
    return (id[u]==u?u : id[u]=getid(id[u]));
}


bool sameset(int u, int v){
    return getid(u)==getid(v);
}

void uni(int u, int v){
    u=getid(u);
    v=getid(v);
    if(u==v)
        return ;
    id[u]=v;
}

void initdsu(){
    for(int i=0;i<n;i++)
        id[i]=i;
}

void init(){
    memset(head,-1, n*sizeof(head[0]));
    edgcnt=0;
    curpos=0;
    par[0]=-1;
    dpth[0]=0;
    initdsu();
}

void addEdge(int a, int b){
    nxt[edgcnt]=head[a];
    head[a]=edgcnt;
    to[edgcnt]=b;
    edgcnt++;
}

void addBiEdge(int a, int b){
    addEdge(a,b);
    addEdge(b,a);
}

void calcsz(int u=0){
    sz[u]=1;
    heavyCH[u]=-1;
    int mxv=-1;
    int mxs = 0;
    neig(u,v,e){
        if(v==par[u])
            continue;
        par[v]=u;
        dpth[v]=dpth[u]+1;
        calcsz(v);
        sz[u]+=sz[v];
        if(sz[v]>mxs){
            mxs=sz[v];
            mxv=v;
        }
    }
    if(mxs!=-1 && 2*mxs>=sz[u])
        heavyCH[u]=mxv;
}

void HLD(int u=0, int c=0){
    if(u==-1)
        return ;
    vis[u]=1;
    chhead[u]=c;
    inToNo[curpos]=u;
    noToIn[u]=curpos;
    curpos++;
    HLD(heavyCH[u], c);
    neig(u,v,e){
        if(v==par[u] || v==heavyCH[u])
            continue;
        HLD(v,v);
    }
}

char qu[20];
int qt[Q],qa[Q], qb[Q],q;

int getans(int a, int b){
    int res=0;
    while(chhead[a]!=chhead[b]){

        if(dpth[chhead[a]]<dpth[chhead[b]])
            swap(a,b);
        res+=get(noToIn[chhead[a]], noToIn[a]);
        a=par[chhead[a]];
    }

    if(dpth[a]>dpth[b])
        swap(a,b);
    res+=get(noToIn[a], noToIn[b]);
    return res;
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&n);
    init();
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&q);
    for(int i=0;i<q;i++){
        scanf("%s",qu);
        scanf("%d%d",&qa[i], &qb[i]);
        if(qu[0]=='e'){
            qt[i]=0;
        }else if(qu[0]=='b'){
            qt[i]=1;
            if(!sameset(--qa[i], --qb[i])){
                uni(qa[i], qb[i]);
                addBiEdge(qa[i], qb[i]);
            }
        }else{
            qt[i]=2;
        }
    }
    for(int i=0;i<n;i++){
        if(vis[i])
            continue;
        calcsz(i);
        HLD(i,i);
    }
    build();
    initdsu();
    for(int i=0;i<q;i++){
        switch(qt[i]){
        case 0 :
            if(sameset(qa[i]-1, qb[i]-1)){
                printf("%d\n", getans(qa[i]-1, qb[i]-1));
            }else{
                puts("impossible");
            }
            break;
        case 1 :
            if(!sameset(qa[i], qb[i])){
                uni(qa[i], qb[i]);
                puts("yes");
            }else{
                puts("no");
            }
            break;
        case 2 :
            qa[i]--;
            upd(noToIn[qa[i]],qb[i]);
            break;
        }
    }
    return 0;
}
