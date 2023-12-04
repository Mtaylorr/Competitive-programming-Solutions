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

int h[N], d[N], t[N];
int nxt[N];

void test_case() {
    for (int i = 0; i < 2; i++) {
        cin >> h[i] >> d[i] >> t[i];
    }
    nxt[0] = 0;
    nxt[1] = 0;
    int curt = 0;
    while (1) {
        if (nxt[0] == nxt[1]) {
            curt = nxt[0];
            h[0] -= d[1];
            h[1] -= d[0];
            nxt[0] += t[0];
            nxt[1] += t[1];
        } else if (nxt[0] < nxt[1]) {
            h[1] -= d[0];
            curt = nxt[0];
            nxt[0] += t[0];
        } else {
            h[0] -= d[1];
            curt = nxt[1];
            nxt[1] += t[1];
        }
        if (h[0] <= 0 && h[1] <= 0) {
            cout << "draw\n";
            return;
        } else if (h[0] <= 0) {
            cout << "player two\n";
            return;
        } else if (h[1] <= 0) {
            cout << "player one\n";
            return;
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
