//https://codeforces.com/problemset/problem/900/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 3e5 + 5, M=1000 +5,E = 2e5 +5 ;
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


int x,y;
vector<int> v;

int solve(int x){
    return powe(2,x-1);
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> x >> y;
    if(y%x){
        cout << 0;
        return 0;
    }
    y/=x;
    ll z = y;
    for(int i=2;i*i<=z;i++){
        if(z%i==0){
            v.pb(i);
            while(z%i==0){
                z/=i;
            }
        }
    }
    if(z>1){
        v.pb(z);
    }
    int s = v.size();
    int ans=0;
    for(int msk=0;msk<(1<<s);msk++){
        int nb=0;
        int va = 1;
        for(int j=0;j<s;j++){
            if((1<<j)&msk){
                va*=v[j];
                nb++;
            }
        }
        if(nb%2==0){
            ans=add(ans, solve(y/va));
        }else{
            ans=sub(ans, solve(y/va));
        }
    }
    cout << ans;


    return 0;
}
