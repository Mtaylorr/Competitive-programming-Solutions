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
const int N = 1e6 + 5;

map<int, int> freq;
int n, a[N];

void test_case() {
    freq.clear();
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]]++;
    }
    if (n == 1) {
        cout << "NO\n";
        return;
    }
    if (freq.size() <= 2) {
        cout << "YES\n";
        return;
    }
    sort(a, a + n);
    if (freq[a[0]] >= 2 && freq[a[n - 1]] >= 2) {
        cout << "YES\n";
        return;
    }
    for (int i = 1; i < n - 1; i++) {
        map<int, int> tmp;
        int z = a[i] - a[0];
        int w = a[n - 1] - z;
        tmp[a[0]]++;
        tmp[a[i]]++;
        tmp[a[n - 1]]++;
        tmp[w]++;
        bool cond = true;
        for (auto &u : tmp) {
            if (freq[u.fi] < u.se) {
                cond = false;
            }
        }
        if (cond) {
            if (w <= z || (i + 1 < n && a[i + 1] == w)) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
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
