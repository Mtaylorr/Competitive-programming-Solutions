//https://codeforces.com/problemset/problem/366/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5, E = 1 << 17;
const int MOD = 998244353;


int n,k, a[N],b[N];
int dp[105][200005];

int solve(int i, int cur){
    if(i>=n){
        if(cur==10000){
            return 0;
        }
        return -1e9;
    }
    if(dp[i][cur]!=-1)
        return dp[i][cur];
    int rs = -1e9;
    if(cur==10000){
        rs=0;
    }
    rs=max(rs, solve(i+1,cur));
    rs=max(rs, a[i] + solve(i+1, cur+b[i]*k-a[i]));
    return dp[i][cur]=rs;
}

int main() {
    freopen("input.txt", "r", stdin);
    memset(dp, -1, sizeof(dp));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n;i++){
        cin >> b[i];
    }
    int ans=-1;
    ans=max(ans, solve(0,10000));
    if(ans)
        cout << ans << endl;
    else{
        cout << -1 << endl;
    }
    return 0;
}
