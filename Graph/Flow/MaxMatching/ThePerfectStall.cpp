//https://vjudge.net/problem/OpenJ_Bailian-1274

#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 505, E = 2*30000 +5, M=N;
const int MOD = 1e9 + 7 ;

#define neig(u,v,e) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int head[N], nxt[E], to[E], edgcnt,n;
int vis[N], vid=0;
int l2r[N], r2l[M];

void addEdge(int a, int b){
    nxt[edgcnt]=head[a];
    head[a]=edgcnt;
    to[edgcnt]=b;
    edgcnt++;
}

void init(){
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
}

int dfs(int lid){
    if(vis[lid]==vid)
        return 0;
    vis[lid]=vid;
    neig(lid,rid,e){
        if(r2l[rid]==-1 || dfs(r2l[rid])){
            r2l[rid]=lid;
            l2r[lid]=rid;
            return 1;
        }
    }
    return 0;
}
int m,x,y;
int maxMatching(){
    int res=0;
    memset(r2l,-1, m*sizeof(r2l[0]));
    for(int i=0;i<n;i++){
        vid++;
        res+=dfs(i);
    }
    return res;
}

int main(){
    freopen("input.txt", "r", stdin);

    while(~scanf("%d%d",&n,&m)){
        init();
        for(int i=0;i<n;i++){
            scanf("%d",&x);
            while(x--){
                scanf("%d",&y);
                y--;
                addEdge(i,y);
            }
        }
        printf("%d\n", maxMatching());
    }
    return 0;
}
