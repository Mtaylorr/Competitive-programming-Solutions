//https://codeforces.com/contest/1067/problem/A

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e5 + 5, M=1000 +5,E = 1e6 +5 ;
const int MOD = 998244353   ;
const double eps = 1e-7;

int mul(int u , int v, int mod=MOD){
    return ((u%mod)*1ll*(v%mod))%mod;
}
int add(int u, int v, int mod=MOD){
    return ((u%mod)+0ll+(v%mod)+mod)%mod;
}
int sub(int u, int v , int mod=MOD){
    return ((u%mod)-0ll-(v%mod)+mod)%mod;
}



int dp[2][N][200];
int n;
int a[N];

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    if(n==2){
        if(a[0]==a[1] && a[0]==-1){
            cout << 200;
            return 0;
        }
        if(a[0]==a[1]){
            cout << 1 << endl;
            return 0;
        }
        if(a[0]==-1 || a[1]==-1){
            cout << 1 << endl;
            return 0;
        }
        cout << 0;
        return 0;
    }
    for(int i=1;i<=200;i++){
        if(a[n-1]==-1) {
            dp[0][n - 1][i] = add(dp[0][n - 1][i - 1] ,1);
            dp[1][n - 1][i] = add(dp[1][n - 1][i - 1] , 1);
        }else{
            dp[0][n - 1][i] = dp[0][n - 1][i - 1] ;
            dp[1][n - 1][i] = dp[1][n - 1][i - 1] ;
            if(a[n-1]==i){
                dp[0][n-1][i]=add(dp[0][n-1][i],1);
                dp[1][n - 1][i]=add(dp[1][n - 1][i],1);
            }
        }
    }

    for(int i=1;i<=200;i++){
        dp[0][n-2][i]=dp[0][n-2][i-1];
        dp[1][n-2][i]=dp[1][n-2][i-1];
        if(a[n-2]!=-1){
            if(a[n-2]==i){
                dp[0][n-2][i]=add(dp[0][n-2][i],dp[0][n-1][i]);
                dp[1][n-2][i]=add(dp[1][n-2][i],sub(dp[1][n-1][i], dp[1][n-1][i-1]));
            }
        }else{
            dp[0][n-2][i]=add(dp[0][n-2][i],dp[0][n-1][i]);
            dp[1][n-2][i]=add(dp[1][n-2][i],sub(dp[1][n-1][i], dp[1][n-1][i-1]));
        }
    }
    if(n>=4){
        for(int j=n-3;j>=1;j--){
            for(int i=1;i<=200;i++){
                dp[0][j][i]=dp[0][j][i-1];
                dp[1][j][i]=dp[1][j][i-1];
                if(a[j]!=-1){
                    if(a[j]==i){
                        dp[0][j][i]=add(dp[0][j][i],dp[0][j+1][i]);
                        dp[0][j][i]=add(dp[0][j][i], sub(dp[1][j+1][200], dp[1][j+1][i]));
                        dp[1][j][i]=add(dp[1][j][i],sub(dp[1][j+1][200], dp[1][j+1][i]));
                        dp[1][j][i]=add(dp[1][j][i],sub(dp[0][j+1][i], dp[0][j+1][i-1]));
                    }
                }else{
                    dp[0][j][i]=add(dp[0][j][i],dp[0][j+1][i]);
                    dp[0][j][i]=add(dp[0][j][i], sub(dp[1][j+1][200], dp[1][j+1][i]));
                    dp[1][j][i]=add(dp[1][j][i],sub(dp[1][j+1][200], dp[1][j+1][i]));
                    dp[1][j][i]=add(dp[1][j][i],sub(dp[0][j+1][i], dp[0][j+1][i-1]));
                }
            }
        }
    }

    int j=0;
    for(int i=1;i<=200;i++){
        dp[0][j][i]=dp[0][j][i-1];
        dp[1][j][i]=dp[1][j][i-1];
        if(a[j]!=-1){
            if(a[j]==i){
                dp[1][j][i]=add(dp[1][j][i],sub(dp[1][j+1][200], dp[1][j+1][i]));
                dp[1][j][i]=add(dp[1][j][i],sub(dp[0][j+1][i], dp[0][j+1][i-1]));
            }
        }else{
            dp[1][j][i]=add(dp[1][j][i],sub(dp[1][j+1][200], dp[1][j+1][i]));
            dp[1][j][i]=add(dp[1][j][i],sub(dp[0][j+1][i], dp[0][j+1][i-1]));
        }
    }
    cout << dp[1][0][200];


    return 0;
}
