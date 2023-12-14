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

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

unordered_set<string> st;
vector<string> v;

string g[1005];
int n;
string s;

string getcurrent() {
    string tmp = "";
    for (int i = 0; i < n; i++) {
        tmp += g[i];
    }
    return tmp;
}
void test_case() {
    n = 0;
    while (cin >> s) {
        g[n++] = s;
    }
    int m = g[0].size();
    string tmp = getcurrent();
    while (true) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 'O') {
                    int k = i - 1;
                    while (k >= 0 && g[k][j] == '.') {
                        swap(g[k][j], g[k + 1][j]);
                        k--;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 'O') {
                    int k = j - 1;
                    while (k >= 0 && g[i][k] == '.') {
                        swap(g[i][k], g[i][k + 1]);
                        k--;
                    }
                }
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 'O') {
                    int k = i + 1;
                    while (k < n && g[k][j] == '.') {
                        swap(g[k][j], g[k - 1][j]);
                        k++;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = m - 1; j >= 0; j--) {
                if (g[i][j] == 'O') {
                    int k = j + 1;
                    while (k < m && g[i][k] == '.') {
                        swap(g[i][k], g[i][k - 1]);
                        k++;
                    }
                }
            }
        }
        tmp = getcurrent();
        if (st.count(tmp)) {
            break;
        }

        st.insert(tmp);
        v.pb(tmp);
    }
    int ind = v.size() - 1;
    int l = 0;
    while (v[ind] != tmp) {
        ind--;
        l++;
    }
    l++;
    int tot = 1000000000;
    tot -= (ind + 1);
    tot %= l;
    tmp = v[ind + tot];
    ind = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            g[i][j] = tmp[ind++];
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'O') {
                ans += (n - i);
            }
        }
    }
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
