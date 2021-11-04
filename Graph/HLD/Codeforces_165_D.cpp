//https://codeforces.com/contest/165/problem/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

#define neig(u,v,e) for(int e=head[u], v;(e!=-1) && (v=to[e],1); e=nxt[e])

const int N = 2e5  +5 ;


int head[N], nxt[N], to[N], id[N];
int edToNo[N];
int n ,m;
int deg[N];
int ndcnt=0, ndToId[N], idToNd[N];
int comp[N];
int src;
int st[N], en[N];
int c=0;
int u,v,ty;
int dpth[N];
int edgcnt=0;



int tree[4*N];

void addEdge(int u, int v, int i){
    nxt[edgcnt]=head[u];
    head[u]=edgcnt;
    to[edgcnt]=v;
    id[edgcnt]=i;
    edgcnt++;
}

void addBiEdge(int u,int v, int i){
    addEdge(u,v,i);
    addEdge(v,u,i);
}

void dfs(int u, int p=-1, int d=0){
    ndToId[u]=ndcnt;
    idToNd[ndcnt]=u;
    ndcnt++;
    dpth[u]=d;
    if(u!=src){
        comp[u]=c;
    }
    neig(u,v,e){
        if(v==p)
            continue;
        if(u==src){
            st[c]=ndcnt;
        }
        edToNo[id[e]]=v;
        dfs(v,u,d+1);
        if(u==src){
            en[c]=ndcnt-1;
            c++;
        }
    }
}

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        tree[id]=1;
        return ;
    }

    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    tree[id]=tree[l]+ tree[r];
}

void upd(int p, int id=0, int ns=0, int ne=n-1){
    if(ns>p || ne<p)
        return ;
    if(ns==ne){
        tree[id]=1-tree[id];
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(p,l, ns, md);
    upd(p,r, md+1, ne);
    tree[id]=tree[l]+tree[r];
}

int get(int qs, int qe, int id=0,int ns=0, int ne=n-1){
    if(qs>ne || qe<ns)
        return 0;
    if(qs<=ns && qe>=ne)
        return tree[id];
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return get(qs, qe,l, ns, md)  + get(qs, qe,r, md+1, ne);
}


int main(){
    freopen("input.txt", "r", stdin);
    memset(head, -1, sizeof(head));
    scanf("%d",&n);
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        --u,--v;
        addBiEdge(u,v,i);
        deg[u]++;
        deg[v]++;
    }
    src=0;
    for(int i=0;i<n;i++){
        if(deg[i]>2)
            src=i;
    }
    dfs(src);
    build();
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%d",&ty);
        switch(ty){
        case 1 :
            scanf("%d",&u);
            upd(ndToId[edToNo[--u]]);
            break;
        case 2 :
            scanf("%d",&u);
            upd(ndToId[edToNo[--u]]);
            break;
        case 3 :{
            scanf("%d%d",&u,&v);
            --u;--v;
            if(u==v){
                puts("0");
                break;
            }
            if(u==src || v==src){
                if(v==src)
                    swap(u,v);
                int dist = ndToId[v]-st[comp[v]]+1;
                int nb = get(st[comp[v]],ndToId[v]);
                if(dist==nb)
                    printf("%d\n", dist);
                else
                    puts("-1");
                break;
            }
            if(comp[u]==comp[v]){
                if(ndToId[u]<ndToId[v])
                    swap(u,v);
                int dist = ndToId[u]-ndToId[v];
                int nb = get(ndToId[v]+1, ndToId[u]);
                if(dist==get(ndToId[v]+1, ndToId[u]))
                    printf("%d\n", dist);
                else
                    puts("-1");
            }else{
                int dist = ndToId[v]-st[comp[v]]+1 + ndToId[u]-st[comp[u]]+1;
                int nb = get(st[comp[v]],ndToId[v])+get(st[comp[u]], ndToId[u]);
                if(dist==nb)
                    printf("%d\n", dist);
                else
                    puts("-1");
            }
            break;
            }
        }
    }
    return 0;
}
