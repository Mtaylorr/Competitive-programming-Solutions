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

string led[N];
string pat[N];
int r, c, k;
set<int> rows;

void test_case() {
    cin >> r >> c >> k;
    for (int i = 0; i < r; i++) {
        cin >> led[i] >> pat[i];
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (led[i][j] == '-') {
                rows.insert(i);
            }
        }
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < k; j++) {
            if (pat[i][j] == '*' && rows.count(i)) {
                cout << "N";
                return;
            }
        }
    }
    cout << "Y";
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
