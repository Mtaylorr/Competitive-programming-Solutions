//https://www.spoj.com/problems/AMR12A/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 105 , E = 2e6 + 5,M=2*N;
const int MOD = 1e9 + 7 ;
#define neig(u,e,v) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int head[N], nxt[E], to[E],edgcnt=0,n,m;
int vis[N], vid=0 , dist[N], par[N];

int r2l[M] ,l2r[N];

void addEdge(int a , int b){
    nxt[edgcnt]=head[a];
    to[edgcnt]=b;
    head[a]=edgcnt++;
}

void init(){
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
}

int bound;

int nodes, holes, k, c;
int adj[105][105];

int dfs(int u){
    if(vis[u]==vid)
        return  0;
    vis[u]=vid;
    neig(u,e,v){
        if(r2l[v]==-1  || dfs(r2l[v])){
            r2l[v]=u;
            l2r[u]=v;
            return 1;
        }
    }
    return 0;
}


int maxmatching(){
    memset(r2l,-1, m*sizeof(r2l[0]));
    bool bl=true;
    int rs=0;
    for(int i=0;i<n;i++){
        vid++;
        rs+=dfs(i);
    }
    return rs;
}

bool ok(){
    n=nodes;
    m = holes*2;
    init();
    for(int i=0;i<nodes;i++){
        for(int j=0;j<holes;j++){
            if(adj[i][j]<=bound)
                addEdge(i, j);
            if(adj[i][j]+c<=bound)
                addEdge(i, holes+j);
        }
    }
    int f = maxmatching();
    return f>=k;
}
int solve(){
    int l=0;
    int r=INT_MAX;
    while(l<r-1){
        bound=l+(r-l)/2;
        if(ok()){
            r=bound;
        }else{
            l=bound;
        }
    }
    bound=l;
    if(ok()){
        return l;
    }else{
        return r;
    }
}


int main(){
    freopen("input.txt", "r", stdin);
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d%d",&nodes, &holes, &k,&c);
        for(int i=0;i<nodes;i++){
            for(int j=0;j<holes;j++){
                scanf("%d",&adj[i][j]);
            }
        }
        printf("%d\n",solve());
    }
    return 0;
}

