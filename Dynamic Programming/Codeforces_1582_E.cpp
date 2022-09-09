//https://codeforces.com/problemset/problem/1582/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5, E = 1 << 17;
const int MOD =  998244353 ;


ll dp[N][500];
int n,a[N];
ll sum[N];
int t;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n;
        for(int i=1;i<=n;i++){
            cin >> a[i];
            sum[i]=a[i]+sum[i-1];
        }
        int smk=1;
        int ans=1;

        for(int i=1;i<=n;i++){
            dp[i][1]=a[i];
        }
        dp[n+1][1]=0;


        for(int k=2;;k++){
            smk+=k;
            if(smk>n)
                break;
            for(int i=1;i<=n+1;i++) {
                dp[i][k]=0;
            }
            ll mx = 0;
            bool cond=false;
            for(int j=n-k+1;j>=1;j--){
                mx=max(mx, dp[j+k][k-1]);
                ll sm =sum[j+k-1]-sum[j-1];
                if(mx>sm){
                    dp[j][k]=sm;
                    cond=true;
                }
            }
            if(cond){
                ans=k;
            }else{
                break;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
