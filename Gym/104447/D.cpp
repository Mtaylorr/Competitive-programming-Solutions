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

int freq[1050];
vector<int> vals;
int n, k;
int a[N];
void test_case() {
    memset(freq, 0, sizeof(freq));
    vals.clear();
    cin >> n >> k;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for (int i = 0; i < 1024; i++) {
        int x = i;
        int p = 0;
        while (x) {
            p += (x % 2);
            x /= 2;
        }
        if (p == k) {
            vals.pb(i);
        }
    }
    int ans = 0;
    freq[0] = 1;
    for (auto u : vals) {
        freq[u] = 1;
        ans=max(ans,u);
    }
    int s = 0;

    for (int i = 0; i < n; i++) {
        s = s ^ a[i];
        for (int j = 0; j <= 1023; j++) {
            if (freq[j]) {
                ans = max(ans, s ^ j);
            }
        }
        freq[s] = 1;
        ans=max(ans,s);
        for (auto u : vals) {
            freq[s ^ u] = 1;
            ans=max(ans, s^u);
        }
    }
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
