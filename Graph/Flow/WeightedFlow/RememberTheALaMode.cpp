//https://vjudge.net/problem/UVALive-3562

#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 205, E = 3e4 +5;
const int MOD = 1e9 + 7 ;

#define neig(u,v,e) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int head[N], nxt[E], to[E], cap[E], cst[E], edgcnt,n,m,src,snk;
int captmp[E];
int dist[N], par[N];
int inq[N], vid=0, fl[N];
void addEdge(int a, int b , int cs, int cp){
    nxt[edgcnt]=head[a];
    head[a]=edgcnt;
    to[edgcnt]=b;
    cap[edgcnt]=cp;
    cst[edgcnt]=cs;
    edgcnt++;
}

void addAug(int a , int b ,int cs, int c, int d=0){
    addEdge(a,b,cs,c);
    addEdge(b,a,-cs,d);
}

void init(){
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
}

bool bellmanford(){
    queue<int> q;
    q.push(src);
    memset(dist, 63, n*sizeof(dist[0]));
    dist[src]=0;
    inq[src]=++vid;
    int ncnt = n;
    fl[snk]=0, fl[src]=INT_MAX;
    while(--ncnt && q.size()){
        int s = q.size();
        while(s--){
            int u = q.front();
            q.pop();
            inq[u]=0;
            neig(u,v,e){
                if(!cap[e])
                    continue;
                int d = dist[u] + cst[e];

                if(d<dist[v]){
                    fl[v]=min(fl[u], cap[e]);
                    dist[v]=d;
                    par[v]=e;
                    if(inq[v]!=vid){
                        inq[v]=vid;
                        q.push(v);
                    }
                }
            }
        }
    }
    return fl[snk]>0;
}


pair<int,int> mcmf(){
    int c=0, f=0;
    while(bellmanford()){
        c+=dist[snk]*fl[snk];
        f+=fl[snk];
        for(int u=snk;u!=src; u=to[par[u]^1]){
            cap[par[u]]-=fl[snk];
            cap[par[u]^1]+=fl[snk];
        }

    }
    return {c, f};
}


int main(){
    freopen("input.txt", "r", stdin);
    int ice, pie,cp;
    double g;
    int ii=0;
    while(1){
        scanf("%d%d",&pie ,&ice);
        if(pie==0 && ice==0)
            break;
        n = pie+ice+2;
        src=n-1;
        snk=n-2;
        init();
        for(int i=0;i<pie;i++){
            scanf("%d",&cp);
            addAug(src, i, 0, cp);
        }
        for(int i=0;i<ice;i++){
            scanf("%d",&cp);
            addAug(i+pie, snk,0,cp);
        }
        for(int i=0;i<pie;i++){
            for(int j=0;j<ice;j++){
                scanf("%lf",&g);
                if(g==-1)
                    continue;
                addAug(i, pie+j,g*100 + 0.5, INT_MAX);
            }
        }
        memcpy(captmp, cap, edgcnt*sizeof(cap[0]));
        auto mn = mcmf();
        memcpy(cap, captmp, edgcnt*sizeof(cap[0]));
        for(int i=0;i<edgcnt;i++)
            cst[i]*=-1;
        auto mx = mcmf();
        printf("Problem %d: %.2lf to %.2lf\n", ++ii, mn.fi/100.0, -mx.fi/100.0);
    }
    return 0;
}
