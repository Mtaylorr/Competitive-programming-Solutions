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

int x[N], y[N];
int n;
bool vis[N];
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        if (x[i] == 90 || x[i] == 90) {
            cout << "yes\n";
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        int l = i;
        int r = (l + 1) % n;
        int sty = y[l];
        int eny = y[r];
        if (sty < 0) {
            sty = 360 + sty;
        }
        if (eny < 0) {
            eny = 360 + eny;
        }
        int direct = abs(sty - eny);
        if (direct == 180) {
            cout << "yes\n";
            return;
        }
        int undirect = 360 - abs(sty - eny);
        if (sty > eny)
            swap(sty, eny);
        //dbg(sty, eny, direct, undirect);
        if (direct < undirect) {
            //dbg("direct");
            for (int i = 2 * sty; i <= 2 * eny; i++) {
                vis[i] = 1;
            }
        } else {
            //dbg("undiredct");
            for (int i = 2 * eny; i < 2 * 360; i++) {
                vis[i] = 1;
            }
            for (int i = 2 * 0; i <= 2 * sty; i++) {
                vis[i] = 1;
            }
        }
    }

    for (int i = 0; i < 2 * 360; i++) {
        // dbg(i,vis[i]);
        if (!vis[i]) {
            cout << "no ";
            int p = i;
            if (p >= 360) {
                p = p - 2 * 360;
            }
            double x = p;
            cout << fixed << setprecision(1) << x/2 << endl;
            return;
        }
    }
    cout << "yes ";
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
