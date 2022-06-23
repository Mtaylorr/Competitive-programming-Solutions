//https://codeforces.com/problemset/problem/1155/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;

int t;
int n;
ll x,a[N];
ll dp[N];



int main() {
    freopen("input.txt", "r", stdin);
    //freopen("game.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> x;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    ll sum1=0;
    ll sum2=0;
    ll mx1 = 0;
    ll mx2 =0;
    ll ans=0;
    for(int i=0;i<n;i++){
        sum1 += a[i];
        sum2 += x*a[i];
        mx1 = max(mx1,-sum1);
        mx2 = max(mx2,-sum2 + sum1+mx1);
        dp[i]=sum2+mx2;
        ans=max(ans, dp[i]);
    }
    sum1=0;
    mx1=0;
    for(int i=n-1;i>=0;i--){
        sum1+=a[i];
        mx1=max(mx1, -sum1);
        ans=max(ans, sum1+mx1);
        if(i>=1)
            ans=max(ans,dp[i-1]+sum1+mx1);
    }
    cout << ans ;

    return 0;

}
