//https://csacademy.com/ieeextreme-practice/task/ed8629419f140a5a2c923b049aba1224/

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e3+5;

int dp[2][505];
int w[205], f[205];
int t,n,c;

int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        memset(dp, 0,sizeof(dp));
        scanf("%d%d",&c,&n);
        for(int i=0;i<n;i++){
            scanf("%d%d",&w[i],&f[i]);
        }
        for(int i=1;i<=n;i++){
            int id = i&1;
            for(int j=0;j<=c;j++){
                dp[id][j]=dp[id^1][j];
                if(j>=w[i-1]){
                    dp[id][j]=max(dp[id][j], f[i-1]+dp[id^1][j-w[i-1]]);
                }
            }
        }
        printf("%d\n", dp[n&1][c]);
    }
    return 0;
}
