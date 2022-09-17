//https://codeforces.com/problemset/problem/893/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e6 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 1e9 + 7 ;

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
int q,x,y;

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init(2000000);
    cin >> q;
    while(q--){
        cin >> x >> y;
        int ans=1;
        for(int j=2;j*j<=x;j++){
            int nb=0;
            while(x%j==0){
                nb++;
                x/=j;
            }
            if(nb){
                ans=mul(ans, cnk(nb+y-1,nb));
            }
        }
        if(x>1){
            ans=mul(ans, y);
        }
        ans=mul(ans, powe(2,y-1));
        cout << ans << endl;
    }
    return 0;


}
