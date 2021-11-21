//https://vjudge.net/problem/OpenJ_Bailian-1274

#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5005, E = 2*30000 +5;
const int MOD = 1e9 + 7 ;

#define neig(u,v,e) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int head[N], nxt[E], to[E], cap[E], edgcnt,n,src,snk;
int vis[N], vid=0, work[N],dist[N], qu[N];

void addEdge(int a, int b , int c){
    nxt[edgcnt]=head[a];
    head[a]=edgcnt;
    to[edgcnt]=b;
    cap[edgcnt]=c;
    edgcnt++;
}

void addAug(int a , int b , int c, int d=0){
    addEdge(a,b,c);
    addEdge(b,a,d);
}

void init(){
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
}


int dfs(int u=src, int fl = INT_MAX){
    if(u==snk)
        return fl;
    vis[u]=vid;
    for(int &e=work[u];~e;e=nxt[e]){
        int v = to[e];
        if(dist[u]+1!=dist[v] || !cap[e])
            continue;
        int f = dfs(v, min(fl, cap[e]));
        if(f){
            cap[e]-=f;
            cap[e^1]+=f;
            return f;
        }
    }
    return 0;
}

bool bfs(){
    vid++;
    vis[src]=vid;
    qu[0]=src;
    dist[src]=0;
    int qsz = 1;

    for(int i=0;i<qsz;i++){
        int u = qu[i];
        neig(u,v,e){
            if(vis[v]==vid  || !cap[e])
                continue;
            vis[v]=vid;
            dist[v]=dist[u]+1;
            qu[qsz++]=v;
        }
    }
    return vis[snk]==vid;
}

ll dinic(){
    ll res=0,flow;
    while(bfs()){

        memcpy(work, head, n*sizeof(head[0]));
        while(flow=dfs())
            res+=flow;
    }
    return res;
}

int main(){
    freopen("input.txt", "r", stdin);
    int m,n;
    int x,y;
    while(~scanf("%d%d",&n,&m)){
        ::n = n+m+2;
        src = n+m;
        snk = n+m+1;
        init();
        for(int i=0;i<n;i++){
            addAug(src, i,1);
        }
        for(int i=0;i<m;i++){
            addAug(n+i,snk,1);
        }
        for(int i=0;i<n;i++){
            scanf("%d",&x);
            while(x--){
                scanf("%d",&y);
                y--;
                addAug(i,n+y,1);
            }
        }
        printf("%d\n", dinic());
    }
    return 0;
}
