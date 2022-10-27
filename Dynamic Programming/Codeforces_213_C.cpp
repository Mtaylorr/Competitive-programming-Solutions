//https://codeforces.com/contest/213/problem/C
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
const int N = 3e2 + 5;

int A[N][N];
vector<pair<int, int> > pts[2*N];
int dp[2][2 * N][2 * N];
int pos[N][N];
int n;
int dx[] = {0, -1};
int dy[] = {-1, 0};

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
            pos[i][j] = pts[i + j].size();
            pts[i + j].pb({i, j});
        }
    }
    dp[0][0][0] = A[0][0];
    for (int i = 1; i <= n + n - 2; i++) {
        int id = i&1;
        for(int j=0;j<pts[i].size();j++){
            for(int k=0;k<pts[i].size();k++){
                dp[id][j][k]=-1e9;
            }
        }
        for (int j = 0; j < pts[i].size(); j++) {
            int a = pts[i][j].fi;
            int b = pts[i][j].se;
            for (int k = j; k < pts[i].size(); k++) {
                int c = pts[i][k].fi;
                int d = pts[i][k].se;
                for (int o = 0; o < 2; o++) {
                    int na = a + dx[o];
                    int nb = b + dy[o];
                    if (na < 0 || nb < 0) continue;
                    for (int f = 0; f < 2; f++) {
                        int nc = c + dx[f];
                        int nd = d + dy[f];
                        if (nc < 0 || nd < 0) continue;
                        if(pos[na][nb]<=pos[nc][nd]){
                            int sm = dp[id^1][pos[na][nb]][pos[nc][nd]];
                            if(j==k){
                                sm+=A[a][b];
                            }else{
                                sm+=A[a][b]+A[c][d];
                            }
                            dp[id][j][k]=max(sm, dp[id][j][k]);
                        }
                        
                    }
                }
            }
        }
    }
    cout << dp[(n + n - 2) % 2][0][0];
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >>T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
