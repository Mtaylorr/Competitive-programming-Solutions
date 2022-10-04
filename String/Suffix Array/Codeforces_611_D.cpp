//https://codeforces.com/contest/611/problem/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;


int mul(int u , int v, int mod=MOD){
    return ((u%mod)*1ll*(v%mod))%mod;
}
int add(int u, int v, int mod=MOD){
    return ((u%mod)+0ll+(v%mod)+mod)%mod;
}

int sub(int u, int v , int mod=MOD){
    return ((u%mod)+0ll-(v%mod)+mod)%mod;
}
int n;
string s;
int dp[5005][5005];
int lcp[5005][5005];

int solve(int l, int p){
    if(p>=n)
        return 1;

    if(dp[l][p]!=-1)
        return dp[l][p];
    int rs = solve(l, p+1);
    int sz = p-l;
    if(s[p]!='0' && n-p>=sz){
        int x = lcp[l][p];
        bool cond=true;
        if(x>=sz){
            cond=false;
        }else if(s[l+x]>s[p+x]){
            cond=false;
        }
        if(cond){
            rs=(rs+0ll+solve(p, p+sz))%MOD;
        }else if(p+sz<=n-1){
            rs=(rs+0ll+solve(p, p+sz+1))%MOD;
        }
    }
    return dp[l][p]=rs;

}



int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    cin >> n;
    cin >> s;
    for(int i=n-1;i>=0;i--){
        for(int j=i-1;j>=0;j--){
            if(s[i]==s[j]){
                lcp[j][i]=1+lcp[j+1][i+1];
            }else{
                lcp[j][i]=0;
            }
        }
    }
    int ans=solve(0,1);
    cout << ans << endl;

    return 0;

}
