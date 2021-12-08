//https://www.spoj.com/problems/DISJPATH/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 30020 , E = 2e6 + 5;
const int MOD = 1e9 + 7 ;
#define neig(u,e,v) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int head[N], nxt[E], to[E],edgcnt=0,cap[E],n, work[N];
int vis[N], vid=0 , dist[N], par[N],src, snk;

void addEdge(int a , int b , int c){
    nxt[edgcnt]=head[a];
    to[edgcnt]=b;
    cap[edgcnt]=c;
    head[a]=edgcnt++;
}

void addAug(int a, int b , int fcp, int rcp=0){
    addEdge(a,b,fcp);
    addEdge(b,a,rcp);
}

void init(){
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
}
bool bfs(){
    queue<int> q;
    dist[src]=0;
    vis[src]=++vid;
    q.push(src);
    while(q.size()){
        int u = q.front();
        q.pop();
        neig(u,e,v){
            if(!cap[e] || vis[v]==vid)
                continue;
            dist[v]=dist[u]+1;
            vis[v]=vid;
            q.push(v);
        }
    }
    return vis[snk]==vid;
}

int dfs(int u=src, int fl=INT_MAX){
    if(u==snk)
        return fl;

    for(int &e=work[u],v;(~e)&&(v=to[e],1);e=nxt[e]){
        if(!cap[e] || dist[v]!=dist[u]+1)
            continue;
        int f = dfs(v, min(cap[e], fl));
        if(f){
            cap[e]-=f;
            cap[e^1]+=f;
            return f;
        }
    }
    return 0;
}

int dinic(){
    int flow=0, f=0;
    while(bfs()){
        memcpy(work , head, n*sizeof(head[0]));
        while(f=dfs()){
            flow+=f;
        }
    }
    return flow;
}
int nodes, k,m;
string s;
vector<int> tmp;

void getinput(){
    tmp.clear();
    getline(cin , s);
    int x=0;
    for(auto c:s){
        if(c==' '){
            tmp.pb(x);
            x=0;
        }
        else{
            x=x*10 + (c-'0');
        }
    }
    tmp.pb(x);
}

void solve(int u=src){

    if(u<nodes){
        tmp.pb(u);
    }
    if(u==1)
        return ;
    vis[u]=vid;
    neig(u,e,v){
        if(e%2==0 && (!cap[e]) && (v==1 || vis[v]!=vid)){
            solve(v);
            return;
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    int ii=0;
    while(1){

        getinput();
        k = tmp[0],nodes = tmp[1];
        if(k==0 && nodes==0)
            break;
        printf("Case %d:\n",++ii);
        n = 2*nodes;
        init();
        src = 0;
        snk = 1+nodes;
        for(int i=0;i<nodes;i++){
            getinput();
            for(auto v:tmp){
                addAug(i+nodes,v-1,1);
            }
        }
        addAug(0, nodes, INT_MAX);
        addAug(1, 1+nodes, INT_MAX);
        for(int i=2;i<nodes;i++){
            addAug(i,i+nodes,1);
        }
        int f  = dinic();
        if(f<k){
            puts("Impossible");
        }else{
            vid++;
            for(int i=0;i<k;i++){
                tmp.clear();
                solve(nodes);
                printf("1 ");
                for(auto v:tmp){
                    printf("%d ",v+1);
                }
                puts("");
            }
        }
        puts("");
    }
    return 0;
}

