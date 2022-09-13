//https://codeforces.com/problemset/problem/1680/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, E = 1 << 17;
const int MOD = 1e9 + 7;

int sum[N];
int n;
char grid[2][N];
int dp[2][N];
int t;
int l,r;

int solve(int i, int j){
    if(j>=r){
        return 0;
    }
    if(dp[i][j]!=-1){
        return dp[i][j];
    }
    int ans=1e9;
    if(sum[j+1]==2){
        ans=min(ans, 2+solve(0,j+1));
        ans=min(ans, 2+solve(1,j+1));
    }else{

        int x = grid[i][j+1]=='*';
        int y = grid[1-i][j+1]=='*';
        ans=min(ans, 1+solve(i,j+1)+(y==1));
        ans=min(ans, 2+solve(1-i,j+1));
    }
    return dp[i][j]=ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n;
        for(int i=0;i<n;i++){
            sum[i]=0;
            dp[0][i]=dp[1][i]=-1;
        }
        l=-1;
        for(int i=0;i<2;i++){
            cin >> grid[i];
            for(int j=0;j<n;j++){
                sum[j]+=grid[i][j]=='*';
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<2;j++){
                if(grid[j][i]=='*'){
                    r=i;
                    if(l==-1){
                        l=i;
                    }
                }
            }
        }
        int ans=1e9;
        if(sum[l]==2){
            ans=min(ans, 1+solve(0,l));
            ans=min(ans, 1+solve(1,l));
        }else{
            if(grid[0][l]=='*'){
                ans=min(ans, solve(0,l));

                ans=min(ans, 1+solve(1,l));
            }else{
                ans=min(ans, 1+solve(0,l));
                ans=min(ans, solve(1,l));
            }
        }
        cout << ans << endl;
    }

    return 0;


}
