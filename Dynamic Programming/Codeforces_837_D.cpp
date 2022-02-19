//https://codeforces.com/contest/837/problem/D

#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7 ;

int n,k;
ll a[N];
int five[N], two[N];
int dp[2][205][205*27];

int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        while(a[i]%2==0){
            two[i]++;
            a[i]/=2;
        }
        while(a[i]%5==0){
            five[i]++;
            a[i]/=5;
        }
    }

    int ub = 27*n;
    for(int j=0;j<=k;j++){
        for(int i=1;i<=ub;i++){
            dp[0][j][i]=-1e7;
        }
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        int p = i&1;
        for(int o=0;o<=k;o++){
            for(int j=0;j<=ub;j++){
                dp[p][o][j]=dp[p^1][o][j];
                if(j>=five[i] && o>=1){
                    dp[p][o][j]=max(dp[p][o][j],two[i]+dp[p^1][o-1][j-five[i]]);
                }
                ans=max(ans, min(dp[p][o][j],j));
             }
        }

    }
    cout << ans << endl;
    return 0;
}
