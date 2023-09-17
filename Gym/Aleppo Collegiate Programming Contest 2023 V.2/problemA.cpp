//IMK solution
#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<char> vchr;
typedef vector<string> vstr;
typedef vector<vi> vvi;
typedef vector<vchr> vvchr;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<vll> vvll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;

#define endl '\n';
#define yes cout << "YES\n";
#define no  cout << "NO\n";
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
mt19937_64 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
    ~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
	*this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
    sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define MP make_pair
#define PB push_back
#define fastio ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define For(i, n) for(int i=0; i < n; ++i)
#define Forr(i, n, p) for(int i=p; i < n; ++i)
#define dd(arr) For(i, arr.size()) cout << arr[i] << " "; cout << endl;



const int N = 2e6+7;
int n, x;
vector<int> arr;

map<pair<int,int>,int> dp;

int work(int i, int xx){
    if(xx == 1) return 0;
    if(i == (int)arr.size()) return 1e6;
    if(dp.count({i,xx})) return dp[{i,xx}];

    int xxx = xx;
    int gcdd=gcd(xxx,arr[i]);
    xxx=xxx/gcdd;
    int  ans = min(work(i+1, xx), 1 + work(i+1, xxx));
    return dp[{i,xx}]=ans;
}

void solve(){
    cin >> n >> x;
    map<int,int> mp;
    For(i, n) {
        ll v;
        cin >> v;
        v=gcd(v,x);
        if(v==1) continue;
        mp[v]++;
    }

    for(auto el:mp){
        int nb = 0;
        ll k = el.first;
        int mx = 1e9;
        while (k < mx) {
            nb++;
            k*= el.first;
        }
        for(int i=0;i<min((int)el.second,nb);i++){
            arr.push_back(el.first);
        }
    }
    int ans = work(0, x);
    cout << (ans == 1e6 ? -1 : ans) << endl;
}

int main(){
    fastio;
    // cout << setprecision(9);
    // cout << fixed;
    // freopen("input.in", "r", stdin);
    // freopen("output.out", "w", stdout);
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}
