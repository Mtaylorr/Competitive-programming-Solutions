// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
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

int val[N];
int f[3];

int ask(int u) {
    cout << "get " << u << endl;
    int r;
    cin >> r;
    val[u] = r;
    return r;
}

void askswap(int u, int v) {
    cout << "swap " << u << " " << v << endl;
    swap(val[u], val[v]);
}

int n;
void test_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x = ask(i);
        f[x]++;
    }
    vector<int> tmp;
    for (int i = f[0] + 1; i <= n; i++) {
        if (val[i] == 0) {
            tmp.pb(i);
        }
    }
    for (int i = 1; i <= f[0]; i++) {
        if (val[i] != 0) {
            askswap(i, tmp.back());
            tmp.pop_back();
        }
    }
    tmp.clear();
    for (int i = f[0] + f[1] + 1; i <= n; i++) {
        if (val[i] == 1) {
            tmp.pb(i);
        }
    }
    for (int i = f[0] + 1; i <= f[0] + f[1]; i++) {
        if (val[i] != 1) {
            askswap(i, tmp.back());
            tmp.pop_back();
        }
    }
    cout << "Sorted!";
    return;
}

int main() {
    // freopen("input.txt", "r", stdin);
    int T = 1;

    while (T--) {
        test_case();
    }
    return 0;
}
