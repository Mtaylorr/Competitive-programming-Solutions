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
#define yes cout<<"Yes"<<endl;
#define no cout<<"No"<<endl;
#define endl "\n"
const db pi=4*atan(1);
const int mod = 1e9+7;
const db EPS = 0.0000000001; // 1 e -9
const ll inf = (ll)1e18;
ll gcd(ll a , ll b) {return b ? gcd(b , a % b) : a ;}
ll lcm(ll a , ll b) {return (a * b) / gcd(a , b);}

int run_case(){
    ll r,u,p,h,k,n,y,z,l,e,q,w,x,j;
    cin >> k ;
    ll a[k];
    f(i,0,k,1)
    {
        cin >> a[i];
    }
    ll b[k];
    f(i,0,k,1)
    {
        cin >> b[i];
    }
    ll next[k];
    ll prev[k];
    f(i,0,k,1)
    {
        next[i]=(i+1)%k;
        prev[i]=(i-1+k)%k;
    }
    ll diff[k];
    ll diff1[k];
    f(i,0,k,1)
    {
        diff[i]=b[i]-a[i];
        diff1[i]=diff[i];
    }
    f(i,0,k,1)
    {
        if (diff1[i]<0)
        {
            if((-diff1[i])&1)
            {
                no;
                return 0;
            }
            diff1[prev[i]]-=(-diff1[i])>>1;
            diff1[next[i]]-=(-diff1[i])>>1;
            diff1[i]=0;
        }
    }
    f(i,0,k,1)
    {
        if(diff1[i])
        {
            no;
            return 0;
        }
    }
    f(i,0,k,1)
    {
        if (diff[i]>0)
        {
            if (diff[next[i]]<0 && diff[prev[i]]<0)
            {
                if (!(a[i]+((-diff[next[i]])>>1)-1<=a[next[i]]+diff[next[i]] && b[i]-1<=b[prev[i]] || a[i]+((-diff[prev[i]])>>1)-1<=a[prev[i]]+diff[prev[i]] && b[i]-1<=b[next[i]] ))
                {
                    no;
                    return 0;
                }
            }
            else if (diff[next[i]]<0)
            {
                if (!(b[i]-1<=b[next[i]] ))
                {
                    no;
                    return 0;
                }
            }
            else
            {
                if (!(b[i]-1<=b[prev[i]] ))
                {
                    no;
                    return 0;
                }
            }
        }
    }
    yes;
    return 0;
}

signed main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    ll t = 1;//cin >> t;
    while(t--){
        run_case();
    }
    return 0;
}
