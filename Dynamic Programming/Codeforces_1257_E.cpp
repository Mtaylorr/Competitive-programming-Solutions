//https://codeforces.com/problemset/problem/1257/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 +5 , E = 1<<17;
const int MOD = 1e9 + 7;


int k[3];
int a[3][N];
int n;
int dp[3][N];
int pos[N];


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for(int i=0;i<3;i++){
        cin >> k[i];

    }
    for(int i=0;i<3;i++) {
        for (int j = 0; j < k[i]; j++) {
            cin >> a[i][j];
            pos[a[i][j]] = i;
        }
        sort(a[i], a[i] + k[i]);
    }
    n=k[0]+k[1]+k[2];
    int j=0;
    int nb=0;
    dp[0][0]=k[0];
    for(int i=1;i<=n;i++){
        if(pos[i]==1){
            nb++;
        }
        while(j<k[0] && a[0][j]<=i){
            j++;
        }
        dp[0][i]=nb + k[0]-j;

    }
    j=0;
    nb=0;
    dp[1][0]=k[0]+k[1];
    int mn = dp[0][0];
    int ans=dp[1][0];

    for(int i=1;i<=n;i++){
        if(pos[i]==2){
            nb++;
        }
        mn =min(mn, dp[0][i]);
        while(j<k[1] && a[1][j]<=i){
            j++;
        }
        dp[1][i]=mn+nb + k[1]-j;
        ans=min(ans, dp[1][i]);
    }
    cout << ans;
    return 0;

}
