//https://codeforces.com/problemset/problem/797/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e5 + 5, E = 1 << 17;
const int MOD = 1e9 + 7;

int a[N];
int dp[N][320];
int n;
int q,p,k;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    int B = sqrt(n);
    for(int i=0;i<n;i++)
        cin >> a[i];
    for(int i=n-1;i>=0;i--) {
        for (int j = 1; j <= B; j++) {
            int x = i + a[i] + j;
            if (x >= n) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = 1 + dp[x][j];
            }
        }
    }
    cin >> q;
    while(q--){
        cin >> p >> k;
        p--;
        if(k<=B){
            cout << dp[p][k] << "\n";
        }else{
            int nb=0;
            while(p<n){
                p=p+a[p]+k;
                nb++;
            }
            cout << nb << "\n";
        }
    }
    return 0;


}
