//https://csacademy.com/ieeextreme18/task/ieee754-emulator/
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

map<char,string> m;
map<string,char> mm;

string fh(string &t)
{
    string tt;
    f(i,0,8,1)
    {
        tt+=m[t[i]|' '];
    }
    return tt;
}

string fg(string &t)
{
    string tt;
    string t1;
    f(i,0,8,1)
    {
        t1="";
        f(j,0,4,1)
        {
            t1+=t[i*4+j];
        }
        tt+=mm[t1];
    }
    return tt;
}

string nnd(string &t,string &t1)
{
    string tt;
    f(i,0,32,1)
    {
        tt+=(1-((t[i]-'0')&(t1[i]-'0')))+'0';
    }
    return tt;
}

float binaryToFloat(const string &binary) {
    bitset<32> bits(binary);
    float value;
    memcpy(&value,&bits,sizeof(float));
    return value;
}

string floatToBinary(float value) {
    bitset<32> bits;
    memcpy(&bits, &value, sizeof(float));
    return bits.to_string();
}

string fma(const string &t, const string &t1, const string &t2) {
    float a = binaryToFloat(t);
    float b = binaryToFloat(t1);
    float c = binaryToFloat(t2);
    float result = fma(a,b,c);
    return floatToBinary(result);
}

void prep()
{
    m['0']="0000";
    m['1']="0001";
    m['2']="0010";
    m['3']="0011";
    m['4']="0100";
    m['5']="0101";
    m['6']="0110";
    m['7']="0111";
    m['8']="1000";
    m['9']="1001";
    m['a']="1010";
    m['b']="1011";
    m['c']="1100";
    m['d']="1101";
    m['e']="1110";
    m['f']="1111";
    fj(j,m)
    {
        mm[j->ss]=j->ff;
    }
    return ;
}

int run_case()
{
    ll  n,u,p,i,j,h,z,e,q,w,l,x,y,r,b;
    string t;
    cin >> t;
    cin >> l;
    ll k[l];
    string tt;
    t=fh(t);
    vector<string> lut[l];
    f(i,0,l,1)
    {
        cin >> k[i];
        f(j,0,k[i],1)
        {
            cin >> tt ;
            lut[i].pb(fh(tt));
        }
    }
    cin >> q;
    char c ;
    string t1;
    vector<string> v;
    v.pb(t);
    f(iiii,0,q,1)
    {
        cin >> c;
        if (c=='C')
        {
            cin >> t1;
            v.pb(fh(t1));
        }
        else if (c=='L')
        {
            cin >> i >> j >> b;
            p=0;
            r=1;
            for(int ii=j;ii<=j+b-1;ii++)
            {
                if (t[31-ii]=='1')p+=r;
                r*=2;
            }
            v.pb(lut[i][p]);
        }
        else if (c=='N')
        {
            cin >> i >> j ;
            v.pb(nnd(v[i],v[j]));
        }
        else
        {
            cin >> i >> j >> r ;
            v.pb(fma(v[i],v[j],v[r]));
        }
        //cout << iiii << " " << v.back() << endl;
    }
    cout << fg(v.back()) << endl;
    /*ll a[k];
    f(i,0,k,1)
    {
        cin >> a[i];
    }*/
    return 0;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    ll t = 1;cin >> t;
    prep();
    while(t--){
        run_case();
    }
    return 0;
}
