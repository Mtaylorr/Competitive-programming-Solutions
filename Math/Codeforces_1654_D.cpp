//https://codeforces.com/problemset/problem/1654/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 5e5 + 5, M=1000 +5,E = 1e6 +5 ;
const int MOD = 998244353   ;
const double eps = 1e-7;

ll mul(ll u , ll v, ll mod=MOD){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
    return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
    return ((u%mod)-(v%mod)+mod)%mod;
}

ll powe(ll u, ll v, ll mod=MOD){
    ll ans=1;
    ll acc=u;
    while(v){
        if(v%2){
            ans=mul(ans,acc,mod);
        }
        acc = mul(acc,acc,mod);
        v/=2;
    }
    return ans;
}
ll  inv(ll u,ll mod=MOD){
    return powe(u,mod-2,mod);
}


int t,n;
int a[N],b[N], x[N],y[N];
ll freq[N];
ll mn[N];
vector<pair<int,pair<int,int> > >adj[N];
ll ans=0;

void add(int u){
    for(int i=2;i*i<=u;i++){
        while(u%i==0){
            freq[i]++;
            u/=i;
        }
    }
    if(u>1){
        freq[u]++;
    }
}

void rem(int u){
    for(int i=2;i*i<=u;i++){
        while(u%i==0){
            freq[i]--;
            u/=i;
        }
        mn[i]=min(mn[i],freq[i]);
    }
    if(u>1){
        freq[u]--;
        mn[u]=min(mn[u],freq[u]);
    }
}

void dfs(int u, int lst=1, int p=-1){
    ans=add(ans, lst);
    for(auto v:adj[u]){
        if(v.fi==p)
            continue;
        ll z = mul(v.se.se, inv(v.se.fi));
        add(v.se.se);
        rem(v.se.fi);
        dfs(v.fi, mul(lst, z),u);
        add(v.se.fi);
        rem(v.se.se);
    }
}

void init(){
    for(int i=0;i<=n;i++){
        adj[i].clear();
        freq[i]=0;
        mn[i]=0;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n;
        init();
        for(int i=0;i<n-1;i++){
            cin >> a[i] >> b[i] >> x[i] >> y[i];
            a[i]--,b[i]--;
            adj[a[i]].pb({b[i],{x[i],y[i]}});
            adj[b[i]].pb({a[i],{y[i],x[i]}});
        }
        ans=0;
        dfs(0);
        for(int i=1;i<=n;i++){
            if(mn[i]<0){
                ans=mul(ans, powe(i, -mn[i]));
            }
        }
        cout << ans << "\n";
    }


    return 0;
}
