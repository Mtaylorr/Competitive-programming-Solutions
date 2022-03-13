//https://codeforces.com/problemset/problem/383/D
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 1e9 +7 ;

int n;
int dp[2][10005];
int a[N];

ll add(ll u, ll v, ll mod=MOD){
	return ((u%mod)+(v%mod)+mod)%mod;
}

int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int mx = 10000;
    dp[0][5000]=1;
    ll ans=0;
    for(int i=1;i<=n;i++){
        int p = i&1;
        for(int j=0;j<=mx;j++){
            dp[p][j]=0;
        }
        for(int j=0;j<=mx;j++){
            if(j-a[i]>=0){
                dp[p][j]=add(dp[p][j],dp[1-p][j-a[i]]);
            }
            if(j+a[i]<=mx){
                dp[p][j]=add(dp[p][j],dp[1-p][j+a[i]]);
            }
        }
        ans=add(ans, dp[p][5000]);
        dp[p][5000]=add(dp[p][5000],1);
    }
    cout << ans << endl;
    return 0;

}
