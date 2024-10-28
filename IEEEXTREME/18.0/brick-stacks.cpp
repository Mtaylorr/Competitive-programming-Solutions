//https://csacademy.com/ieeextreme18/task/brick-stacks/
#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cstring>
#include <math.h>
using namespace std;
typedef int ll;
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

ll a[1000001];
ll par[1000001];
ll vis[1000001];
ll sz;

int run_case()
{
    ll  n,u,p,i,j,h,k,z,e,q,w,l,x,y,r;
    cin >> k >> x ;
    sl s;
    f(i,0,k,1)
    {
        s.insert(i);
        cin >> p;
        a[i]=p;
    }
    sort(a,a+k);
    memset(par,255,sizeof(par));
    f(i,0,k,1)
    {
        if (a[k-1]<a[i]+x)
        {
            sz++;
            continue ;
        }
        l=i+1;
        r=k-1;
        while (l<r)
        {
            y=(l+r)/2;
            if (a[y]>=a[i]+x)
            {
                r=y;
            }
            else
            {
                l=y+1;
            }
        }
        y=(l+r)/2;
        auto io=s.lower_bound(y);
        if (io==s.end())
        {
            sz++;
            continue;
        }
        y=*io;
        s.erase(y);
        par[y]=i;
    }
    cout << sz << endl;
    for (int i=k-1;i>=0; i--)
    {
        if (vis[i])continue;
        vl v;
        j=i;
        while (~j)
        {
            vis[j]=1;
            v.pb(a[j]);
            j=par[j];
        }
        cout << v.size() << " ";
        fj(j,v)cout << *j << " ";
        cout << endl;
    }
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
