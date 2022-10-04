//https://codeforces.com/problemset/problem/571/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 3e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

ll dp[5005][5005];
ll a[N];
int n,k;
int x,y,z;

ll solve(int c,int d){
    if(c==0 && d==0){
        return 0;
    }
    if(dp[c][d]!=-1){
        return dp[c][d];
    }
    int lf = (y-c)*(x-1) + (z-d)*(x);
    ll ans = 1e18;
    if(c){
        ans=min(ans, a[lf+x-1]-a[lf+1]+solve(c-1,d));
    }
    if(d)
        ans=min(ans, a[lf+x]-a[lf+1]+solve(c, d-1));
    return dp[c][d]=ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    sort(a+1,a+n+1);
    x=(n-1)/k +1;
    for(int i=0;i<k;i++){
        int w = (n-1-i)/k;
        w++;
        if(w==x){
            z++;
        }else{
            y++;
        }
    }
    cout << solve(y,z);
    return 0;

}
