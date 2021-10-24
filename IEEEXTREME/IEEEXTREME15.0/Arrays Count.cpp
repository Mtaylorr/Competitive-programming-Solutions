//20%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 +5 ;

int t;
ll n, k;
int mask[20];

int dp[15];
int tar;

int solve(int pos=0){
    if(pos>=k){
        return 1;
    }
    int & res = dp[pos];
    if(res!=-1)
        return res;

    res=0;
    int cur=1;
    for(int j=pos;j<k;j++){
        if(mask[j]==0)
            continue;
        res+=solve(j+1);
        res%=4;
    }
    return res;
}

int prefixSolve(int pos=0, int cur_mask=0){
    if(pos>=k){
        return 0;
    }
    int res=0;
    int new_mask = 0;
    int cur=1;
    bool cond=false;
    for(int j=pos;j<k;j++){
        if(mask[j]==0){
            cur*=2;
            continue;
        }
        new_mask = new_mask + cur*mask[j];
        cur*=2;
        if((new_mask|cur_mask)==tar)
            cond=true;
        if(cond){
            res+=solve(j+1);
        }else{
            res+=prefixSolve(j+1, new_mask|cur_mask);
        }
        res%=4;
    }

    return res;
}


int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%lld %lld",&n,&k);
        int ans=0;
        tar = (1<<n)-1;
        for(int i=0;i<(1<<k);i++){
            for(int j=0;j<k;j++){
                mask[j]=((1<<j)&i)>0;
            }
            memset(dp,-1, sizeof(dp));
            int res = prefixSolve();
            ans=ans+res;
            ans%=4;
        }
        cout << ans << endl;
    }
    return 0;
}
