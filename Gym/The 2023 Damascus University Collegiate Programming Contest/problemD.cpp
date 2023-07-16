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
const int P = 3e5 + 5;
class NumberTheory {
   public:
    bitset<P> is_prime;
    vector<int> primes;
    vector<int> mob;
    int sieve_size;
    NumberTheory() { sieve_size = 0; }
    void mobius_sieve(int ub) {
        sieve_size = ub;
        is_prime.set();
        is_prime[0] = is_prime[1] = 0;
        mob.assign(ub + 1, 1);
        for (int i = 2; i <= ub; i++) {
            if (is_prime[i] == 0) continue;
            primes.pb(i);
            mob[i] = -1;
            for (int j = 2 * i; j <= ub; j += i) {
                is_prime[j] = 0;
                mob[j] *= -1;
                if ((j / i) % i == 0) mob[j] = 0;
            }
        }
    }

} nt;

int n, m;
int ex[N];
void test_case() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        ex[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        for (int j = 2; j * j <= x; j++) {
            if (x % j == 0) {
                if (j <= m) {
                    ex[j] = 1;
                }
                while (x % j == 0) {
                    x /= j;
                }
            }
        }
        if (x >= 2 && x <= m) {
            ex[x] = 1;
        };
    }
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        bool rs = 1;
        int x = i;
        for (int j = 2; j * j <= x; j++) {
            if (x % j == 0) {
                if (ex[j]) {
                    rs = 0;
                    break;
                }
                while (x % j == 0) x /= j;
            }
        }
        if (x > 1 && ex[x]) {
            rs = 0;
        }
        ans += (rs);
    }
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    nt.mobius_sieve(200000);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
