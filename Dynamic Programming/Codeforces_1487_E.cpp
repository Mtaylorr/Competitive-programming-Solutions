//https://codeforces.com/problemset/problem/1487/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e5 +5 , E = 1<<17;
const int MOD = 1e9 + 7;

int n[4];
int a[4][N];
vector<int> adj[3][N];
int m;
int dp[4][N];
int x,y;
multiset<int> s;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for(int i=0;i<4;i++){
        cin >> n[i];
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<n[i];j++){
            cin >> a[i][j];
        }
    }
    for(int i=0;i<3;i++){
        cin >> m;
        while(m--){
            cin >> x >> y;
            x--;y--;
            adj[i][x].pb(y);
        }
    }
    for(int i=0;i<n[3];i++){
        dp[3][i]=a[3][i];
    }
    for(int i=2;i>=0;i--){
        s.clear();
        for(int j=0;j<n[i+1];j++){
            s.insert(dp[i+1][j]);
        }
        for(int j=0;j<n[i];j++){
            for(auto u:adj[i][j]){
                s.erase(s.find(dp[i+1][u]));
            }
            if(s.size()){
                dp[i][j]=a[i][j]+*(s.begin());
            }else{
                dp[i][j]=1e9;
            }
            for(auto u:adj[i][j]){
                s.insert(dp[i+1][u]);
            }
        }
    }
    int ans=1e9;
    for(int i=0;i<n[0];i++){
        ans=min(ans, dp[0][i]);
    }
    if(ans<1e9){
        cout << ans;
    }else{
        cout << -1;
    }
    return 0;

}
