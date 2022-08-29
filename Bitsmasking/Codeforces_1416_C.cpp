//https://codeforces.com/problemset/problem/1416/C

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5, E = 1 << 17;
const int MOD =  998244353;


unordered_map<int,int> sz;
ll dp[30][2];
int n, a[N];
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    int cur=0;
    for(int bit=29;bit>=0;bit--){
        sz.clear();
        int curpo = 1<<bit;
        cur+=curpo;
        for(int i=0;i<n;i++){
            int x = a[i]&cur;
            if(x&(curpo)){
                sz[x]++;
                dp[bit][1]+=sz[x-curpo];
            }else{
                sz[x]++;
                dp[bit][0]+=sz[x+curpo];
            }
        }
    }
    ll x=0;
    ll ans=0;
    for(int i=0;i<30;i++){
        if(dp[i][0]<=dp[i][1]){
            ans+=dp[i][0];
        }else{
            ans+=dp[i][1];
            x+=(1<<i);
        }
    }
    cout << ans << " " << x;
    return 0;
}
