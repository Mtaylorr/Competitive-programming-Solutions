//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1960
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e3 + 5;

char s[N][N];
char pat[N][N];
int t,n,m,a,b;
int dp[N];
int f[N][N];

int getln(int i, int len, char c){
    while(len && pat[i][len]!=c){
        len=f[i][len-1];
    }
    if(pat[i][len]==c)
        len++;
    return len;
}

void compute_f(){
    for(int i=0;i<a;i++){
        f[i][0]=0;
        for(int j=1;j<b;j++){
            f[i][j] = getln(i,f[i][j-1], pat[i][j]);
        }
    }
}

void match(int x , int y){
    int len=0;
    for(int j=0;j<m;j++){
        len = getln(y, len, s[x][j]);
        if(len==b)
            dp[j]++;
    }
}


int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++){
            scanf("%s",s[i]);
        }
        int ans=0;
        scanf("%d%d",&a,&b);
        for(int i=0;i<a;i++)
            scanf("%s",pat[i]);
        compute_f();
        for(int i=0;i<=n-a;i++){
            memset(dp, 0, sizeof(dp));
            for(int j=0;j<a;j++){
                match(i+j,j);
            }
            for(int i=0;i<m;i++){
                if(dp[i]==a){
                    ans++;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
