//https://www.spoj.com/problems/NKLEAVES/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353 ;

int n,k,leaves[N];
ll dp[2][N];
ll cm1[N], cm2[N];

void row(int mk, int s, int e ,int ss, int ee){
    if(e<s)
        return ;
    int md  = s+(e-s)/2;
    ll &ret = dp[mk&1][md];
    ret = 1e18;
    int bstj;
    for(int j=max(ss,md);j<=ee;j++){
        ll sum=cm2[j]-cm2[md-1]-md*1ll*(cm1[j]-cm1[md-1]) + dp[(mk+1)&1][j+1] ;
        if(sum<ret){
            ret=sum;
            bstj=j;
        }
    }
    row(mk,s, md-1, ss, bstj);
    row(mk, md+1, e,bstj,ee );
}

int main(){
    freopen("input.txt", "r",stdin);

    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&leaves[i]);
        cm1[i]=cm1[i-1]+leaves[i];
        cm2[i] = cm2[i-1] + i*1ll*leaves[i];
        dp[0][i]=1e18;
    }
    for(int mk=1;mk<=k;mk++){
        row(mk,1,n,1,n);
    }
    printf("%lld", dp[k&1][1]);
    return 0;
}
