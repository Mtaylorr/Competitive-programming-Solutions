//https://codeforces.com/problemset/problem/1316/E
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5, E = 2*2e5 + 5;
const int MOD = 1e9 + 7 ;

int n,p,k;
int s[N][10];
int a[N];
ll dp[N][129];
int bitcnt[129];
vector<int> v;
int msk;

int cntBit(int x){
    int rs=0;
    while(x){
        rs+=x%2;
        x/=2;
    }
    return rs;
}

ll solve(int i, int mask){
    if(i>=n){
        if(mask==msk)
            return 0;
        return -1e18;
    }
    if(dp[i][mask]!=-1)
        return dp[i][mask];
    ll rs = -1e18;
    int rm = (i)-bitcnt[mask];
    if(rm<k){
        rs=max(rs, a[v[i]]+0ll+solve(i+1,mask));
    }else{
        rs=max(rs, solve(i+1, mask));
    }
    for(int j=0;j<p;j++){
        if(!(mask&(1<<j))){
            rs=max(rs, s[v[i]][j]+0ll+solve(i+1, mask+(1<<j)));
        }
    }
    return dp[i][mask]=rs;
}


int main()
{
    freopen("input.txt", "r",stdin);
    memset(dp,-1,sizeof(dp));
    scanf("%d%d%d",&n,&p,&k);
    msk=(1<<p)-1;
    for(int i=0;i<=msk;i++){
        bitcnt[i]=cntBit(i);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        v.pb(i);
    }
    sort(v.begin(),v.end(), [](int x, int y){return a[x]>a[y];});
    for(int i=0;i<n;i++){
        for(int j=0;j<p;j++){
            scanf("%d",&s[i][j]);
        }
    }
    cout << solve(0,0);


    return 0;

}
