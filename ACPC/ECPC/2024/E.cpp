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
//#define int ll
#define ss second
#define ff first
#define pb push_bac
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
const db EPS = 0.000000000000001; // 1 e -9
const ll inf = (ll)1e18;
ll gcd(ll a , ll b) {return b ? gcd(b , a % b) : a ;}
ll lcm(ll a , ll b) {return (a * b) / gcd(a , b);}

ll cross(ll x1,ll y1,ll x2,ll y2,ll x3,ll y3)
{
    return (x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);
}

ll cross1(ll x1,ll y1,ll x2,ll y2,ll x3,ll y3)
{
    return (x2-x1)*(x3-x1)+(y3-y1)*(y2-y1);
}

db dist(ll x1,ll y1,ll x2,ll y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

int run_case()
{
    ll  k,n,u,h,p,i,j,z,e,q,w,l,x,y,r;
    ll x1,y1,x2,y2,x3,y3,xt,yt;
    cin >>  x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> xt >> yt >> p ;
    if (p)
    {
        swap(x1,x3);
        swap(y1,y3);
    }
    ll vectoriel=cross(x2,y2,x3,y3,xt,yt);
    ll scalar=cross1(x2,y2,x3,y3,xt,yt);
    if (vectoriel==0 || scalar<=0)
    {
        no;
        return 0;
    }
    db vectoriel1=cross(x2,y2,x3,y3,x1,y1);
    ll scalar1=cross1(x2,y2,x3,y3,x1,y1);
    db alpha=180.0/pi*asin((db)vectoriel/(dist(x2,y2,x3,y3)*dist(x2,y2,xt,yt)));
    db betta=180.0/pi*asin(vectoriel1/(dist(x2,y2,x3,y3)*dist(x2,y2,x1,y1)));
    cout << setprecision(7) << fixed ;///(res+betta)/2=alpha => res = 2*alpha-betta
    if (scalar1<0)
    {
        if(betta<0)
        {
            betta=-(180+betta);
        }
        else
        {
            betta=180-betta;
        }
    }
    //cout << alpha << " " << betta << endl;
    if (alpha * betta < 0)
    {
        no;
        return 0;
    }
    yes;
    cout << 2*alpha-betta << endl;
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
