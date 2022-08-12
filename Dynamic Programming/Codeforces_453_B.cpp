//https://codeforces.com/problemset/problem/453/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e2 +5 , E = 1<<17;
const int MOD = 1e9 + 7;

int n;
vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
int a[N];
int msk[60];
int dp[N][E];
int all = (1<<17) -1 ;
int nxt[N][E];
int solve(int p, int m){
    if(p>=n){
        return 0;
    }
    if(dp[p][m]!=-1){
        return dp[p][m];
    }
    if(m==all){
        nxt[p][m]=1;
        return dp[p][m]=a[p]-1  +solve(p+1,m);
    }
    int rs=1e9;
    for(int j=1;j<60;j++){
        if(m&msk[j])
            continue;
        int nx = abs(a[p]-j)+solve(p+1, m|msk[j]);
        if(nx<rs){
            rs=nx;
            nxt[p][m]=j;
        }
    }
    return dp[p][m]=rs;
}
int main() {
    freopen("input.txt", "r", stdin);
    memset(dp, -1,sizeof(dp));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for(int i=2;i<60;i++){
        int m = 0;
        for(int j=0;j<primes.size();j++){
            if(i%primes[j]==0)
                m+=(1<<j);
        }
        msk[i]=m;
    }
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    int ans=solve(0,0);
    int p=0;
    int m = 0;
    while(p<n){
        cout << nxt[p][m] << " ";
        m = m|msk[nxt[p][m]];
        p++;
    }

    return 0;

}
