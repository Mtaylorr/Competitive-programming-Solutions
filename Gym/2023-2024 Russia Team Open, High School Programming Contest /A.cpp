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

string s;
int n;
int nb[30];
int cur[30];

void test_case() {
    memset(nb, -1, sizeof(nb));
    cin >> s;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        int x;
        cin >> c;
        cin >> x;
        nb[c - 'a'] = x;
    }
    int r = 0;
    for (auto &c : s) {
        int x = c - 'a';
        if (nb[x] == -1) {
            r++;
        } else {
            if (cur[x] == 0) {
                r += 2;
                cur[x] = nb[x] - 2;
            } else {
                r++;
                cur[x]--;
            }
        }
    }
    cout << r << endl;
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
