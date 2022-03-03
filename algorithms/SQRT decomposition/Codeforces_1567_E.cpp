//https://codeforces.com/problemset/problem/1567/E
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 1e9 + 7 ;


int n,q,t;
int a[N];
long long dp[N];
int le[N];
int B;
int sz[N];
int ri[N];
int x,y;

ll getrange(int l, int r){
    if(l>r)
        return 0;
    int cn=0;
    int bf = -1;
    ll ans=0;
    for(int j=l;j<=r;j++){
        if(a[j]>=bf){
            cn++;
        }else{
            cn=1;
        }
        bf=a[j];
        ans+=cn;
    }
    return ans;
}

void upd(int i){
    int l = i*B;
    int r = min(n-1,(i+1)*B-1);
    int cn=0;
    int bf = -1;
    dp[i]=0;
    for(int j=l;j<=r;j++){
        if(a[j]>=bf){
            cn++;
        }else{
            cn=1;
        }
        bf=a[j];
        dp[i]+=cn;
    }
    int j=r;
    int x = a[r];
    while(j>=l && a[j]<=x){
        x=a[j];
        j--;
    }
    ri[i]=r-j;
    j = l;
    x=a[l];
    while(j<=r && a[j]>=x){
        x=a[j];
        j++;
    }
    le[i]=j-l;
}

int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&q);
    B = sqrt(n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        sz[i/B]++;
    }
    for(int i=0;i<n;i+=B){
        upd(i/B);
    }
    while(q--){
        scanf("%d%d%d",&t,&x,&y);
        if(t==1){
            x--;
            a[x]=y;
            upd(x/B);
        }else{
            x--;y--;
            ll ans=0;
            int lb = x/B;
            int ub = y/B;
            if(lb==ub){
                ans = getrange(x,y);
            }else{
                lb++;
                ans+=getrange(x, lb*B-1);
                ans+=getrange(ub*B,y);
                ll z=min(ri[lb-1],lb*B-1 - x+1);
                for(int j=lb;j<ub;j++){
                    ans+=dp[j];
                    if(a[(j)*B]>=a[(j)*B-1]){
                        ans+=z*le[j];
                    }else{
                        z=0;
                    }
                    if(le[j]==sz[j]){
                        z+=sz[j];
                    }else{
                        z=ri[j];
                    }

                }
                ll w = min(le[ub],y-ub*B+1);
                if(a[ub*B]>=a[ub*B-1])
                    ans+=(w*z);
            }
            printf("%lld\n",ans);
        }
    }
    return 0;
}
