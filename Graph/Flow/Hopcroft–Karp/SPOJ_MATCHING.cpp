//https://www.spoj.com/problems/MATCHING/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 50000 +5 , E = 150000 +5, M=N;
const int MOD = 1e9 + 7 ;

#define neig(u,v,e) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int head[N], nxt[E], to[E], edgcnt,n;
int vis[N], vid=0, dist[N];
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

void bfs(){
    queue<int> q;
    for(int i=0;i<n;i++){
        if(l2r[i]==-1){
            q.push(i);
            dist[i]=0;
        }else{
            dist[i]=-1;
        }
    }
    while(q.size()){
        int lid = q.front();
        q.pop();
        neig(lid, rid, e){
            int newlid = r2l[rid];
            if(newlid!=-1 && dist[newlid]==-1){
                dist[newlid]=dist[lid]+1;
                q.push(newlid);
            }
        }
    }
}

int dfs(int lid){
    neig(lid,rid,e){
        if(r2l[rid]!=-1 && dist[r2l[rid]]!=dist[lid]+1)
            continue;
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
    memset(l2r,-1, n*sizeof(r2l[0]));
    bool bl=true;
    while(bl){
        bl=false;
        bfs();
        for(int i=0;i<n;i++){
            if(dist[i]==0 && dfs(i)){
                res++;
                bl=true;
            }
        }
    }
    return res;
}

int main(){
    freopen("input.txt", "r", stdin);
    int e;
    scanf("%d%d%d",&n,&m,&e);
    init();
    for(int i=0;i<e;i++){
        scanf("%d%d",&x,&y);
        addEdge(--x,--y);
    }
    printf("%d\n", maxMatching());

    return 0;
}
