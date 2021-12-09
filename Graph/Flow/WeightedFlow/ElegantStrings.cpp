//https://vjudge.net/problem/UVA-11381
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 300 , E = 2e6 + 5;
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
int cs[26][26];

char s[1005];

int main(){
    freopen("input.txt", "r", stdin);
    int t;
    scanf("%d",&t);
    while(t--){
        memset(cs, -1, sizeof(cs));
        scanf("%s",s);
        int k = strlen(s);
        for(int i=0;i<k-1;i++){
            int x = s[i]-'a';
            int y = s[i+1]-'a';
            if(cs[x][y]==-1)
                cs[x][y]=(i+1)*(i+1);
        }
        scanf("%s",s);
        k=strlen(s);
        n = 2*k+2;
        src=  n-1;
        snk = n-2;
        init();
        for(int i=0;i<k;i++){
            addAug(src, i, 0, 1);
            addAug(i+k, snk, 0,1);
        }
        for(int i=0;i<k;i++){
            for(int j=i+1;j<k;j++){
                int x = s[i]-'a';
                int y = s[j]-'a';
                if(cs[x][y]!=-1){
                    addAug(i,k+j,cs[x][y],1);
                }
            }
        }
        auto rs = mcmf();
        printf("%d %d\n", k-rs.second, rs.first);
    }
    return 0;
}
