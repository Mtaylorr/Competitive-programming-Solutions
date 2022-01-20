//https://www.codechef.com/problems/XORSUB
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e6 +5 ;
const int MOD = 998244353 ;

int t;
int a[N],n, k;
int dp[2][1050];

int main(){
    //freopen("input.txt", "r",stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        memset(dp[0],0, sizeof(dp[0]));
        memset(dp[1],0, sizeof(dp[1]));
        int ans = 0;
        dp[0][0]=1;
        for(int i=1;i<=n;i++){
            int p = i&1;
            for(int j=0;j<1024;j++){
                if(dp[p^1][j]){
                    dp[p][j]=1;
                    dp[p][j^a[i]]=1;
                }
            }
        }
        for(int i=0;i<1024;i++){
            if(dp[n&1][i])
                ans=max(ans, k^i);
        }
        cout << ans << endl;

    }
    return 0;
}
