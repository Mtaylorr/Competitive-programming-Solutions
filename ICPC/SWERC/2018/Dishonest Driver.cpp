#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7 ;

char s[N];
int n;
int f[1000][1000];

void calcf(int b){
    f[b][b]=0;
    int cur=0;
    for(int j=b+1;j<n;j++){
        while(cur!=0 && s[b+cur]!=s[j]){
            cur=f[b][cur+b-1];
        }
        if(s[b+cur]==s[j])
            cur++;
        f[b][j]=cur;
    }
}

int dp[1005][1005];

int solve(int l, int r){
    if(l>r)
        return 0;
    if(l==r)
        return 1;
    if(dp[l][r]!=-1)
        return dp[l][r];
    int rs = 1e9;
    for(int i=l;i<r;i++){
        rs=min(rs, solve(l,i)+solve(i+1,r));
    }
    int sz = r-l+1;
    int x = sz-f[l][r];
    if(sz%x==0 && f[l][r]){
        rs=min(rs, solve(l,l+x-1));
    }

    return dp[l][r]=rs;
}

int main()
{
   // freopen("input.txt", "r",stdin);
    memset(dp,-1, sizeof(dp));
    scanf("%d",&n);
    scanf("%s",s);

    for(int i=0;i<n;i++){
        calcf(i);
    }
    cout << solve(0,n-1);
    return 0;

}
