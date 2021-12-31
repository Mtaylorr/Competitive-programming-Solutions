//https://vjudge.net/problem/UVALive-4554
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353 ;

int t,n,m;
int dp[1001][51];

int run(int h=m, int b=n){
    if(h==0)
        return 0;
    if(b==1)
        return h;
    int & rt = dp[h][b];
    if(~rt)
        return rt;
    rt = INT_MAX;
    int st= 1 ,e=h,md;
    while(st<e){
        md = st+(e-st)/2;
        if(run(md-1,b-1)<run(h-md,b)){
            st=md+1;
        }else{
            e=md;
        }
    }
    rt = 1+max(run(st-1, b-1), run(h-st,b));
    return rt;
}

int main(){
    freopen("input.txt", "r",stdin);
    memset(dp, -1, sizeof(dp));
    int tt=0;
    scanf("%d",&tt);
    while(tt--){
        scanf("%d%d%d",&t,&n,&m);
        printf("%d %d\n",t, run());
    }

    return 0;
}
