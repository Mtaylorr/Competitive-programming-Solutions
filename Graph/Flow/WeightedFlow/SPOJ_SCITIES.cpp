//https://www.spoj.com/problems/SCITIES/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1005 , E = 2e6 + 5, M=N;
const int MOD = 1e9 + 7 ;
#define neig(u,e,v) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int head[N], nxt[E], to[E], cap[E], cst[E], edgcnt=0,n;
int src, snk , inq[N], vid=0, fl[N], dist[N],par[N];
void addEdge(int a, int b, int cs, int cp){
    nxt[edgcnt]=head[a];
    to[edgcnt]=b;
    cst[edgcnt]=cs;
    cap[edgcnt]=cp;
    head[a]=edgcnt++;
}

void addAug(int a, int b, int cs, int fcp, int rcp=0){
    addEdge(a,b,cs,fcp);
    addEdge(b,a,-cs, rcp);
}
void init(){
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
}

bool bellmanford(){
    queue<int> q;
    memset(dist,63, n*sizeof(dist[0]));
    dist[src]=0;
    fl[src]=INT_MAX;
    fl[snk]=0;
    q.push(src);
    inq[src]=++vid;
    int ndcnt=n;
    while(--ndcnt&& q.size()){
        int s = q.size();
        while(s--){
            int u = q.front();
            q.pop();
            inq[u]=0;
            neig(u,e,v){
                if(!cap[e])
                    continue;
                int d = dist[u]+cst[e];
                if(dist[v]>d){
                    par[v]=e;
                    dist[v]=d;
                    fl[v]=min(fl[u], cap[e]);
                    if(inq[v]!=vid){
                        q.push(v);
                        inq[v]=vid;
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
        f+=fl[snk];
        c+=fl[snk]*dist[snk];
        for(int i=snk;i!=src;i=to[par[i]^1]){
            cap[par[i]]-=fl[snk];
            cap[par[i]^1]+=fl[snk];
        }
    }
    return {c,f};
}

int t;
int c1,c2;
int a,b,c;
int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&c1,&c2);
        n = c1+c2+2;
        src = n-2;
        snk = n-1;
        init();
        for(int i=0;i<c1;i++){
            addAug(src, i, 0, 1);
        }
        for(int i=0;i<c2;i++){
            addAug(i+c1, snk, 0, 1);
        }
        while(1){
            scanf("%d%d%d",&a,&b,&c);
            if(a==0)
                break;
            --a;--b;
            addAug(a, b+c1,-c,1);
        }
        auto res = mcmf();
        printf("%d\n",-res.first);
    }
    return 0;
}

