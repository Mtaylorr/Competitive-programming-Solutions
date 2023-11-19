// Mtaylor
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
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

int h, w;
char gridc[4005][55];
int grid[4005][55];
int vis[4005];
int freq[55][16];
int getval(char c) {
    if (c == 'b') return 1;
    if (c == 'r') return 2;
    if (c == 'w') return 4;
    if (c == 'g') return 8;
    return 0;
}

void test_case() {
    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        cin >> gridc[i];
        for (int j = 0; j < w; j++) {
            grid[i][j] = getval(gridc[i][j]);
        }
    }
    int tot = 15;
    int lc = w * ((h / __gcd(h, w)));
    int p, q, a;
    int d;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            if (j == i) continue;
            memset(freq, 0, sizeof(freq));
            d = (j - i);
            if (d < 0) {
                d = w + d;
            }
            for (int k = 0; k <= 40000; k++) {
                p = grid[k % h][i] | grid[k % h][j];
                freq[k % w][p]++;
                p = grid[k % h][i] | grid[k % h][j];
                q = tot ^ p;
                a = (k - d + w) % w;
                // dbg(k,a);
                if (freq[a % w][q]) {
                    cout << "possible\n";
                    return;
                }
            }
        }
    }
    cout << "impossible";
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
