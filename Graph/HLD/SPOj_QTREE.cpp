//https://www.spoj.com/problems/QTREE/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e5 + 5, E=1e5+5;

#define neig(u,v,e) for(int e=head[u],v;~e && ((v=to[e]), 1);e=nxt[e])

vector<vector<int> > adj;
int par[N], sz[N], dpth[N], pos[N], chhead[N], HeavyCH[N];
int head[E], nxt[E], to[E], cst[N],vl[N];
int n, CurPos, edgcnt, invpos[N];

int seg[1<<16];


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

void init(){
    CurPos=0;
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
    par[0]=-1;
}

void calcsz(int u=0){
    HeavyCH[u]=-1;
    sz[u]=1;
    int mx=0, mxv;
    neig(u,v,e){
        if(par[u]==v)
            continue;
        par[v]=u;
        vl[v]=cst[e];
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
void HLD(int u=0,int c=0){
    if(u==-1)
        return ;
    invpos[CurPos]=u;
    pos[u]=CurPos++;

    chhead[u]=c;
    HLD(HeavyCH[u],c);
    neig(u,v,e){
        if(v==par[u])
            continue;
        if(v==HeavyCH[u])
            continue;
        HLD(v,v);
    }
}



void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        seg[id] = vl[invpos[ns]];
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns + (ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    seg[id]=max(seg[l],  seg[r]);
}
int query(int qs , int qe, int id=0, int ns=0, int ne=n-1){
    if(qs>ne || qe<ns)
        return INT_MIN;
    if(qs<=ns && qe>=ne){
        return seg[id];
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return max(query(qs, qe, l, ns, md), query(qs, qe, r, md+1, ne));
}

void upd(int qp, int qv , int id=0,int ns=0, int ne=n-1){
    if(ns >qp || ne<qp)
        return ;
    if(ns==ne){
        seg[id]=qv;
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qp, qv, l, ns, md);
    upd(qp, qv, r, md+1, ne);
    seg[id]=max(seg[l], seg[r]);
}
int getMax(int u, int v){
    int mx = INT_MIN;
    while(chhead[u]!=chhead[v]){
        if(dpth[chhead[v]]>dpth[chhead[u]])
            swap(u,v);
        mx=max(mx, query(pos[chhead[u]], pos[u]));
        u=par[chhead[u]];
    }
    if(dpth[u]>dpth[v])
        swap(u,v);
    mx=max(mx, query(pos[u]+1, pos[v]));
    return mx;
}


int t;
int s, x,y,c;
int q;
char qu[10];

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    int tt=0;
    while(t--){
        scanf("%d",&n);
        init();
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&x,&y,&c);
            addBiEdge(--x,--y,c);
        }
        calcsz();
        HLD();
        build();
        while(1){
            scanf("%s",qu);
            if(qu[0]=='D')
                break;
            scanf("%d%d",&x,&y);
            if(qu[0]=='Q'){

                printf("%d\n", getMax(--x, --y));
            }else{
                x--;
                x*=2;
                int ch;
                if(par[to[x]]==to[x^1]){
                    ch=to[x];
                }else{
                    ch=to[x^1];
                }
                upd(pos[ch], y);
            }
        }

    }

    return 0;
}
