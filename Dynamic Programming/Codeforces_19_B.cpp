//https://codeforces.com/problemset/problem/19/B

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e5 + 5, E = 1 << 17;
const int MOD =  1e9 + 7;


int n;
ll dp[2005][4005];
int t[N],c[N];

ll solve(int p, int r){
    r=min(r, 4000);
    if(p>=n){
        if(r>=2000){
            return 0;
        }else{
            return 1e18;
        }
    }
    if(dp[p][r]!=-1){
        return dp[p][r];
    }
    ll ans = solve(p+1, r-1);
    ans=min(ans, c[p] + solve(p+1, r+t[p]));
    return dp[p][r]=ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(dp,-1 ,sizeof(dp));
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> t[i] >> c[i];
    }
    cout << solve(0,2000);
    return 0;
}
