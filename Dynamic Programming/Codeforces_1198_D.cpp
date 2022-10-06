//https://codeforces.com/contest/1198/problem/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

int n;
int dp[51][51][51][51];
char grid[51][51];
int s[51][51];

int get_rec_sum(int a, int b, int c, int d) {
    return s[b][d] + s[a - 1][c - 1] - s[b][c - 1] - s[a - 1][d];
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            s[i][j] = (grid[i - 1][j - 1] == '#') + s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1];
        }
    }
    for (int dx = 1; dx <= n; dx++) {
        for (int dy = 1; dy <= n; dy++) {
            for (int a = 1; a + dx - 1 <= n; a++) {
                for (int b = 1; b + dy - 1 <= n; b++) {
                    int c = a + dx - 1;
                    int d = b + dy - 1;
                    dp[a][b][c][d] = max(dx, dy);

                    for (int j = a; j <= c; j++) {
                        int sm = get_rec_sum(j, j, b, d);
                        if (sm == 0) {

                            int lef = 0;
                            int rig = 0;
                            if(j>a){
                                rig = dp[a][b][j-1][d];
                            }
                            if(j<c){
                                lef = dp[j+1][b][c][d];
                            }
                            dp[a][b][c][d]=min(dp[a][b][c][d], rig+lef);
                        }
                    }
                    for (int j = b; j <= d; j++) {
                        int sm = get_rec_sum(a, c, j, j);
                        if (sm == 0) {
                            int lef = 0;
                            int rig = 0;
                            if(j>b){
                                rig = dp[a][b][c][j-1];
                            }
                            if(j<d){
                                lef = dp[a][j+1][c][d];
                            }
                            dp[a][b][c][d]=min(dp[a][b][c][d], rig+lef);
                        }
                    }
                    //cout << a << " " << c << " " << b << " " << d << " " << dp[a][b][c][d] << endl;
                }
            }
        }
    }
    cout << dp[1][1][n][n] << endl;


    return 0;

}
