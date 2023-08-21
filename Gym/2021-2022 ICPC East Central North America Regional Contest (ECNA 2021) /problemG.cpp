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

string x[3];
string tmp[3];
char c, p;

bool valid() {
    double a = stod(tmp[0]);
    double b = stod(tmp[1]);
    double d = stod(tmp[2]);
    if (c == '+') {
        return fabs(a + b - d) <= 1e-6;
    } else if (c == '*') {
        return fabs(a * b - d) <= 1e-6;
    }
    return 0;
}

void test_case() {
    cin >> x[0] >> c >> x[1] >> p >> x[2];
    vector<pair<int, int> > v = {{0, 1}, {0, 2}, {1, 2}};
    for (int l = 0; l < 3; l++) {
        for (int r = l + 1; r < 3; r++) {
            for (int i = 1; i <= x[l].size() - 1; i++) {
                for (int j = 1; j <= x[r].size() - 1; j++) {
                    string lpref = x[l].substr(0, i);
                    string lrem = x[l].substr(i);
                    string rpref = x[r].substr(0, j);
                    string rrem = x[r].substr(j);
                    tmp[l] = rpref + lrem;
                    tmp[r] = lpref + rrem;
                    tmp[3 - l - r] = x[3 - l - r];
                    if (valid()) {
                        cout << tmp[0] << " " << c << " " << tmp[1] << " "
                             << "="
                             << " " << tmp[2] << endl;
                    }
                }
            }
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
