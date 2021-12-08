//https://www.spoj.com/problems/EN/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 30020 , E = 2e6 + 5;
const int MOD = 1e9 + 7 ;
#define neig(u,e,v) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int head[N], nxt[E], to[E],edgcnt=0,n;
int vis[N], vid=0 , dist[N], par[N];
int initialdist[N];
int t;
int c1,c2;
int a,b,c;
int m;
bool tag[N];

int mx, mxv;
void addEdge(int a, int b){
    nxt[edgcnt]=head[a];
    to[edgcnt]=b;
    head[a]=edgcnt++;
}

void init(){
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
}

void calcdist(){
    queue<int> q;
    q.push(0);
    initialdist[0]=0;
    vis[0]=++vid;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        neig(u,e,v){
            if(vis[v]==vid)
                continue;
            par[v]=u;
            initialdist[v]=initialdist[u]+1;
            q.push(v);
            vis[v]=vid;
        }
    }
}



void solve(int u=0){
    if(vis[u]==vid)
        return ;
    vis[u]=vid;
    if(tag[u]){
        if(mx<initialdist[u]){
            mx=initialdist[u];
            mxv=u;
        }
        return ;
    }
    neig(u,e,v){
        solve(v);
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=0;i<m;i++){
            scanf("%d%d",&a,&b);
            a--;b--;
            addEdge(a,b);
        }
        calcdist();
        for(int i=0;i<n;i++)
            tag[i]=0;
        int u = n-1;
        while(u!=0){
            tag[u]=1;
            u=par[u];
        }
        mx=-1;
        mxv=-1;
        vid++;
        solve();
        printf("%d\n", mxv+1);
    }
    return 0;
}
