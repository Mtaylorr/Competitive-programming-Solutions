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
double d[N];
int t;
int nb = 0;
double toff[N];
int num[N], t1[N], t2[N];

void showans() {
    cout << nb - 1 << endl;
    for (int i = 1; i < nb; i++) {
        cout << fixed << setprecision(10) << toff[i] << " " << num[i] << " " << t1[i] << " " << t2[i] << endl;
    }
}

void dfs(int mask, double ct) {
    if (abs(ct - t) <= 1e-10) {
        showans();
        exit(0);
    }
    if (ct > t) return;
    if (mask == (1 << n) - 1) return;
    for (int i = 0; i < n; i++) {
        if ((1 << i) & mask) continue;
        for (int j = 0; j < nb; j++) {
            double nct = toff[j] + d[i];
            if (nct > ct) {
                toff[nb] = nct;
                num[nb] = i + 1;
                t1[nb] = j;
                t2[nb] = -1;
                nb++;
                dfs(mask + (1 << i), nct);
                nb--;
            }
            for (int k = j; k < nb; k++) {
                double rem = d[i] - (toff[k] - toff[j]);
                if (rem <= 0) continue;
                rem /= 2;
                double nct = toff[k] + rem;
                if (nct > ct) {
                    toff[nb] = nct;
                    num[nb] = i + 1;
                    t1[nb] = j;
                    t2[nb] = k;
                    nb++;
                    dfs(mask + (1 << i), nct);
                    nb--;
                }
            }
        }
    }
}
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    cin >> t;
    nb = 1;
    dfs(0, 0);
    cout << -1 << endl;
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
