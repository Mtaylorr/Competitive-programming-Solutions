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

int n, k;
ll w[N], x[N], y[N], r[N];
double d[N];
vector<pair<int, int> > ans;
void test_case() {
    cin >> n;
    vector<int> ordmet;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        ordmet.pb(i);
    }
    sort(all(ordmet), [](int &x, int &y) {
        return w[x] > w[y];
    });
    cin >> k;
    vector<int> ord;
    for (int i = 0; i < k; i++) {
        ord.pb(i);
        cin >> x[i] >> y[i] >> r[i];
        d[i] = sqrt(x[i] * x[i] + y[i] * y[i]) - r[i];
    }

    sort(all(ord), [](int &x, int &y) { return d[x] < d[y]; });
    int j = 0;
    for (int i = 0; i < n; i++) {
        double dmet = sqrt(1e6 / (1.0 * w[ordmet[i]]));
        if (j < ord.size() && d[ord[j]] <= dmet) {
            ans.pb({ordmet[i], ord[j]});
            j++;
        }
    }
    cout << ans.size() << endl;
    sort(all(ans));
    for (auto &u : ans) {
        cout << u.fi + 1 << " " << u.se + 1 << endl;
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
