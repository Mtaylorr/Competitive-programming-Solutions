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
string dps[205][205];
int dpsize[205][205];
int n;

string solve(string& tmp, int i, int j) {
    int l = tmp.size();
    string res = tmp;
    for (int k = 2; k <= 9; k++) {
        if (tmp.size() % k) continue;
        int le = l / k;
        string r = tmp.substr(0, le);
        bool cond = true;

        for (int o = le; o < tmp.size(); o += le) {
            cond = cond && tmp.substr(o, le) == r;
        }
        if (cond) {
            string re = "";
            re += char('0' + k);
            re += '(';
            re += dps[i][i + le - 1];
            // dbg(i, i + le - 1, dps[i][i+le-1]);
            re += ')';
            if (re.size() < res.size()) {
                res = re;
            }
            // dbg(re, k);
        }
    }
    return res;
}

int par[N];
int dpc[205];

void test_case() {
    cin >> s;
    n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        string tmp = "";
        for (int j = i; j < n; j++) {
            tmp += s[j];
            dps[i][j] = solve(tmp, i, j);
            dpsize[i][j] = dps[i][j].size();
            for (int k = i; k < j; k++) {
                int ssz = dpsize[i][k] + dpsize[k + 1][j];
                if (ssz < dpsize[i][j]) {
                    dpsize[i][j] = ssz;
                    dps[i][j] = dps[i][k] + dps[k + 1][j];
                }
            }
        }
    }
    cout << dps[0][n - 1] << endl;
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
