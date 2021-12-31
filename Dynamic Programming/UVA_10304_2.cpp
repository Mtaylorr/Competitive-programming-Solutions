//https://vjudge.net/problem/UVA-10304
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353 ;

int n, freq[300];
int dp[300][300];

int run(int s=1,int e=n){

    for(int len = 2;len<=n;len++){
        for(int s=1;s+len-1<=n;s++){
            int e = s+len-1;
            int &rs = dp[s][len];
            rs=INT_MAX;
            for(int i=s;i<=e;i++){
                rs=min(rs, freq[e]-freq[s-1]-(freq[i]-freq[i-1]) + dp[s][i-s] + dp[i+1][e-i]);
            }
        }
    }
    return dp[1][n];
}

int main(){
    freopen("input.txt", "r",stdin);
    while(~scanf("%d",&n)){
        for(int i=1;i<=n;i++){
            scanf("%d",&freq[i]);
            freq[i]+=freq[i-1];
        }
        printf("%d\n",run());
    }

    return 0;
}

