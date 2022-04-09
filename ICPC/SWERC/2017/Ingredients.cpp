#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e6 + 5, E = 1e6 +5;
const int MOD = 1e9 + 7 ;

#define neig(u,e,v) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])

int B;
int n;
string s[N],t[N];
int c[N],p[N];
string tmp;
int head[N], nxt[E],cs[E], pr[E], edgcnt, to[E];
set<string> ss;
map<string,int> code;
pair<int,int> dist[N];
bool vis[N];
int cn=0;

void addEdge(int u, int v, int c , int p){
    nxt[edgcnt]=head[u];
    to[edgcnt]=v;
    cs[edgcnt]=c;
    pr[edgcnt]=p;
    head[u]=edgcnt++;
}

void dfs(int u){
    if(vis[u])
        return;
    vis[u]=1;
    if(head[u]==-1){
        dist[u]={0,0};
        return ;
    }
    pair<int,int> p = {1e9,-1e9};
    neig(u,e,v){
        dfs(v);
        p=min(p,{dist[v].fi+cs[e], dist[v].se-pr[e]});
    }
    dist[u]=p;
}
ll dp[2][10005];

int main()
{
    ios::sync_with_stdio(0);
    memset(head, -1, sizeof(head));
    //freopen("input.txt", "r",stdin);
    cin >> B;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> s[i] >> t[i] >>tmp >>  c[i] >> p[i];
        ss.insert(s[i]);
        ss.insert(t[i]);
    }
    for(auto u:ss){
        code[u]=cn++;

    }
    for(int i=0;i<n;i++){
        //cout << code[s[i]] << " " << code[t[i]] << endl;
        addEdge(code[s[i]],code[t[i]],c[i],p[i]);
    }
    for(int i=0;i<cn;i++){
        if(vis[i])
            continue;
        dfs(i);
      }
    for(int i=1;i<=cn;i++){
        int id = i&1;
        for(int j=0;j<=B;j++){
            dp[id][j]=dp[id^1][j];
            if(j>=dist[i-1].fi){
                dp[id][j]=max(dp[id][j], -dist[i-1].se + dp[id^1][j-dist[i-1].fi]);
            }
        }
    }
    ll ansp = dp[cn&1][B];
    cout << ansp << endl;
    for(int i=0;i<=B;i++){
        if(dp[cn&1][i]==ansp){
            cout << i << endl;
            break;
        }
    }

    return 0;

}
