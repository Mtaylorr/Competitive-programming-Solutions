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
int val[30];
bool used[30];
string s, t;
void test_case() {
    cin >> s >> t;
    if (s.size() != t.size()) {
        cout << "impossible\n";
        return;
    }
    memset(val, -1, sizeof(val));
    n = s.size();
    for (int i = 0; i < n; i++) {
        int p = s[i] - 'a';
        int q = t[i] - 'a';
        if (val[p] == -1) {
            val[p] = q;
            used[q] = 1;
        } else if (val[p] != q) {
            cout << "impossible\n";
            return;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (val[i] == -1) continue;
        for (int j = i + 1; j < 26; j++) {
            if (val[j] == -1) continue;
            if (val[i] == val[j]) {
                cout << "impossible\n";
                return;
            }
        }
    }
    int id = 0;
    for (int i = 0; i < 26; i++) {
        if (val[i] == -1) {
            while (used[id]) {
                id++;
            }
            cout << char('a' + id);
            id++;
        } else {
            cout << char('a' + val[i]);
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
