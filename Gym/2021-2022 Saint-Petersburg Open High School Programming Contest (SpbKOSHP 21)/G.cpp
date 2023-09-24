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

int n;
ll a[N], b[N];
ll c[N];
ll base[62];
int ind[62];
int init_swaps[N];
vector<int> bef[N];

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        c[i] = b[i];
    }
    ll tot = 0;
    for (int i = 0; i < n; i++) {
        tot ^= a[i];
        b[i] ^= a[i];
    }
    memset(base, -1, sizeof(base));
    for (int i = 0; i < n; i++) {
        ll x = b[i];
        vector<int> tmp;

        for (int j = 59; j >= 0; j--) {
            if (!((1ll << j) & x)) continue;
            if (base[j] != -1) {
                x ^= base[j];
                tmp.pb(ind[j]);
                continue;
            }
            // dbg(j, i, x, b[i]);
            // for (auto &u : tmp) {
            //     cout << u << " ";
            // }
            // cout << endl;
            base[j] = x;
            ind[j] = i;
            bef[j] = tmp;
            break;
        }
    }
    for (int j = 59; j >= 0; j--) {
        ll c = (1ll << j);
        if (tot & c) continue;
        if (base[j] == -1) continue;
        tot ^= base[j];
        init_swaps[ind[j]]++;
        init_swaps[ind[j]] %= 2;
    }
    for (int j = 0; j <= 59; j++) {
        if (base[j] != -1) {
            ll x = b[ind[j]];
            //dbg(j, init_swaps[ind[j]]);
            for (auto &u : bef[j]) {
                //dbg(j, u, x);
                init_swaps[u] += init_swaps[ind[j]];
                init_swaps[u] %= 2;
            }
        }
    }
    ll sma = 0;
    ll smb = 0;
    vector<int> indices;

    for (int i = 0; i < n; i++) {
        if (init_swaps[i] % 2) {
            //dbg(i, init_swaps[i]);
            swap(a[i], c[i]);
            indices.pb(i + 1);
        }
        sma ^= a[i];
        smb ^= c[i];
    }
    cout << sma + smb << " " << indices.size() << endl;
    for (auto &u : indices) {
        cout << u << " ";
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
