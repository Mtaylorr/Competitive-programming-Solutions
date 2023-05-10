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

const int P = 1e7 + 5;
class NumberTheory {
   public:
    bitset<P> is_prime;
    vector<int> primes;
    vector<int> mob;
    int GPF[P];
    int index[P];
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
    template <typename T>
    bool issquare(T w) {
        T sq = round(sqrt(w));
        return sq * sq == w;
    }
    void sieve(int ub) {
        sieve_size = ub;
        primes.clear();
        is_prime.set();
        is_prime[0] = is_prime[1] = 0;
        int nb = 0;
        for (int i = 2; i <= ub; i++) {
            if (is_prime[i] == 0) continue;
            ++nb;
            nb %= 2;
            index[i] = nb;
            GPF[i] = i;
            for (int j = i * 2; j <= ub; j += i) {
                is_prime[j] = 0;
                GPF[j] = i;
            }
        }
    }

} nt;
int n, d;
int a[N];

void test_case() {
    nt.sieve(1e7);
    cin >> n >> d;
    ll x = 0;
    ll y = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < d; i++) {
        int p = i % n;
        if (a[p] > 1) {
            int index = nt.index[nt.GPF[a[p]]];
            if (index) {
                x += a[p];
            } else {
                y += a[p];
            }
            a[p] /= nt.GPF[a[p]];
        }
        if (x >= y) {
            cout << "R\n";
        } else {
            cout << "B\n";
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
