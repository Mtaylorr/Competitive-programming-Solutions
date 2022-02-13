//https://codeforces.com/problemset/problem/662/C
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 + 7 ;
int n,m;
char s[21][100002];
int dp[21][(1<<20) + 2];
int x[N];
map<int,int> freq;
int po[30];

int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&m);
    po[0]=1;
    for(int i=1;i<=20;i++){
        po[i]=2*po[i-1];
    }
    for(int i=0;i<n;i++){
        scanf("%s",s[i]);
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            x[i]=2*x[i]+(s[j][i]-'0');
        }
        freq[x[i]]++;
    }
    for(int mask=0;mask<po[n];mask++){
        dp[0][mask]=freq[mask];
    }
    for(int k=1;k<=n;k++){
        for(int mask=0;mask<po[n];mask++){
            if(k>=2){
                dp[k][mask]=(k-2-n)*dp[k-2][mask];
            }
            for(int p=0;p<n;p++){
                dp[k][mask]+=dp[k-1][mask^po[p]];
            }
            dp[k][mask]/=k;
        }
    }
    int ans=n*m;
    for(int mask=0;mask<(po[n]);mask++){
        int res=0;
        for(int i=0;i<=n;i++){
            res+=min(i,n-i)*dp[i][mask];
        }
        ans=min(ans,res);
    }
    cout << ans;
    return 0;
}
