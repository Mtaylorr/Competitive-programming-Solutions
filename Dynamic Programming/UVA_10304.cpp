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
int vis[300][300], vid=1, dp[300][300];

int run(int s=1,int e=n){
    if(s>e){
        return 0;
    }
    int &rt = dp[s][e];
    if(vis[s][e]==vid)
        return rt;
    vis[s][e]=vid;
    rt=INT_MAX;
    for(int i=s;i<=e;i++){
        int cur = freq[e]-freq[s-1] - (freq[i]-freq[i-1]) + run(s, i-1) + run(i+1,e);
        rt=min(rt, cur);
    }
    return rt;
}

int main(){
    freopen("input.txt", "r",stdin);
    while(~scanf("%d",&n)){
        vid++;
        for(int i=1;i<=n;i++){
            scanf("%d",&freq[i]);
            freq[i]+=freq[i-1];
        }
        printf("%d\n",run());
    }

    return 0;
}
