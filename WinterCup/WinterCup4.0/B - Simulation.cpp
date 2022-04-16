#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353  ;

int n,m,k;
double K[305][305];

double calc(int n, int p){
    if(p==0){
        return 1.0;
    }
    if(K[n][p]>=0)
        return K[n][p];
    return K[n][p] = calc(n-1,p-1)/(p*1.0);
}

double dp[305][305];

double solve(int i=0, int rem=m){
    if(i>=n){
        if(rem)
            return 0;
        return 1;
    }
    if(dp[i][rem]>=0){
        return dp[i][rem];
    }
    dp[i][rem]=0;
    double cur= 1 ;
    for(int j=0;j<=min(rem,k-1);j++){

        dp[i][rem]+=cur*solve(i+1,rem-j);
        cur = (cur*(rem-j)/((j+1)*1.0))/((n)*1.0);
    }
    return dp[i][rem];
}

int main(){
    //freopen("input.txt", "r",stdin);
    memset(dp,-1,sizeof(dp));
    memset(K, -1, sizeof(K));
    scanf("%d%d%d",&n,&m,&k);
    double ans = solve();
    ans=1.0-ans;
    cout << fixed << setprecision(5) << ans << endl;
    return 0;
}
