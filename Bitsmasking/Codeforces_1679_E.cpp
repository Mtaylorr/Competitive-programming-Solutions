//https://codeforces.com/problemset/problem/1679/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 998244353;


void mul(int &u, int v, ll mod = MOD) {
    u = ((u % mod) * 1ll * (v % mod)) % mod;
}

void add(int &u, int v, int mod = MOD) {
    u = ((u % mod) + 0ll + (v % mod) + mod) % mod;
}

ll sub(ll u, ll v, ll mod = MOD) {
    return ((u % mod) - (v % mod) + mod) % mod;
}

int powe(ll u, ll v, ll mod = MOD) {
    int ans = 1;
    int acc = u;
    while (v) {
        if (v % 2) {
            mul(ans, acc, mod);
        }
        mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}

int a[(1 << 17) + 5][20];
int n, q;
char s[N];
int F[(1 << 17) + 5][20];
int t;

int po[20][1005];


int main() {
    //freopen("input.txt", "r", stdin);
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    //cout.tie(0);
    scanf("%d", &n);
    scanf("%s", s);
    for (int i = 0; i <= 17; i++) {
        for (int j = 0; j <= 1000; j++) {
            po[i][j] = powe(i, j);
        }
    }
    int all = 0;
    for (int i = 0; i < n; i++) {
        all += (s[i] == '?');
    }
    for (int i = 0; i < n; i++) {
        int nb = 0;
        int msk = 0;
        for (int j = 0; j < n; j++) {
            if (i - j < 0 || i + j >= n)
                break;
            if (s[i + j] == '?' && s[i - j] == '?') {
                if (i + j != i - j)
                    nb++;
            } else if (s[i + j] == '?' || s[i - j] == '?') {
                nb++;
                if (s[i + j] != '?') {
                    msk |= (1 << (s[i + j] - 'a'));
                } else {
                    msk |= (1 << (s[i - j] - 'a'));
                }
            } else if (s[i + j] != s[i - j]) {
                break;
            }
            for (int j = 0; j <= 17; j++) {
                add(a[msk][j], po[j][all - nb]);

            }
        }

        msk = 0;
        nb = 0;

        for (int j = 0; j < n; j++) {
            if (i - j - 1 < 0 || i + j >= n)
                break;
            if (s[i + j] == '?' && s[i - j - 1] == '?') {
                if (i + j != i - j - 1)
                    nb++;
            } else if (s[i + j] == '?' || s[i - j - 1] == '?') {
                nb++;
                if (s[i + j] != '?') {
                    msk |= (1 << (s[i + j] - 'a'));
                } else {
                    msk |= (1 << (s[i - j - 1] - 'a'));
                }
            } else if (s[i + j] != s[i - j - 1]) {
                break;
            }
            for (int j = 0; j <= 17; j++) {

                add(a[msk][j], po[j][all - nb]);
            }
        }

    }
    for (int j = 0; j <= 17; j++) {
        for (int i = 0; i < (1 << 17); ++i) {
            F[i][j] = a[i][j];
        }
    }
    for (int i = 0; i < 17; ++i)
        for (int mask = 0; mask < (1 << 17); ++mask) {
            if (mask & (1 << i)) {
                for (int j = 0; j <= 17; j++)
                    add(F[mask][j], F[mask ^ (1 << i)][j]);
            }

        }

    cin >> q;
    while (q--) {
        scanf("%s", s);
        int msk = 0;
        int l = strlen(s);
        for (int i = 0; i < l; i++) {
            msk += (1 << (s[i] - 'a'));
        }
        printf("%d\n", F[msk][l]);
    }
    return 0;

}
