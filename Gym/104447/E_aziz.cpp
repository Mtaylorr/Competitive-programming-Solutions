#pragma GCC optimize("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define pi pair<ll,ll>
#define F first
#define S second
#define all(x) (x).begin(), (x).end()
#define alll(x) ((x).begin()+1), (x).end()
#define yes cout<<"Yes"<<endl;
#define no cout<<"No"<<endl;
#define mod mod
#define endl '\n'
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll mod = 998244353;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

template<class T>
bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

template<class T>
bool ckmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }

void nop() {
    cout << -1 << endl;
    return;
}

const ll MAXN = 1e3;

long long fac[MAXN + 1], inv[MAXN + 1];

/** Computes x^y modulo p in O(log p) time. */
long long exp(long long x, long long y, long long p = mod) {
    long long res = 1;
    x %= p;
    while (y) {
        if (y & 1) {
            res *= x;
            res %= p;
        }
        x *= x;
        x %= p;
        y >>= 1;
    }
    return res;
}

/** Precomputes n! from 0 to MAXN. */
void factorial(long long p) {
    fac[0] = 1;
    for (ll i = 1; i <= MAXN; i++) { fac[i] = fac[i - 1] * i % p; }
}

/** Precomputes all modular inverse factorials from 0 to MAXN in O(n + log p)
 * time */
void inverses(long long p) {
    inv[MAXN] = exp(fac[MAXN], p - 2, p);
    for (ll i = MAXN; i >= 1; i--) { inv[i - 1] = inv[i] * i % p; }
}

/** Computes nCr mod p */
long long choose(long long n, long long r, long long p = mod) {
    if(n<r) return 0 ;
    return fac[n] * inv[r] % p * inv[n - r] % p;
}
void prep(long long p)
{
    factorial(p) ;
    inverses(p) ;
}

void fix(ll& x)
{
    assert(abs(x)<mod) ;
    if(x<0) x+= mod ;
}

ll mul(ll x , ll y)
{
    return x*y % mod ;
}
ll add(ll x , ll y)
{
    if(y<0) y+= mod ;
    x+= y ;
    if(x>=mod) x-=mod ;
    return x ;
}

int n , k ;
const int N = 702 ;
int dp[N][N] , dp1[N] , tot[N] , pref[N][N] , pref1[N][N] ;
int solve(int i)
{
    if(!i) return 0 ;
    int& ret = dp1[i] ;
    if(ret!=-1) return ret ;
    ret = 0 ;
    for(int j = 1 ; j<=i ; j++){
        ret = add(ret , mul(solve(i-j) +1 , mul(exp(tot[i] , mod-2) , dp[j][i]))) ;
    }
    return ret ;

}



void solve() {
    cin>>n>>k ;
    for(int i = 0 ; i<=n ; i++){
        for(int j = 0 ; j<=n ; j++){
            pref[i][j] = pref1[i][j]  = dp[i][j] = 0 ;
        }
        dp1[i] = -1 ;
    }


    for(int keith = 1 ; keith<=k ; keith++){
        for(int idx = 1 ; idx<=n ; idx++){
            dp[idx][idx] = keith ;
            dp[1][idx] = choose(keith , idx) ;
            for(int maxsofar = 2 ; maxsofar<idx ; maxsofar++){
                dp[maxsofar][idx] = add(pref[idx-maxsofar][maxsofar] , add(pref1[maxsofar][idx] ,- pref1[maxsofar][idx-maxsofar])) ;
            }
        }
        for(int j = 1 ; j<=n ; j++){
            for(int x = 1 ; x<=n ; x++){
                pref[j][x] = add(pref[j][x-1] , dp[x][j]) ;
                pref1[j][x] = add(pref1[j][x-1] , dp[j][x]) ;
            }
        }
    }
    for(int i = 1 ; i<=n ; i++){
        tot[i] = 0 ;
        for(int j = 1 ; j<=n ; j++){
            tot[i] = add(tot[i] , dp[j][i]) ;
        }
    }

    cout<<solve(n)<<endl;

}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    io();
    prep(mod) ;
    ll tt = 1;
    cin>>tt ;
    while (tt--) {
        solve();
    }

    return 0;
}
