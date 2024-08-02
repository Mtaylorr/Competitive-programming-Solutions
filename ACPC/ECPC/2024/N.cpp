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
const db pi=3.14159265359;
const int mod = 998244353;
const db EPS = 0.000000000001; // 1 e -9
const ll inf = (ll)1e18;
ll gcd(ll a , ll b) {return b ? gcd(b , a % b) : a ;}
ll lcm(ll a , ll b) {return (a * b) / gcd(a , b);}

ll n1;

ll mrg (ll x ,ll y )
{
    return x+y;
}

struct segment_tree
{
    vector<ll> tree;
    void clear()
    {
        tree.clear();
    }

    void init(int num, const vector<ll>& a)
    {
        n1 = num;
        tree.assign(4 * n1, 0ll);
        build(a);
    }

    void build(const vector<ll>& a, int id=0,int ns = 0, int ne = n1-1)
    {
        if(ns==ne){
            tree[id] = a[ns];
            return ;
        }
        int l = 2*id+1;
        int r = l+1;
        int md = ns+(ne-ns)/2;
        build(a,l, ns, md);
        build(a,r, md+1, ne);
        tree[id] = mrg(tree[l],tree[r]);
    }


    ll query(int qs, int qe, int id=0, int ns=0, int ne=n1-1)
    {
        if(ns>qe || qs>ne){
            return 0; ///infnity
        }
        if(qs<=ns && qe>=ne){
            return tree[id];
        }
        int l = 2*id+1;
        int r = l+1;
        int md = ns+(ne-ns)/2;
        ll ndl = query(qs, qe, l, ns, md);
        ll ndr = query(qs, qe,r, md+1,ne);
        return mrg(ndl,ndr );
    }

    void upd(int pos , int val , int id=0, int ns=0,int ne=n1-1)
    {
        if(ns>pos || pos>ne){
            return;
        }
        if(ns==ne){
            tree[id]=val;
            return ;
        }
        int l = 2*id+1;
        int r = l+1;
        int md = ns+(ne-ns)/2;
        upd(pos, val,l, ns, md);
        upd(pos, val, r, md+1, ne);
        tree[id] = mrg(tree[l],tree[r]);
    }
} sta ;

int run_case()
{
    ll  k,n,u,h,p,i,j,z,e,q,w,l,x,y,r;
    cin >> k ;
    p=0;
    vl a(k);
    f(i,0,k,1)
    {
        cin >> a[i];
    }
    sta.init(k,a);
    sl s;
    s.insert(0);
    f(i,1,k,1)
    {
        while (s.size())
        {
            q=*s.rbegin();
            if (sta.query(q,i-1)>=a[i])
            {
                p+=i-q;
                break;
            }
            s.erase(*s.rbegin());
        }
        s.insert(i);
    }
    cout << p << endl;
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
