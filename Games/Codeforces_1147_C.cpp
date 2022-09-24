//https://codeforces.com/problemset/problem/1147/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 1e9 + 7  ;
const double eps = 1e-7;

int n;
int a[N];

int dp[55][55];

int solve(int x, int y){
    if(x==0 || y==0){
        return 1;
    }
    if(dp[x][y]!=-1){
        return dp[x][y];
    }
    int rs = 0;
    for(int i=1;i<=x;i++){
        rs=max(rs, 1-solve(x-i, y));
    }
    for(int i=1;i<=y;i++){
        rs=max(rs, 1-solve(x, y-i));
    }
    return dp[x][y]=rs;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(dp,-1, sizeof(dp));
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    int c=0;
    sort(a,a+n);
    reverse(a,a+n);
    bool cond=solve(a[n/2-1],a[n-1]);
    if(cond){
        cout << "Alice\n";
    }else{
        cout << "Bob\n";
    }
    return 0;
}
