//https://codeforces.com/problemset/problem/16/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5, E = 1 << 17;
const int MOD =  998244353;

int n;
double a[20][20];
double dp[1<<18];
bool vis[1<<18];
int target;
double solve(int mask){
    if(mask==target){
        return 1.0;
    }
    if(vis[mask]){
        return dp[mask];
    }
    vis[mask]=1;
    vector<int> x,y;
    int cur=1;
    for(int i=0;i<n;i++){
        if(mask&cur){
            x.pb(i);
        }else{
            y.pb(i);
        }
        cur*=2;
    }
    double rs=0.0;
    for(auto u:x){
        for(auto v:y){
            rs+=a[u][v]*(solve(mask+(1<<v)));
        }
    }
    rs/=((x.size())*(x.size()+1)*0.5);
    return dp[mask]=rs;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin  >> n;
    target = (1<<n)-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> a[i][j];
        }
    }
    for(int i=0;i<n;i++){
        cout << fixed  << setprecision(10) << solve(1<<i) << " ";
    }
    return 0;
}
