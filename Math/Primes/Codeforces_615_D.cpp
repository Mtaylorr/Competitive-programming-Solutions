//https://codeforces.com/problemset/problem/615/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 4e5 + 5, E = 1 << 17;
const int MOD =  1e9 + 7;


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


int n;
int primes[N];
int x;
int up[N], down[N];
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin  >> x;
        primes[x]++;
    }
    int ans=1;
    int nb=1;
    up[0]=up[1]=1;
    for(int i=2;i<=200000;i++){
        up[i]=mul(up[i-1], primes[i]+1, MOD-1);
    }
    down[200001]=1;
    for(int i=200000;i>=1;i--){
        down[i]=mul(down[i+1], primes[i]+1, MOD-1);
    }
    for(int i=2;i<=200000;i++){
        if(!primes[i])
            continue;
        int nb = mul(up[i-1], down[i+1], MOD-1);
        int prod = powe(i,(primes[i]*1ll*(primes[i]+1))/2);
        ans=mul(ans, powe(prod, nb));
    }
    cout << ans;
    return 0;
}
