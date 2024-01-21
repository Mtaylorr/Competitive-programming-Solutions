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

vector<string> tmp[2];
int n, k;
void test_case() {
    cin >> n >> k;
    if (n % 2) {
        cout << "No solution";
        return;
    }
    tmp[0].pb("W");
    tmp[0].pb("B");
    int b = -1;
    for (int i = 1;; i++) {
        int id = i & 1;
        tmp[id].clear();

        for (auto &x : tmp[id ^ 1]) {
            tmp[id].pb(x + "W");
        }
        reverse(all(tmp[id ^ 1]));
        for (auto &x : tmp[id ^ 1]) {
            tmp[id].pb(x + "B");
        }

        if (tmp[id].size() >= n) {
            b = id;
            break;
        }
    }
    if (tmp[b][0].size() > k) {
        cout << "No solution";
        return;
    }
    int s = tmp[b].size() / 2;
    int l = s - n / 2;
    while (n--) {
        string ans = tmp[b][l++];
        while (ans.size() < k) {
            ans += "W";
        }
        cout << ans << endl;
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
