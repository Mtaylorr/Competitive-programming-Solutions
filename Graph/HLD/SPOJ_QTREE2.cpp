//https://www.spoj.com/problems/QTREE2/

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

#define neig(u, v, e) for(int e=head[u], v; ~e&&(v=to[e], 1); e=nxt[e])

const int N = 1e5+5, E=1e5+5;

int nxt[2*E], head[N], to[N];
int dpth[N],indexToNode[N], nodeToIndex[N], par[N], heavyCH[N], chhead[N], cst[N];
int edgcnt=0, sz[N],vl[N];
int curpos;
int n;

int sum[1<<15];

void init(){
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
    par[0]=-1;
    curpos=0;
    dpth[0]=0;
    vl[0]=0;
}

void addEdge(int a, int b, int c){
    nxt[edgcnt]=head[a];
    head[a]=edgcnt;
    to[edgcnt]=b;
    cst[edgcnt]=c;
    edgcnt++;
}

void addBiEdge(int a, int b, int c){
    addEdge(a,b,c);
    addEdge(b,a,c);
}

void calcsz(int u=0){
    sz[u]=1;
    heavyCH[u]=-1;
    int mxs=0;
    int mxv=-1;
    neig(u,v,e){
        if(v==par[u])
            continue;
        vl[v]=vl[u]+cst[e];
        par[v]=u;
        dpth[v]=dpth[u]+1;
        calcsz(v);
        sz[u]+=sz[v];
        if(sz[v]>mxs){
            mxs=sz[v];
            mxv=v;
        }
    }
    if(mxv!=-1 && 2*mxs>=sz[u]){
        heavyCH[u]=mxv;
    }
}

void HLD(int u=0, int c=0){
    if(u==-1)
        return ;
    chhead[u]=c;
    indexToNode[curpos]=u;
    nodeToIndex[u]=curpos;
    curpos++;
    HLD(heavyCH[u],c);
    neig(u,v,e){
        if(v==par[u] || v==heavyCH[u])
            continue;
        HLD(v,v);
    }
}


int lcaHLD(int a , int b ){
    while(chhead[a]!=chhead[b]){
        if(dpth[chhead[a]] < dpth[chhead[b]])
            swap(a,b);
        a=par[chhead[a]];
    }
    if(dpth[a]>dpth[b])
        swap(a,b);
    return a;
}

int getDistance(int a, int b){
    int lca = lcaHLD(a,b);
    return vl[a]+vl[b]-2*vl[lca];
}


int getkth(int a, int b, int k){
    int lca = lcaHLD(a,b);
    int d = dpth[a]+dpth[b]-2*dpth[lca];
    if(dpth[a]-dpth[lca]+1<k){
        k-=(dpth[a]-dpth[lca]+1);
        k= dpth[b]-dpth[lca]-k;
        a=b;
    }else{
        k--;
    }
    while(k){
        if(dpth[a]-dpth[chhead[a]]>=k){
            a=par[a];
            k--;
        }
        else{
            k-=(dpth[a]-dpth[par[chhead[a]]]);
            a=par[chhead[a]];
        }
    }

    return a;
}

char qu[10];
int t,a,b,c;


int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        init();
        for(int i=0;i<n-1;i++){
            scanf("%d%d%d",&a,&b,&c);
            a--;b--;
            addBiEdge(a,b,c);
        }
        calcsz();
        HLD();
        while(1){
            scanf("%s",qu);
            if(qu[1]=='O'){
                puts("");
                break;
            }
            if(qu[0]=='D'){
                scanf("%d%d",&a,&b);
                a--;b--;
                printf("%d\n", getDistance(a,b));
            }else{
                scanf("%d%d%d",&a,&b,&c);
                a--;b--;
                printf("%d\n", getkth(a,b,c)+1);
            }
        }
    }
    return 0;
}
