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
int n;
int a[N];
bool done[N];
vector<int> v[N];
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 1; j * j <= a[i]; j++) {
            if (a[i] % j == 0) {
                v[j].pb(i);
                if (a[i] != j * j) {
                    v[a[i] / j].pb(i);
                }
            }
        }
    }
    int nb=n;
    for (int i = 1e6; i >= 2; i--) {
        while (1) {
            int x = -1;
            while (v[i].size() && done[v[i].back()]) {
                v[i].pop_back();
            }
            if (v[i].size()) {
                x = v[i].back();
            }
            if (x == -1) break;
            v[i].pop_back();
            int y = -1;
            while (v[i].size() && done[v[i].back()]) {
                v[i].pop_back();
            }
            if (v[i].size()) {
                y = v[i].back();
            }
            if (y == -1) {
                break;
            }
            v[i].pop_back();
            done[x] = 1;
            done[y] = 1;
            nb-=2;
        }
    }
    cout << nb << endl;
    for (int i = 0; i < n; i++) {
        if (!done[i]) {
            cout << a[i] << " ";
        }
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
