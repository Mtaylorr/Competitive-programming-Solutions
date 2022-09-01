//https://codeforces.com/problemset/problem/1000/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 4e5 + 5, E = 1 << 17;
const int MOD =  998244353;


int n;
int dp[N];
int a[N];
ll fact[N];
ll invfact[N];

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

void init_fact(ll n, ll mod=MOD){
    fact[0]=fact[1]=1;
    for(int i=2;i<=n;i++){
        fact[i]=mul(i,fact[i-1],mod);
    }
}

ll cnk (ll n , ll k){
    if(k>n)return 0;
    if(n==0)return 1;
    ll ans = mul(fact[n],invfact[k]);
    ans= mul(ans,invfact[n-k]);
    return ans;
}

void init_inv_fact(ll n, ll mod=MOD){
    for(int i=0;i<=n;i++){
        invfact[i]=powe(fact[i],mod-2,mod);
    }
}
void init(ll n, ll mod=MOD){
    init_fact(n,mod);
    init_inv_fact(n,mod);
}



int solve(int p){
    if(p>=n){
        return 1;
    }
    if(dp[p]!=-1){
        return dp[p];
    }
    int rs= solve(p+1) ;
    if(a[p]>=1 && p+a[p]+1<=n){
        for(int j=p+a[p]+1;j<=n;j++){
            int x = j-p-2;
            int y = a[p]+1-2;
            rs=add(rs, mul(cnk(x,y),solve(j)));
        }

    }
    return dp[p]=rs;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init(10005);
    memset(dp,-1, sizeof(dp));
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    cout << sub(solve(0),1);
    return 0;
}
