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
typedef long long ull;
const int N = 3e5 + 5;

const int P = 1e5 + 5;
class NumberTheory {
   public:
    bitset<P> is_prime;
    vector<int> primes;
    vector<int> mob;
    int sieve_size;

    NumberTheory() { sieve_size = 0; }
    template <typename T>
    T gcd(T a, T b) {
        return (b == 0 ? a : gcd(b, a % b));
    }
    template <typename T>
    T lcm(T a, T b) {
        return a * (b / gcd(a, b));
    }

} nt;

pair<ull, ull> dp[50][50][50][50];
bool vis[50][50][50][50];
int n, m, p;
pair<ull, ull> mrg(pair<ull, ull> x, pair<ull, ull> y) {
    ull l = nt.lcm(x.se,y.se);
    ull a = x.fi * (l / x.se);
    ull b = y.fi * (l / y.se);
    // dbg(a, b, l, x.fi, x.se);
    a += b;
    ull d = nt.gcd(a, l);
    a /= d;
    l /= d;
    return {a, l};
}
pair<ull, ull> mul(pair<ull, ull> x, pair<ull, ull> y) {
    ull a = x.fi * y.fi;
    ull b = x.se * y.se;
    ull d = nt.gcd(a, b);
    //dbg(x.fi, y.fi, x.se, y.se);
    a /= d;
    b /= d;
    return {a, b};
}

pair<ull, ull> solve(int x, int y, int r, int oth) {
    if (r == 0) {
        if (x == 0) {
            return {1, 1};
        } else {
            return {0, 1};
        }
    }
    if (x == 0) {
        return {0, 1};
    }
    if (vis[x][y][r][oth]) return dp[x][y][r][oth];
    vis[x][y][r][oth] = 1;
    pair<ull, ull> ans = {0, 1};
    ll rem = oth + 2 * x + y;
    ans = mrg(ans, mul({2 * x, rem}, solve(x - 1, y + 1, r - 1, oth)));
    if (y) ans = mrg(ans, mul({y, rem}, solve(x, y - 1, r - 1, oth)));
    if (oth) ans = mrg(ans, mul({oth, rem}, solve(x, y, r - 1, oth - 1)));

    return dp[x][y][r][oth] = ans;
}

void test_case() {
    cin >> m >> n >> p;
    pair<ull, ull> ans = solve(n, 0, p, m - 2 * n);
    cout << ans.fi << "/" << ans.se << endl;
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
