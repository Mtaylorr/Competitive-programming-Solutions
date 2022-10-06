//https://codeforces.com/problemset/problem/372/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 8e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

int s[41][41];

int dp[41][41][41][41];
int n,m,q;
char grid[41][41];
int get_rec_sum(int a, int b, int c, int d){
    return s[b][d]+s[a-1][c-1] -s[b][c-1] - s[a-1][d];
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> q;
    for(int i=0;i<n;i++) {
        cin >> grid[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            s[i][j]=(grid[i-1][j-1]-'0') + s[i-1][j]+s[i][j-1] - s[i-1][j-1];
        }

    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int dx=0;dx<=i-1;dx++){
                for(int dy=0;dy<=j-1;dy++){
                    int sm = get_rec_sum(i-dx, i, j-dy, j);

                    dp[i][j][dx][dy]=0;
                    if(dx>=1){
                        dp[i][j][dx][dy]+=dp[i][j][dx-1][dy];
                    }
                    if(dy>=1){
                        dp[i][j][dx][dy]+=dp[i][j][dx][dy-1];
                    }
                    if(dy>=1 && dx>=1){
                        dp[i][j][dx][dy]-=dp[i][j][dx-1][dy-1];
                    }
                    if(sm==0){
                        dp[i][j][dx][dy]++;
                    }
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int dx=0;dx<=i-1;dx++){
                for(int dy=0;dy<=j-1;dy++){
                    if(dx>=1){
                        dp[i][j][dx][dy]+=dp[i-1][j][dx-1][dy];
                    }
                    if(dy>=1){
                        dp[i][j][dx][dy]+=dp[i][j-1][dx][dy-1];
                    }
                    if(dy>=1 && dx>=1){
                        dp[i][j][dx][dy]-=dp[i-1][j-1][dx-1][dy-1];
                    }
                }
            }
        }
    }
    int a,b,c,d;
    while(q--){
        cin >> a >> b >> c >> d;
        cout << dp[c][d][c-a][d-b] << "\n";
    }

    return 0;

}
