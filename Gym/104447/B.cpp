// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
typedef long long ll;
const int N = 3e5 + 5;

int n, k, m;
vector<int> v;
void test_case() {
    cin >> n >> k >> m;
    v.clear();
    for (int i = 0; i < m; i++) {
        int id;
        cin >> id;
        int h;
        cin >> h;
        char c;
        cin >> c;
        int m;
        cin >> m;
        v.pb(h * 60 + m);
    }
    sort(all(v));
    int ans=0;
    int bef=1e9;
    for(auto u:v){
        if(u-bef>k){
            ans++;
        }
        bef=u;
    }
    ans++;
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
