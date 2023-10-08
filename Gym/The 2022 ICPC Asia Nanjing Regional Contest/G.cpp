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

int n, a[N];
int aft[N];
bool ok[N];

void test_case() {
    cin >> n;
    int ans = 1;
    int nb = 1;
    int nb0 = 0;
    for (int i = 0; i < n; i++) {
        ok[i] = 0;
        cin >> a[i];
    }
    vector<int> tmp[2];
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) {
            nb++;
            ans++;
            tmp[0].pb(i);
        } else if (a[i] == -1) {
            if (nb >= 2) {
                nb--;
                tmp[0].pop_back();
            } else if (nb0) {
                nb0--;
                ans++;
                tmp[1].pop_back();
            } else {
                cout << "-1" << endl;
                return;
            }
        } else {
            tmp[1].push_back(i);
            nb0++;
        }
    }

    while (tmp[0].size()) {
        if (tmp[1].size() && tmp[1].back() >= tmp[0].back()) {
            tmp[1].pop_back();
            nb--;
        }
        tmp[0].pop_back();
    }
    int rem = tmp[1].size();
    ans += (rem + 1) / 2;
    nb += (rem % 2);
    int d = __gcd(ans, nb);
    cout << (ans/d) << " " << nb/d << endl;
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
