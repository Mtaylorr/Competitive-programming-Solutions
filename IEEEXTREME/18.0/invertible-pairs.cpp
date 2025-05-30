//https://csacademy.com/ieeextreme18/task/invertible-pairs/
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

int run_case()
{
    ll  n,u,p,i,j,h,k,z,e,q,w,l,x,y,r;
    cin >> n ;
    ll a[n];
    f(i,0,n,1)
    {
        cin >> a[i];
    }
    p=0;
    l=0;
    r=0;
    f(i,0,n,2)
    {
        p=max(p,r+abs(a[i])-l);
        r+=abs(a[i]+a[i+1]);
        l=min(l,r-abs(a[i+1]));
    }
    p=max(p,r-l);
    cout << p << endl;
    return 0;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    ll t = 1;cin >> t;
    while(t--){
        run_case();
    }
    return 0;
}
