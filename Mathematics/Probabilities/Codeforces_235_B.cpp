//https://codeforces.com/problemset/problem/235/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e6 + 5, M=1000 +5,E = 2000 +5;
const int MOD = 1e9 + 7;

int n;
double a[N];
double dp[N][2];

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    double smp = 0;
    double sm = 0;
    double smpp=0;
    double smdp=0;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=n-1;i>=0;i--){
        smpp+=smp;
        sm+=smp+2*smpp;
        sm+=1*(1-a[i+1]);
        dp[i][0]=(1-a[i+1])*dp[i+1][0]+ (a[i+1])*dp[i+1][1];
        dp[i][1]=sm+smdp;
        smp+=((1-a[i+1]));
        smp*=a[i];
        smpp*=a[i];
        sm*=a[i];
        smdp=(1-a[i])*dp[i][0]+a[i]*smdp;
    }
    cout << fixed << setprecision(10) <<(1-a[0])*dp[0][0]+a[0]*dp[0][1] << endl;
    return 0;


}
