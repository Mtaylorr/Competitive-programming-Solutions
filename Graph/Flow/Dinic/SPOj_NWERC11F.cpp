//https://vjudge.net/problem/SPOJ-NWERC11F

#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5005, E = 2*90000 +5;
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
    int t,r,c,d,f,b;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d %d %d %d",&c,&r,&d,&f,&b);
        n = r*c+2;
        src = n-1;
        snk = n-2;
        init();
        long long res=0;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                char ch;
                scanf(" %c",&ch);
                if((i==0 || i==r-1 || j==0 || j==c-1)){
                    if(ch=='.')
                        res+=f;
                    addAug(src, i*c+j,INT_MAX);
                }else{
                    if(ch=='.')
                        addAug(i*c+j,snk,f);
                    else
                        addAug(src, i*c+j,d);
                }
                int di=-1,dj=0;
                for(int k=0;k<4;k++){
                    int ni = i+di;
                    int nj = j+dj;
                    if(ni>=0 && ni<r&& nj>=0 &&nj<c){
                        addAug(i*c+j,ni*c+nj,b);
                    }
                    swap(di,dj);
                    if(k==1)
                        di*=-1;
                }
            }
        }
        printf("%lld\n",dinic()+res);
    }
    return 0;
}
