//https://www.spoj.com/problems/POTHOLE/

#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 50000 +5 , E = 150000 +5;
const int MOD = 1e9 + 7 ;

#define neig(u,v,e) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])

int edgcnt, n, head[N], to[E], cap[E], nxt[E];

void addEdge(int a, int b, int c){
    nxt[edgcnt]=head[a];
    to[edgcnt]=b;
    cap[edgcnt]=c;
    head[a]=edgcnt++;
}

void addAug(int a , int b , int c, int d=0){
    addEdge(a,b,c);
    addEdge(b,a,d);
}

void init(){
    edgcnt=0;
    memset(head,-1, n*sizeof(head[0]));
}
int vis[N],dist[N],work[N],vid=0,src,snk;
int qu[N],qsz;

bool bfs(){
    qsz=0;
    vid++;
    dist[src]=0;
    qu[qsz++]=src;
    vis[src]=vid;
    for(int i=0;i<qsz;i++){
        int u = qu[i];
        neig(u,v,e){
            if(vis[v]==vid || !cap[e])
                continue;
            vis[v]=vid;
            dist[v]=dist[u]+1;
            qu[qsz++]=v;
        }
    }
    return vis[snk]==vid;
}

int dfs(int u, int fl=INT_MAX){
    if(u==snk)
        return fl;

    for(int &e=work[u];(~e);e=nxt[e]){
        int v = to[e];
        if((dist[v]!=dist[u]+1) || (!cap[e]))
            continue;
        int f = dfs(v,min(fl,cap[e]));
        if(f){
            cap[e]-=f;
            cap[e^1]+=f;
            return f;
        }
    }
    return 0;
}


int dinic(){
    int res=0, flow;
    while(bfs()){
        memcpy(work , head, n*sizeof(head[0]));
        while(flow=dfs(src)){
            res+=flow;
        }
    }
    return res;
}
int t;
int nn,x,y;
int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&nn);
        n=nn;
        src=0;
        snk=nn-1;
        init();
        for(int i=0;i<nn-1;i++){
            scanf("%d",&x);
            while(x--){
                scanf("%d",&y);
                --y;
                if(i==src || i==snk || y==src || y==snk)
                    addAug(i,y,1);
                else{
                    addAug(i,y,n+1);
                }
            }
        }
        printf("%d\n",dinic());
    }
    return 0;
}
