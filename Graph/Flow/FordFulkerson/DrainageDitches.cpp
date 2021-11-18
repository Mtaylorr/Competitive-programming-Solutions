//https://vjudge.net/problem/HDU-1532


//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include<climits>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 205, E = 405;
const int MOD = 1e9 + 7 ;

#define neig(u,v,e) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int head[N], nxt[E], to[E], cap[E], edgcnt,n,src,snk;
int vis[N], vid=0;

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
    if(vis[u]==vid || fl==0)
        return 0;
    if(u==snk)
        return fl;
    vis[u]=vid;
    neig(u,v,e){
        int f = dfs(v, min(fl, cap[e]));
        if(f){
            cap[e]-=f;
            cap[e^1]+=f;
            return f;
        }
    }
    return 0;
}


int maxFlow(){
    int res=0,flow;
    do{
        vid++;
        flow=dfs();
        res+=flow;
    }while(flow);
    return res;
}

int main(){
    freopen("input.txt", "r", stdin);
    int m;
    int u,v,c;
    while(~scanf("%d%d",&m,&n)){
        src=0;
        snk=n-1;
        init();
        for(int i=0;i<m;i++){
            scanf("%d%d%d",&u,&v,&c);
            --u;--v;
            addAug(u,v,c);
        }
        printf("%d\n", maxFlow());
    }
    return 0;
}
