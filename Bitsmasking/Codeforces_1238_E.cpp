//https://codeforces.com/problemset/problem/1238/E

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

int n,m;
string s;
int nxt[21][21];
int dp[1<<20];
int target;
int po[N];

int solve(int msk){
    if(msk==target){
        return 0;
    }
    if(dp[msk]!=-1)
        return dp[msk];
    int rs = 1e9;
    int p=0;
    for(int i=0;i<m;i++){
        if(po[i]&msk){
            p++;
        }
    }
    for(int i=0;i<m;i++){
        if(po[i]&msk){
            continue;
        }
        int r=0;
        for(int j=0;j<m;j++){
            if(j==i){
                continue;
            }
            if(po[j]&msk){
                r+=nxt[i][j];
            }else{
                r-=nxt[i][j];
            }
        }
        rs=min(rs, r*p + solve(msk+po[i]));
    }
    return dp[msk]=rs;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(dp,-1,sizeof(dp));
    po[0]=1;
    for(int i=1;i<=20;i++){
        po[i]=2*po[i-1];
    }
    cin >> n >> m;
    cin >> s;
    if(n>=1)
        for(int i=0;i<n-1;i++){
            int l  = s[i]-'a';
            int r = s[i+1]-'a';
            if(l!=r){
                nxt[l][r]++;
                nxt[r][l]++;
            }
        }
    target = (1<<m)-1;
    cout << solve(0);
    return 0;

}
