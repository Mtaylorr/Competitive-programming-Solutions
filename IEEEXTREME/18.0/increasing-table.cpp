//https://csacademy.com/ieeextreme18/task/increasing-table/
#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cstring>
#include <math.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double db;
//typedef double db;
#define int ll
#define ss second
#define ff first
#define pb push_back
#define vi vector<int>
#define pii pair<int,int>
#define vii vector<pii>
#define vl vector<ll>
#define pll pair<ll,ll>
#define vll vector<pll>
#define vd vector<db>
#define pdd  pair<db,db>
#define vdd  vector<pdd>
#define mll map <ll,ll>
#define sl set <ll>
#define sll set <pll>
#define f(i,j,k,l) for(ll i=j;i<k;i+=l)
#define fj(j,m) for(auto j=m.begin();j!=m.end();j++)
#define yes cout<<"YES"<<endl;
#define no cout<<"NO"<<endl;
#define endl "\n"
const db pi=3.14159265359;
const int mod = 998244353;
const db EPS = 0.000000000001; // 1 e -9
const ll inf = (ll)1e18;
ll gcd(ll a , ll b) {return b ? gcd(b , a % b) : a ;}
ll lcm(ll a , ll b) {return (a * b) / gcd(a , b);}

sl s,s1;

ll add(ll a, ll b){
    return (a + b) % mod;
}
ll sub(ll a, ll b){
    return (a - b + mod) % mod;
}
ll mul(ll a, ll b){
    return (((ll)a%mod) * ((ll)b%mod)) % mod;
}
ll bin_pow(ll n, ll k){
    if(k == 0)return 1;
    if(k == 1)return n;
    if(k % 2 == 1) return mul(n, bin_pow(n, k - 1));
    ll t = bin_pow(n, k / 2);
    return mul(t, t);
}
const int MAXN = 4001;
int fact[MAXN];
int inv_fact[MAXN];
ll rev(int x){
    return bin_pow(x, mod - 2);
}
void comb(){
    fact[0] = 1;
    for(int i = 1;i < MAXN;i++){
        fact[i] = mul(i, fact[i - 1]);
    }
    inv_fact[MAXN - 1] = rev(fact[MAXN - 1]);
    for(int i = MAXN - 2;i >= 0;i--){
        inv_fact[i] = mul(inv_fact[i + 1], i + 1ll);
    }
}
int C(int n, int k){
    //C(n, k) = n! / ((n - k)! * k!)
    if(n < k || k < 0)return 0;
    return mul(fact[n], mul(inv_fact[k], inv_fact[n - k]));
}
ll power(ll x , ll y)
{
    return bin_pow(x,y)%mod;
}
ll mod_inv (ll a)
{
    return power(a,mod-2);
}

ll dp[4001][2001];

ll fh(ll i,ll j,ll n)
{
    if (i==2*n+1) return j==n;
    if (j>n) return 0;
    if (i-1-j>j) return 0;
    if (~dp[i][j]) return dp[i][j];
    if (s.count(i)) return dp[i][j]=fh(i+1,j+1,n);
    if (s1.count(i)) return dp[i][j]=fh(i+1,j,n);
    return dp[i][j]=add(fh(i+1,j+1,n),fh(i+1,j,n));
}

int run_case()
{
    ll  k,n,u,p,i,j,h,z,e,q,w,l,x,y,r;
    cin >> n ;
    cin >> x ;
    comb();
    memset(dp,255,sizeof(dp));
    ll a[x];
    f(i,0,x,1)
    {
        cin >> a[i] ;
        s.insert(a[i]);
    }
    cin >> y ;
    ll b[y];
    h=0;
    f(i,0,y,1)
    {
        cin >> b[i] ;
        s1.insert(b[i]);
        if (s.count(b[i]))h=1;
    }
    if (s1.count(1) || s.count(2*n) || h)
    {
        cout << 0 << endl;
        return 0;
    }
    s.insert(1);
    s1.insert(2*n);
    if (s.size()>n || s1.size()>n)
    {
        cout << 0 << endl;
        return 0 ;
    }
    cout << fh(1,0,n) << endl;
    /*ll a[k];
    f(i,0,k,1)
    {
        cin >> a[i];
    }*/
    return 0;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    ll t = 1;//cin >> t;
    while(t--){
        run_case();
    }
    return 0;
}
