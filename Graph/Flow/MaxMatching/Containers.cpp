//https://vjudge.net/problem/UVA-1062
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1005 , E = 2e6 + 5, M=N;
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
char s[N];
int main(){
    freopen("input.txt", "r", stdin);
    int ii=1;
    while(1){
        scanf("%s",s);
        if(s[0]=='e')
            break;
        n=m=strlen(s);
        init();
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(s[j]<=s[i])
                    addEdge(i,j);
            }
        }
        printf("Case %d: %d\n",ii++,n-maxMatching());
    }
    return 0;
}
