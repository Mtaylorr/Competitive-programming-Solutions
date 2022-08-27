//https://codeforces.com/problemset/problem/895/C

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 1 << 17;
const int MOD = 1e9 + 7;

int n;
int primes=0;
vector<int> p;
int mask[N];
int freq[N];
int x;
int po[N];
int dp[71][1<<19];

ll mul(ll u , ll v, ll mod=MOD){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
    return ((u%mod)+(v%mod)+mod)%mod;
}
ll sub(ll u, ll v , ll mod=MOD){
    return ((u%mod)-(v%mod)+mod)%mod;
}

bool isprime(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0)
            return 0;
    }
    return 1;
}

ll solve(int p,int m){
    if(p>=71)
        return (m==0);
    if(dp[p][m]!=-1)
        return dp[p][m];
    if(freq[p]==0){
        return dp[p][m]=solve(p+1,m);
    }
    ll sz = po[freq[p]-1];
    ll rs= add(solve(p+1, m), solve(p+1, m^mask[p]));
    rs=mul(rs, sz);
    return dp[p][m]=rs;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    for(int i=2;i<=70;i++){
        if(isprime(i)){
            p.pb(i);
        }
    }
    cin >> n;
    for(int i=1;i<=70;i++){
        int msk=0;
        int x = i;
        for(int j=0;j<p.size();j++){
            int nb=0;

            while(x%p[j]==0){
                nb++;
                x/=p[j];
            }
            nb%=2;
            msk+=(nb)*(1<<j);
        }
        mask[i]=msk;
    }
    for(int i=0;i<n;i++){
        cin >> x;
        freq[x]++;
    }
    po[0]=1;
    for(int i=1;i<=n;i++){
        po[i]=mul(2, po[i-1]);
    }
    cout << sub(solve(1,0),1);
    return 0;
}
