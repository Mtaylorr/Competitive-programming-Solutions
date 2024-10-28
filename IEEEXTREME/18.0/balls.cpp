//https://csacademy.com/ieeextreme18/task/balls/
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

int k, e[N];

ll bruteFoce(ll n) {
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        bool cond = false;
        for (int j = 0; j < k; j++) {
            if (i % e[j] == 0) {
                cond = true;
            }
        }
        // for (int j = 0; j < k; j++) {
        //     if (e[j] == i) cond = true;
        // }
        ans += cond;
    }
    return ans;
}

const int P = 1e7 + 5;
ll phidp[P];
ll phidpsum[P];
struct CountPrimesN2_3 {
    // https://codeforces.com/blog/entry/91632
    // phi(n,a) {1...n} not divisible by first a primes
    // phi(n,a) = phi(n,a-1) - phi((n/Pa),a-1)
    // pi(n) = phi(n, pi(y)) + pi(y) - F - 1;
    vector<int> ms;
    ll y, ans;
    vector<pair<pair<ll, int>, int> > queries;
    ll run(ll n) {
        y = pow(n, 0.5);
        if (n < 100) {
            y = n;
        }
        for (int j = 1; j <= y; j++) {
            phidp[j] = 1;
            phidpsum[j] = j;
        }
        ll s = n / y;
        ans = 0;
        phi(n, k - 1);
        sort(all(queries));
        int ind = -1;
        for (auto &u : queries) {
            ll a = u.fi.fi;
            ll n = u.fi.se;
            int sign = u.se;
            while (ind < a) {
                ind++;
                for (int j = e[ind]; j <= y; j += e[ind]) {
                    phidp[j] = 0;
                }
                for (int j = 1; j <= y; j++) {
                    phidpsum[j] = phidpsum[j - 1] + phidp[j];
                }
            }
            ans += (phidpsum[n]) * sign;
        }
        queries.clear();
        return ans;
    }

    void phi(ll n, int a, int sign = 1) {
        if (n == 0) return;
        if (a == -1) {
            ans += n * sign;
            return;
        }
        if (n <= y) {
            queries.emplace_back(make_pair(a, n), sign);
            return;
        }
        phi(n, a - 1, sign);
        phi(n / e[a], a - 1, -sign);
    }
} cp;

ll n;

void test_case() {
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        cin >> e[i];
    }
    sort(e, e + k);
    if (e[0] == 1) {
        cout << n << endl;
        return;
    }
    cout << n - cp.run(n);
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
