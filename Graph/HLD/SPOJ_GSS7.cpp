//https://www.spoj.com/problems/GSS7/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e6 + 5, E=1e6+5;

#define neig(u,v,e) for(int e=head[u],v;~e && ((v=to[e]), 1);e=nxt[e])

int par[N], sz[N], dpth[N], pos[N], chhead[N], HeavyCH[N];
ll head[E], nxt[E], to[E],vl[N];
int n, CurPos, edgcnt, posToNode[N];

struct Data{
    ll pre,suf, sum, mx,lazy;
    bool haslazy;
    Data(){
        sum=0;
        lazy=haslazy=0;
        pre=suf=mx=-1e9;
    }
    Data(ll v):pre(max(0ll,v)),suf(max(0ll,v)), sum(v), mx(max(0ll,v)), lazy(0ll),haslazy(0){}

    void setlazy(ll v, int st, int en){
        ll sz = en-st+1;
        sum=v*sz;
        pre = (v<0?0:sum);
        suf = mx = pre;
        haslazy=1;
        lazy=v;
    }
} seg[1<<18];


void push_down(int id, int ns, int ne){
    Data & nd = seg[id];
    if(!nd.haslazy) return ;
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    seg[l].setlazy(nd.lazy, ns , md);
    seg[r].setlazy(nd.lazy, md+1, ne);
    nd.haslazy=0;
}

Data mrg(const Data &lf, const Data &rt){
    Data res;
    res.sum = lf.sum + rt.sum;
    res.mx = max(max(lf.mx, rt.mx),lf.suf+rt.pre);
    res.pre = max(lf.pre, lf.sum+rt.pre);
    res.suf = max(rt.suf, rt.sum+lf.suf);
    return res;
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
    posToNode[CurPos]=u;
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
        seg[id] = Data(vl[posToNode[ns]]);
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns + (ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    seg[id]=mrg(seg[l],  seg[r]);
}
Data query(int qs , int qe, int id=0, int ns=0, int ne=n-1){

    if(qs>ne || qe<ns)
        return Data();
    if(qs<=ns && qe>=ne){
        return seg[id];
    }
    push_down(id, ns, ne);
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    Data ld = query(qs, qe, l, ns, md);
    Data rd = query(qs, qe, r, md+1, ne);
    return mrg(ld, rd);
}

void upd(int qs, int qe, ll qv , int id=0,int ns=0, int ne=n-1){
    if(qs>ne || qe<ns)
        return ;
    if(qs<=ns &&  qe>=ne){
        seg[id].setlazy(qv, ns, ne);
        return ;
    }
    push_down(id, ns, ne);
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qs, qe, qv, l, ns, md);
    upd(qs, qe, qv, r, md+1, ne);
    seg[id]=mrg(seg[l], seg[r]);
}
ll getMax(int u, int v){
    Data du, dv;
    while(chhead[u]!=chhead[v]){
        if(dpth[chhead[v]]>dpth[chhead[u]]){
            swap(u,v);
            swap(du, dv);
        }
        Data tmp = query(pos[chhead[u]], pos[u]);
        du=mrg(tmp, du);
        u=par[chhead[u]];
    }
    if(dpth[u]>dpth[v]){
        swap(u,v);
        swap(du, dv);
    }
    auto tmp = query(pos[u], pos[v]);
    dv = mrg(tmp, dv);
    swap(dv.pre, dv.suf);
    return  mrg(dv, du).mx;
}

void update(int u, int v, ll val){
    while(chhead[u]!=chhead[v]){
        if(dpth[chhead[v]]>dpth[chhead[u]]){
            swap(u,v);
        }
        upd(pos[chhead[u]], pos[u], val);
        u=par[chhead[u]];
    }
    if(dpth[u]>dpth[v]){
        swap(u,v);
    }
    upd(pos[u], pos[v],val);

}


int  x,y;
ll c;
int ty;
int q;

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&n);
    init();

    for(int i=0;i<n;i++)
        cin >> vl[i];

    for(int i=1;i<n;i++){
        cin >> x >> y;
        addBiEdge(--x,--y);
    }
    calcsz();
    HLD();
    build();
    scanf("%d",&q);
    while(q--){
        scanf("%d",&ty);
        if(ty==1){
            cin >> x >> y;
            cout << getMax(--x,--y) << endl;
        }else{
            cin >> x >> y >> c;
            update(--x, --y, c);
        }
    }



    return 0;
}
