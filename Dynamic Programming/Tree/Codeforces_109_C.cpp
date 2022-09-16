//https://codeforces.com/problemset/problem/109/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e5 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 998244353 ;

#define neig(u,e,v) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])

int dp[N];
int sz[N];
int n,u,v,w;
int to[E], head[N], we[E], nxt[E], edgcnt;
ll ans=0;

bool islucky(int x){
    while(x){
        if(x%10 !=4 && x%10!=7)
            return 0;
        x/=10;
    }
    return 1;
}

void addEdge(int u, int v, int w){
    nxt[edgcnt]=head[u];
    to[edgcnt]=v;
    we[edgcnt]=w;
    head[u]=edgcnt++;
}
void addBiEdge(int u, int v, int w){
    addEdge(u,v,w);
    addEdge(v,u,w);
}

void calcdp(int u, int p=-1){
    sz[u]=1;
    neig(u,e,v){
        if(v==p)
            continue;
        calcdp(v,u);
        sz[u]+=sz[v];
        if(islucky(we[e])){
            dp[u]+=sz[v];
        }else{
            dp[u]+=dp[v];
        }
    }
}

void calcans(int u, int topset, int p=-1){
    int total = topset + dp[u];
    ans+=(total*1ll*(total)) - total;
    int sumdp=0;
    neig(u,e,v){
        if(v==p){
            continue;
        }
        int curv = dp[v];
        if(islucky(we[e])){
            curv=sz[v];
        }
        int cur = topset + dp[u]-curv;
        if(islucky(we[e])){
            calcans(v,n-sz[v], u);
        }else{
            calcans(v, cur, u);
        }
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    memset(head, -1, sizeof(head));
    for(int i=0;i<n-1;i++){
        cin >> u >> v >> w;
        u--;v--;
        addBiEdge(u,v,w);
    }
    calcdp(0);
    calcans(0,0);
    cout << ans;

    return 0;


}
