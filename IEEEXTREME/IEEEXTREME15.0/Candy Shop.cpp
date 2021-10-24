//60%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e6 +5 ;
const int MOD = 998244353;

ll mul(ll u , ll v, ll mod=MOD){
	return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
	return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
	return ((u%mod)-(v%mod)+mod)%mod;
}


int n,k;
int a[N], b[N];
int dp[1005][1005];

int solve(int pos= 0, int rem=k){
    if(pos>=n){
        return (rem==0);
    }
    if(dp[pos][rem]!=-1)
        return dp[pos][rem];
    int res=0;
    for(int j=0;j<=min(a[pos],rem/b[pos]);j++){
        res=add(res, solve(pos+1,rem-b[pos]*j));
    }
    return dp[pos][rem]=res;

}

int main(){
    //freopen("input.txt", "r", stdin);
    memset(dp, -1, sizeof(dp));
    cin >> n >> k;
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
    }
    cout << solve();

    return 0;
}
