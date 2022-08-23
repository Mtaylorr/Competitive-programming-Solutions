//https://codeforces.com/contest/1223/problem/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5, E = 1 << 17;
const int MOD = 998244353;


int l[N],r[N];
int dp[N];
int n;
int a[N];
int t;

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >>t;
    while(t--){
        cin >> n;
        for(int i=1;i<=n;i++){
            l[i]=r[i]=-1;
            dp[i]=0;
        }
        for(int i=0;i<n;i++){
            cin >> a[i];
            if(l[a[i]]==-1){
                l[a[i]]=i;
            }
            r[a[i]]=i;
        }
        int mx=-1;
        int cur=0;
        int d=0;
        for(int i=1;i<=n;i++){
            if(l[i]==-1)
                continue;
            d++;
            if(l[i]>mx){
                cur++;
            }else{
                cur=1;
            }
            dp[i]=cur;
            mx=r[i];
        }
        int ans=n;
        for(int i=1;i<=n;i++){
            if(l[i]!=-1)
                ans=min(ans, d-dp[i]);
        }
        cout << ans << endl;
    }
    return 0;
}
