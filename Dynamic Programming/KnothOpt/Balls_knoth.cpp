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
int dp[51][1005];

void run(){
    for(int h=0;h<=1000;h++){
        dp[1][h]=h;
    }
    for(int b=2;b<=50;b++){
        int i=1;
        for(int h=1;h<=1000;h++){
            int &rt = dp[b][h];
            rt = 1e9;
            for(;i<=h;i++){
                int f = dp[b-1][i-1],s= dp[b][h-i];
                if(f>=s){
                    rt=1+max(f,s);
                    break;
                }
            }
        }
    }
}

int main(){
    freopen("input.txt", "r",stdin);
    int tt=0;
    run();
    scanf("%d",&tt);
    while(tt--){
        scanf("%d%d%d",&t,&n,&m);
        printf("%d %d\n",t, dp[n][m]);
    }

    return 0;
}
