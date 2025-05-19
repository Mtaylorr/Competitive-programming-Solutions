// Mtaylor
#pragma GCC optimize("O3")
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

// SRC : https://github.com/likecs/Competitive-Coding/blob/master/C%2B%2B14/Polynomials/FFTMOD.cpp

// General Modulo FFT implementation
// Quite fast as it uses just 4 FFT calls
// Just call preCompute() in main() before usage

const int MAX = 12 * (1e5 + 5);  // Size of Polynomial
const int MOD = 1e9 + 7;

namespace FFTMOD {
const double PI = acos(-1);
const int LIM = 1 << 22;  // 2 * 2^ceil(log2(POLY_SIZE))

// Complex class: Quite faster than in-built C++ library as it uses only functions required
template <typename T>
class cmplx {
   private:
    T x, y;

   public:
    cmplx() : x(0.0), y(0.0) {}
    cmplx(T a) : x(a), y(0.0) {}
    cmplx(T a, T b) : x(a), y(b) {}
    T get_real() { return this->x; }
    T get_img() { return this->y; }
    cmplx conj() { return cmplx(this->x, -(this->y)); }
    cmplx operator=(const cmplx& a) {
        this->x = a.x;
        this->y = a.y;
        return *this;
    }
    cmplx operator+(const cmplx& b) { return cmplx(this->x + b.x, this->y + b.y); }
    cmplx operator-(const cmplx& b) { return cmplx(this->x - b.x, this->y - b.y); }
    cmplx operator*(const T& num) { return cmplx(this->x * num, this->y * num); }
    cmplx operator/(const T& num) { return cmplx(this->x / num, this->y / num); }
    cmplx operator*(const cmplx& b) { return cmplx(this->x * b.x - this->y * b.y, this->y * b.x + this->x * b.y); }
    cmplx operator/(const cmplx& b) {
        cmplx temp(b.x, -b.y);
        cmplx n = (*this) * temp;
        return n / (b.x * b.x + b.y * b.y);
    }
};

typedef cmplx<double> COMPLEX;  // change this to long double in case of error

COMPLEX W[LIM], invW[LIM];

void preCompute() {
    for (int i = 0; i < LIM / 2; ++i) {
        // change this to long double in case of error
        double ang = 2 * PI * i / LIM;
        double _cos = cos(ang), _sin = sin(ang);
        W[i] = COMPLEX(_cos, _sin);
        invW[i] = COMPLEX(_cos, -_sin);
    }
}

void FFT(COMPLEX* a, int n, bool invert = false) {
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        for (int i = 0; i < n; i += len) {
            int ind = 0, add = LIM / len;
            for (int j = 0; j < len / 2; ++j) {
                COMPLEX u = a[i + j];
                COMPLEX v = a[i + j + len / 2] * (invert ? invW[ind] : W[ind]);
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                ind += add;
            }
        }
    }
    if (invert)
        for (int i = 0; i < n; ++i) a[i] = a[i] / n;
}

COMPLEX f[LIM], g[LIM], ff[LIM], gg[LIM];

// c[k] = sum_{i=0}^k a[i] b[k-i] % MOD
void multiply(vector<int>& C, vector<int>& A, vector<int>& B, int mxsize) {
    int n1 = A.size(), n2 = B.size();
    int final_size = n1 + n2 - 1, N = 1;
    while (N < final_size) N <<= 1;

    int SQRTMOD = (int)sqrt(MOD) + 10;
    for (int i = 0; i < N; ++i) f[i] = COMPLEX(), g[i] = COMPLEX();
    for (int i = 0; i < n1; ++i) f[i] = COMPLEX(A[i] % SQRTMOD, A[i] / SQRTMOD);
    for (int i = 0; i < n2; ++i) g[i] = COMPLEX(B[i] % SQRTMOD, B[i] / SQRTMOD);
    FFT(f, N), FFT(g, N);
    COMPLEX X, Y, a1, a2, b1, b2;
    for (int i = 0; i < N; ++i) {
        X = f[i], Y = f[(N - i) % N].conj();
        a1 = (X + Y) * COMPLEX(0.5, 0);
        a2 = (X - Y) * COMPLEX(0, -0.5);
        X = g[i], Y = g[(N - i) % N].conj();
        b1 = (X + Y) * COMPLEX(0.5, 0);
        b2 = (X - Y) * COMPLEX(0, -0.5);
        ff[i] = a1 * b1 + a2 * b2 * COMPLEX(0, 1);
        gg[i] = a1 * b2 + a2 * b1;
    }
    FFT(ff, N, 1), FFT(gg, N, 1);
    final_size = min(final_size, mxsize);
    C.assign(final_size, 0);
    for (int i = 0; i < final_size; ++i) {
        long long x = (ll)(ff[i].get_real() + 0.5);
        long long y = (ll)(ff[i].get_img() + 0.5) % MOD;
        long long z = (ll)(gg[i].get_real() + 0.5);
        C[i] = (x + (y * SQRTMOD + z) % MOD * SQRTMOD) % MOD;
    }
}

int solve(vector<int>& v, int n, int x) {
    vector<int> cur = v;
    vector<int> ans = {1};
    int mxsize = x + 1;
    while (n) {
        if (n % 2) {
            multiply(ans, ans, cur, mxsize);
        }

        n /= 2;
        if (n == 0) break;
        multiply(cur, cur, cur, mxsize);
    }
    return ans[x];
}
};  // namespace FFTMOD
using namespace FFTMOD;

template <typename T, typename U>
int mul(T u, U v, int mod = MOD) {
    return ((u % mod) * 1ll * (v % mod)) % mod;
}
template <typename T, typename U>
int add(T u, U v, int mod = MOD) {
    return ((u % mod) + 0ll + (v % mod) + mod) % mod;
}
template <typename T, typename U>
int sub(T u, U v, int mod = MOD) {
    return ((u % mod) + 0ll - (v % mod) + mod) % mod;
}
template <typename T>
int powe(T u, ll v, int mod = MOD) {
    int ans = 1;
    int acc = u % mod;
    while (v) {
        if (v % 2) ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}
template <typename T>
int inv(T u, int mod = MOD) {
    return powe(u, mod - 2, mod);
}

int p[N];
int n, x;

void test_case() {
    cin >> n >> x;
    int inv100 = inv(100);
    vector<int> v;
    for (int i = 0; i < 13; i++) {
        cin >> p[i];
        p[i] = (p[i] * 1ll * inv100) % MOD;
        v.push_back(p[i]);
    }
    cout << FFTMOD::solve(v, n, x) << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    preCompute();
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
