// Mtaylor
#pragma GCC optimize("Ofast")
// #pragma GCC target ("avx2")
// #pragma GCC optimization ("O3")
#pragma GCC optimization("unroll-loops")
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

int g[N];
int nb = 0;
int ex[N];
void preprocess() {
    g[0] = 0;
    int mx = 0;
    for (int i = 1; i <= 1e6; i++) {
        int sq = sqrt(i);
        for (int j = 1; j <= sq; j++) {
            ex[g[i - j * j]] = 1;
        }
        g[i] = 0;
        while (ex[g[i]]) g[i]++;
        for (int j = 0; j <= 168; j++) {
            ex[j] = 0;
        }
    }
}
int n;

void test_case() {
    scanf("%d",&n);
    if (g[n]) {
        printf("Win\n");
    } else {
        printf("Lose\n");
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    preprocess();
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
