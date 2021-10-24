#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 5e+3 +2 ;

int t;

int n,m;
ll dp[2][1<<18][4];
int a[N];
int tar=0;
char s[20];
ll solve(int pos=0, int mask =0, int nb=0){
    //cout << mask << " " << tar << " " << nb << endl;
    if(nb==3){
        return mask==tar;
    }
    if(pos>=n)
        return 0;
    if(dp[pos][mask][nb]!=-1)
        return dp[pos][mask][nb];
    ll res=solve(pos+1, mask , nb);
    //cout << pos << " " << mask << " "<< nb << endl;
    res+=solve(pos+1, mask|a[pos],nb+1);
    return dp[pos][mask][nb]=res;
}

int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++){
            scanf("%s",s);
            int cur=0;
            for(int j=0;j<m;j++){
                cur=2*cur + (s[j]=='y');
            }
            a[i]=cur;
        }
        tar = (1<<m)-1;
        for(int i=0;i<2;i++){
            for(int j=0;j<=3;j++){
                for(int k=0;k<=tar;k++)
                    dp[i][k][j]=0;
            }
        }
        dp[0][0][0]=1;
        ll ans=0;
        for(int i=1;i<=n;i++){
            int id = i&1;
            for(int j=0;j<=tar;j++){
                for(int k=0;k<=3;k++)
                    dp[id][j][k]=dp[id^1][j][k];
            }
            for(int j=0;j<=tar;j++){
                for(int k=1;k<=3;k++){
                    dp[id][j|a[i-1]][k]+=dp[id^1][j][k-1];

                }
            }

        }
        ans=dp[n&1][tar][3];
        printf("%lld\n", ans);

    }
    return 0;
}
