//https://codeforces.com/problemset/problem/468/B

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 4e5+5;
const int MOD = 1e9 + 7 ;

#define neig(a,u,v,e) for(int e=a.head[u],v;(~e)&&(v=a.to[e],1);e=a.nxt[e])


struct Adj{
    int head[N], to[E], nxt[E], edgcnt,n;

    void addEdge(int a, int b){
        nxt[edgcnt]=head[a];
        head[a]=edgcnt;
        to[edgcnt]=b;
        edgcnt++;
    }

    void init(){
        edgcnt=0;
        memset(head, -1, n*sizeof(head[0]));
    }
}adj;

int vis[N], vid=0;
int nodes[N], comps=0, comp[N], low[N], dfst[N], curt,ndcnt, val[N];

void dfs(int u){
    vis[u]=vid;
    nodes[ndcnt++]=u;
    dfst[u]=low[u]=curt++;
    comp[u]=-1;
    neig(adj,u,v,e){
        if(vis[v]!=vid){
            dfs(v);
            low[u]=min( low[u], low[v]);
        }else{
            if(comp[v]==-1){
                low[u]=min( low[u], low[v]);
            }
        }
    }
    if(low[u]==dfst[u]){
        do{
            comp[nodes[--ndcnt]]=comps;
        }while(nodes[ndcnt]!=u);
        comps++;
    }
}
void tarjan(){
    ndcnt=0;
    vid++;
    curt=0;
    comps=0;
    for(int i=0;i<adj.n;i++){
        if(vis[i]!=vid)
            dfs(i);
    }
}

void getsol(int u){
    if(vis[u]==vid)
        return ;
    vis[u]=vid;
    neig(adj,u,v,e){
        getsol(v);
    }
    if(val[comp[u]]==-1){
        val[comp[u]]=1;
        val[comp[u^1]]=0;
    }
}

bool twoSat(){
    tarjan();
    vid++;
    memset(val, -1, adj.n*sizeof(val[0]));
    for(int i=0;i<adj.n;i+=2){
        getsol(i);
        getsol(i+1);
        if(comp[i]==comp[i+1])
            return 0;
    }
    return 1;
}

int var(int x){
    return x<<1;
}

int notvar(int x){
    return x^1;
}

void addor(int x, int y){
    adj.addEdge(notvar(x),y);
    adj.addEdge(notvar(y),x);
}

map<int,int> maa;
int p[N];
int n,m,a,b;
int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d%d",&n,&a,&b);
    adj.n=2*n;
    adj.init();
    for(int i=0;i<n;i++){
        scanf("%d",&p[i]);
        maa[p[i]]=i+1;
    }
    for(int i=0;i<n;i++){
        if(!maa[a-p[i]]){
            adj.addEdge(notvar(var(i)), var(i));
        }
        if(maa[a-p[i]] && a-p[i]>p[i]){
            int x = maa[a-p[i]]-1;
            int y = i;
            adj.addEdge(notvar(var(x)), notvar(var(y)));
            adj.addEdge(notvar(var(y)), notvar(var(x)));
            adj.addEdge(var(x), var(y));
            adj.addEdge(var(y), var(x));
        }
        if(!maa[b-p[i]]){
            adj.addEdge(var(i), notvar(var(i)));
        }
        if(maa[b-p[i]] && b-p[i]>p[i]){
            int x = maa[b-p[i]]-1;
            int y = i;
            adj.addEdge(notvar(var(x)), notvar(var(y)));
            adj.addEdge(notvar(var(y)), notvar(var(x)));
            adj.addEdge(var(x), var(y));
            adj.addEdge(var(y), var(x));
        }
    }
    bool rs = twoSat();
    if(!rs){
        puts("NO");
        return 0;
    }
    cout << "YES\n";
    for(int i=0;i<adj.n;i+=2){
         cout << val[comp[i]] << " ";
    }
    return 0;
}
