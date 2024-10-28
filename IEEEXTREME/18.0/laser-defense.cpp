//https://csacademy.com/ieeextreme18/task/laser-defense/
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

bool cmp(pair<char,ll> &a,pair<char,ll> &b)
{
    return a.first=='U' && b.first=='R' || a.first=='U' && a.first==b.first && a.second<b.second || a.first=='R' && a.first==b.first && a.second>b.second;
}

int run_case()
{
    ll  k,n,u,p,i,j,h,z,e,q,w,l,x,y,r,m;
    cin >> l >> n >> m ;
    ll a[n];
    char t[n];
    ll b[m];
    char t1[m];
    set<pair<char,ll>> s;
    vector<pair<char,ll>> v;
    f(i,0,n,1)
    {
        cin >> t[i] >> a[i];
        if (!s.count({t[i],a[i]}))
            v.pb({t[i],a[i]});
        s.insert({t[i],a[i]});
    }
    sort(v.begin(), v.end(), cmp);
    n=v.size();
    //fj(j,v)cout << j->ff << " " << j->ss << endl;
    x=n+1;
    s.clear();
    f(i,0,m,1)
    {
        cin >> t1[i] >> b[i];
        if (s.count({t1[i],b[i]}))continue;
        s.insert({t1[i],b[i]});
        if (t1[i]=='L')
        {
            //cout << i << endl;
            x+=n+1;
        }
        else
        {
            //cout << i << endl;
            l=0;
            r=n-1;
            while (l<r)
            {
                y=(l+r+1)/2;
                if (v[y].ff=='R')
                {
                    r=y-1;
                }
                else if (v[y].ss>b[i])
                {
                    r=y-1;
                }
                else
                {
                    l=y;
                }
            }
            y=(l+r+1)/2;
            if (v[y].ff=='R' || v[y].ss>b[i])y--;
            x+=n-y;
        }
    }
    cout << x << endl;
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
