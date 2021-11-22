//https://www.spoj.com/problems/MTOTALF/

#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 50000 +5 , E = 150000 +5;
const int MOD = 1e9 + 7 ;

#define neig(u,v,e) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int n,edcnt,head[N], to[E], cap[E], nxt[E];
int work[N];
void addEdge(int a, int b ,int c){
    nxt[edcnt]=head[a];
    to[edcnt]=b;
    cap[edcnt]=c;
    head[a]=edcnt++;
}

void addAug(int a, int b , int c, int d=0){
    addEdge(a,b,c);
    addEdge(b,a,d);
}

void init(){
    edcnt=0;
    memset(head, -1,n*sizeof(head[0]));
}
int vis[N], vid=0, dist[N], qu[N], qsz;
int src, snk;
bool bfs(){
    vid++;
    qsz=0;
    vis[src]=vid;
    qu[qsz++]=src;
    dist[src]=0;
    for(int i=0;i<qsz;i++){
        int u = qu[i];
        neig(u,v,e){
            if((!cap[e])|| vis[v]==vid)
                continue;
            vis[v]=vid;
            dist[v]=dist[u]+1;
            qu[qsz++]=v;
        }
    }
    return vis[snk]==vid;
}

int dfs(int u=src, int fl=INT_MAX){
    if(u==snk)
        return fl;
    for(int &e=work[u];(~e);e=nxt[e]){
        int v=to[e];
        if((!cap[e])|| dist[v]!=dist[u]+1)
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

int dinic(){
    int res=0,flow;
    while(bfs()){
        memcpy(work , head, n*sizeof(head[0]));
        while(flow=dfs())
            res+=flow;
    }
    return res;
}

int get( char c){
    if(c>'Z')
        return 26+(c-'a');
    return c-'A';
}

int m;
int f,x,y;
char c1,c2;
int main(){
    freopen("input.txt", "r", stdin);
    n = 26*2;
    src=0;
    snk=25;
    init();
    scanf("%d",&m);
    while(m--){
        scanf(" %c %c %d",&c1,&c2,&f);
        x=get(c1);
        y=get(c2);
        addAug(x,y,f);
    }
    printf("%d\n",dinic());
    return 0;
}
