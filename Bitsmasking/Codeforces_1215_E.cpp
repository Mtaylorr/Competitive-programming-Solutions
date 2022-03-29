//https://codeforces.com/contest/1215/problem/E
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = (1<<20) +5;
const int MOD = 998244353 ;

int n,a[N];
ll b[22][22];
int f[22];
ll cnt[22];
ll dp[N];
int msk = (1<<20) -1 ;
int po[22];

ll solve(int mask){
    if(mask==msk)
        return 0;
    if(dp[mask]!=-1)
        return dp[mask];
    ll rs=1e18;
    for(int i=0;i<20;i++){
        if(mask&po[i])
            continue;
        ll c=0;
        for(int j=0;j<20;j++){
            if(!(mask&po[j]))
                c+=b[i][j];
        }
        ll z = solve(mask|po[i]);

        rs=min(rs,  c+z);
    }
    return dp[mask]=rs;
}
int main()
{
    //freopen("input.txt", "r",stdin);
    memset(dp,-1,sizeof(dp));
    po[0]=1;
    for(int i=1;i<=20;i++){
        po[i]=2*po[i-1];
    }
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        a[i]--;
        for(int j=0;j<20;j++){
            if(j!=a[i]){
                b[a[i]][j]+=f[j];
            }
        }
        f[a[i]]++;
    }
    /*for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout << b[i][j] << " ";
        }
        cout << endl;
    }*/
    /*for(int mask=0;mask<msk;mask++){
        for(int i=0;i<20;i++){
            for(int j=0;j<20;j++){
                if(mask&po[j])
                    cnt[i][mask]+=cnt[i][j];
            }
        }
    }*/
    ll ans = solve(0);
    cout << ans;

    return 0;

}
