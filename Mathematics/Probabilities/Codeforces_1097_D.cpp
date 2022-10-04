//https://codeforces.com/contest/1097/problem/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

ll fact[N];
ll invfact[N];
int cnkdp[61];

int mul(int u , int v, int mod=MOD){
    return ((u%mod)*1ll*(v%mod))%mod;
}
int add(int u, int v, int mod=MOD){
    return ((u%mod)+0ll+(v%mod)+mod)%mod;
}

int sub(int u, int v , int mod=MOD){
    return ((u%mod)+0ll-(v%mod)+mod)%mod;
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

ll n;
int k;

int dp[51][10004][51];
int ans[51][51];
int invp[51];

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init(20000);
    for(int i=1;i<=50;i++){
        invp[i]=inv(i);
    }
    for(int i=1;i<=50;i++){
        dp[i][0][i]=1;
    }
    cin >> n >> k;
    for(int i=1;i<=50;i++){
        for(int j=1;j<=k;j++){
            for(int o=1;o<=i;o++){
                dp[i][j][o]=sub(dp[i][j-1][i], dp[i][j-1][o-1]);
                if(j==k){
                    ans[i][o]=dp[i][j][o];
                }
                dp[i][j][o]=add(mul(invp[o],dp[i][j][o]),dp[i][j][o-1]);
            }
        }
    }

    ll res=1;
    ll s=1;
    for(ll x = 2;x*x<=n;x++){
        if(n%x==0){
            int y = x;
            int rs=0;
            int nb=0;

            while(n%x==0){
                n/=x;
                nb++;
            }
            s=mul(s, nb+1);
            int cur=1;
            for(int j=0;j<=nb;j++){
                rs=add(rs, mul(cur, ans[nb+1][j+1]));
                cur=mul(cur, x);
            }
            res=mul(res, rs);
        }
    }
    if(n>1){
        n%=MOD;
        int cur = 1;
        int rs=0;
        s=mul(s, 1+1);
        for(int j=0;j<=1;j++){
            rs=add(rs, mul(cur, ans[1+1][j+1]));
            cur=mul(cur, n);
        }
        res=mul(res, rs);
    }
    res=mul(res, inv(s));
    cout << res ;

    return 0;

}
