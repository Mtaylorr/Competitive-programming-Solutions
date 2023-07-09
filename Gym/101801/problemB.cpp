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

map<int, int> freq;
int a[N];
int n;

void test_case() {
    cin >> n;
    freq.clear();
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int x = a[i];
        for (int j = 2; j * j <= x; j++) {
            if (x % j == 0) freq[j]++;
            while (x % j == 0) {
                x /= j;
            }
        }
        if (x > 1) freq[x]++;
    }
    int ans = 0;
    for (auto &u : freq) {
        ans += (u.se + 2) / 3;
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
