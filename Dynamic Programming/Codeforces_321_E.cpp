//https://codeforces.com/problemset/problem/321/E
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 1e9 + 7 ;


int u[4005][4005];
int n,k;
int dp[2][4005];
int p[2][4005];
int ranges[4005][4005];

int getrange(int l, int r){
    return (u[r][r]+u[l-1][l-1]-u[l-1][r] - u[r][l-1])/2;
}

void solve(int id, int qs, int qe, int optl, int optr){
    if(qs>qe)
        return ;
    int md  = qs+(qe-qs)/2;
    pair<int,int> bst = {1e9, -1};
    int l=max(optl,p[id^1][md]),r=min(md, optr);
    for(int k=l;k<=r;k++){
        bst = min(bst, {dp[id^1][k-1] + ranges[k][md],k});
    }
    dp[id][md] = bst.fi;
    int opt = bst.se;
    p[id][md]=opt;

    solve(id, qs, md-1, optl, opt);
    solve(id, md+1, qe, opt, optr);
}

int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&k);
    char c;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf(" %c",&c);
            u[i][j]=c-'0';
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            u[i][j]+=u[i-1][j]+u[i][j-1] - u[i-1][j-1];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            ranges[i][j]=getrange(i,j);
        }
    }
    for(int i=1;i<=n;i++){
        dp[0][i]=1e9;
    }
    for(int i=1;i<=k;i++){
        solve(i%2 , 1, n, 1, n);
    }
    cout << dp[k&1][n] << endl;


    return 0;
}
