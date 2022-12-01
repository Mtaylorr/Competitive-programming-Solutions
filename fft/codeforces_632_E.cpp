//https://codeforces.com/contest/632/problem/E
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

using cd = complex<double>;
const double PI = acos(-1);

const int M = (1 << 20) + 3, LOGM = 20;
int po[LOGM + 2];
void init_fft() {
    for (int i = 0; i < LOGM + 2; i++) {
        po[i] = 1 << i;
    }
}

int reverse(int x, int logn) {
    int ans = 0;
    for(int i=0;i<logn;i++) if (x & po[i]) ans |= po[logn-1-i];
    return ans;
}

void fft(cd a[M], int n, bool invert) {
    static cd vv[LOGM][M];
    static bool prepared = false;
    if (!prepared) {
        prepared = true;
        for (int i = 0; i < LOGM; i++) {
            double ang = 2 * PI / (1 << (i + 1));
            for (int j = 0; j < po[i]; j++)
                vv[i][j] = cd(cos(ang * j), sin(ang * j));
        }
    }
    int logn = 0;
    while (po[logn] < n) logn++;
    for (int i = 1, j = 0; i < n; i++) {
        int ni = reverse(i, logn);
        if (i < ni) swap(a[i], a[ni]);
    }
    for (int i = 0; po[i] < n; i++)
        for (int j = 0; j < n; j += po[i + 1])
            for (int k = j; k < j + po[i]; k++) {
                cd cur = invert ? conj(vv[i][k - j]) : vv[i][k - j];
                cd l = a[k], r = cur * a[k + po[i]];
                a[k] = l + r;
                a[k + po[i]] = l - r;
            }
    if (invert)
        for (int i = 0; i < n; i++) a[i] /= double(n);
}

void mul(int result[M], int a[M], int b[M]) {
    static cd fp[M], p1[M], p2[M];
    int n = po[LOGM], m = po[LOGM];
    while (n && !a[n - 1]) n--;
    while (m && !b[m - 1]) m--;
    int cnt = n + m;
    while (cnt & (cnt - 1)) cnt++;
    if (cnt > po[LOGM]) return;

    for (int i = 0; i < cnt; i++) fp[i] = cd(a[i], b[i]);
    fft(fp, cnt, false);
    for (int i = 0; i < cnt; i++) {
        p1[i] = (fp[i] + conj(fp[(cnt - i) % cnt])) / cd(2, 0);
        p2[i] = (fp[i] - conj(fp[(cnt - i) % cnt])) / cd(0, 2);
    }
    for (int i = 0; i < cnt; i++) fp[i] = p1[i] * p2[i];
    fft(fp, cnt, true);

    for (int i = 0; i < cnt; i++) result[i] = int(fp[i].real() + 0.5);
}

void mul(int* a, int* b) {
    for (int i = 0; i <po[LOGM];i++) {
        a[i] = !!a[i];
        b[i] = !!b[i];
    }
    mul(a, b, a);
}

void binPow(int* a, int b) {
    static int ans[M];
    for (int i = 0; i < po[LOGM]; i++) ans[i] = !i;

    while (b) {
        if (b & 1) mul(ans, a);
        mul(a, a);
        b >>= 1;
    }

    for (int i = 0; i < po[LOGM]; i++) a[i] = ans[i];
}

int n, k, a[N];
int poly[M];

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        poly[a[i]] = 1;
    }

    binPow(poly,k);
    for (int i = 0; i <po[LOGM]; i++) {
        if (poly[i]) {
            cout << i << " ";
        }
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >>T;
    T = 1;
    init_fft();
    while (T--) {
        solve();
    }
    return 0;
}
