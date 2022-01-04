//https://www.spoj.com/problems/BRKSTRNG/en/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 +5 ;
const int MOD = 998244353 ;

ll dp[1005][1005];
int bsti[1005][1005];
int n,m;
int a[N];
int main(){
    freopen("input.txt", "r",stdin);
    while(~scanf("%d%d",&n,&m)){
        for(int i=1;i<=m;i++){
            scanf("%d",&a[i]);
        }
        a[++m]=n;
        for(int i=1;i<=m;i++){
            dp[i][1]=0;
            bsti[i][1]=i;
        }
        for(int len=2;len<=m;len++){
            for(int s=1;s+len-1<=m;s++){
                int e = s+len-1;
                int ss = bsti[s][len-1];
                int ee = bsti[s+1][len-1];
                ll &r = dp[s][len];
                r=1e18;
                for(int j=ss;j<=min(ee,e-1);j++){
                    ll x = a[e]-a[s-1]+dp[s][j-s+1]+dp[j+1][e-j];
                    if(x<r){
                        r=x;
                        bsti[s][len]=j;
                    }
                }
            }
        }
        cout << dp[1][m] << endl;
    }

    return 0;
}
