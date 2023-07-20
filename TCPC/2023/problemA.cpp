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

int n;
string s;
vector<int> fibs;
int z[N];

void build_z() {
    int l = 1, r = 1;
    z[0] = 0;
    for (int i = 1; i < n; i++) {
        if (i + z[i - l] < r) {
            z[i] = z[i - l];
        } else {
            l = i;
            r = max(r, i);
            while (r < n && s[r] == s[r - l]) {
                r++;
            }
            z[i] = r - i;
        }
    }
}
void preprocess() {
    int x0 = 1;
    int x1 = 1;
    while (x0 + x1 <= 5e5) {
        fibs.pb(x0 + x1);
        int tmp = x0 + x1;
        x0 = x1;
        x1 = tmp;
    }
}

void test_case() {
    cin >> n;
    cin >> s;
    reverse(all(s));
    build_z();
    int ans = 1e9;
    for (auto &p : fibs) {
        if (p > n) continue;
        if (n % p) continue;
        int l = n / p;
        int xl0 = l;
        int xl1 = l;
        int tmp;
        bool valid = 1;
        while (2*xl1 + xl0 <= n) {
            if (z[xl0 + xl1] < xl1) {
                valid = 0;
                break;
            }
            tmp = xl0 + xl1;
            xl0 = xl1;
            xl1 = tmp;
        }
        if (valid && ans > l) {
            ans = l;
        }
    }
    if (ans < 1e9) {
        string s0 = s.substr(ans, ans);
        string s1 = s.substr(0, ans);
        reverse(all(s0));
        reverse(all(s1));
        cout << ans << "\n" << s0 << "\n" << s1 << "\n";
    } else {
        cout << -1 << endl;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    preprocess();
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
