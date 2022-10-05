//https://codeforces.com/problemset/problem/128/C

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

int n,m,k;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init(3000);
    cin >> n >> m >> k;
    n-=2*k+1;
    m-=2*k+1;
    if(n<0 || m<0){
        cout << 0;
    }else{
        ll rs = cnk(2*k+1+n-1,n);
        rs=mul(rs, cnk(2*k+1+m-1,m));
        cout << rs ;
    }

    return 0;

}
