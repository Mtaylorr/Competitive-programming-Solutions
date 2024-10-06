#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define mp make_pair
#define pb push_back
#define ll long long
#define ld long double
#define ft first
#define sd second
#define sqr(n) ((n)*(n))
#define sz(v) ((ll)v.size())
#define all(v) v.begin(), v.end()
#define exists(v,x)  (v.find(x) != v.end())
#define yes cout<<"Yes"<<endl
#define no cout<<"No"<<endl
#define endl '\n'
using namespace std;
const ld EPS = (1e-10);
const double PI  = acos(-1.0);
typedef complex<double> poll;
ll dcmp(ld x, ld y) {	return abs(x-y) <= EPS ? 0 : x < y ? -1 : 1;	}
inline void fast(){ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);}
typedef __gnu_pbds::tree<ll, __gnu_pbds::null_type, less<ll>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> ordered_set;

void solve() {
    int n, m;
    cin>>n>>m;
    int rows[n] = {0}, cols[n] = {0};
    for(ll i = 1;i < n;i+=2)
        rows[i] = cols[i] = 1;
    ll r = n;
    ll c = n;
    for(ll i = 0;i < m;i++){
        string s;
        ll j;
        cin>>s>>j;
        j--;
        if(s == "ROW") {
            rows[j] ^= 1;
            if(j > 0) {
                if(rows[j] == rows[j - 1])
                    r--;
                else
                    r++;
            }
            if(j + 1 < n) {
                if(rows[j] == rows[j + 1])
                    r--;
                else
                    r++;
            }
        } else {
            cols[j] ^= 1;
            if(j > 0) {
                if(cols[j] == cols[j - 1])
                    c--;
                else
                    c++;
            }
            if(j + 1 < n) {
                if(cols[j] == cols[j + 1])
                    c--;
                else
                    c++;
            }
        }
        cout<<r * c<<endl;
    }
}

int main() {
    fast();
    ll t = 1;
//    cin>>t;
    while(t--) solve();
    return 0;
}
