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

int n, a, b;
int x[N], y[N];

bool theory[N];

void test_case() {
    cin >> n >> a >> b;
    ll sm = 0;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        sm += x[i];
        theory[i] = 1;
    }
    vector<int> ord;
    for (int i = 0; i < n; i++) {
        cin >> y[i];
        y[i] = y[i] - x[i];
        ord.pb(i);
    }
    sort(all(ord), [](int &a, int &b) { return y[a] > y[b]; });
    for (int i = 0; i < n; i++) {
        if (n - i == a) break;
        if (i < b) {
            sm += y[ord[i]];
            theory[ord[i]] = 0;
        } else if (y[ord[i]] > 0) {
            sm += y[ord[i]];
            theory[ord[i]] = 0;
        }
    }
    cout << sm << endl;
    for (int i = 0; i < n; i++) {
        cout << "PT"[theory[i]] << " ";
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
