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
string s, t;
int nxt[N][26];
int pos[26];

void test_case() {
    cin >> s >> t;
    string tmp = s + s;
    memset(pos, -1, sizeof(pos));
    for (int i = tmp.size() - 1; i >= 0; i--) {
        pos[tmp[i] - 'a'] = i;
        for (int j = 0; j < 26; j++) {
            nxt[i][j] = pos[j];
        }
    }
    int ans = 1;
    int cur = 0;
    for (int i = 0; i < t.size(); i++) {
        int id = t[i] - 'a';
        int nx = nxt[cur][id];
        cur = nx + 1;
        if (cur >= s.size()) {
            ans++;
        }
        cur %= (s.size());
    }
    if(cur==0){
        ans--;
    }
    cout << ans << endl;
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
