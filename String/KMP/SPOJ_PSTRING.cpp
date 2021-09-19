//https://www.spoj.com/problems/PSTRING/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e6 + 5;

char s[N], pat[N];
int f[N];
int ans=0;
int dp2[1002][250];
int dp[10002][1002];
int n,m;

int getln(int len , char c){
    if(dp2[len][c]!=-1)
        return dp2[len][c];
    int init_len = len;
    while(len && pat[len]!=c){
        len=f[len-1];
    }
    if(pat[len]==c)
        len++;
    return dp2[init_len][c]=len;
}

void compute_f(){
    f[0]=0;
    for(int i=1;pat[i];i++){
        f[i]=getln(f[i-1], pat[i]);
    }
}

int solve(int pos, int ln){
    if(ln>=m)
        return 1e7;
    if(pos>=n)
        return 0;
    if(dp[pos][ln]!=-1)
        return dp[pos][ln];
    int res = 1+solve(pos+1, ln);
    res=min(res, solve(pos+1, getln(ln, s[pos])));
    return dp[pos][ln]=res;
}

int main(){
    freopen("input.txt", "r", stdin);
    while(~scanf("%s",s)){
        scanf("%s",pat);
        n=strlen(s);
        m=strlen(pat);
        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++)
                dp[i][j]=-1;
        for(int i=0;i<=m;i++){
            for(char c='a';c<='z';c++){
                dp2[i][c]=-1;
            }
        }
        compute_f();
        printf("%d\n",solve(0,0));
    }
    return 0;
}
