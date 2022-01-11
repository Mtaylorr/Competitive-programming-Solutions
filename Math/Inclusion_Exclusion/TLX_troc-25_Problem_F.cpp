//https://tlx.toki.id/problems/troc-25/F
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 +1 ;
const int MOD = 998244353 ;

ll n,t;
ll m;
ll ni;
ll dp[N];
ll p[N];
bool isprime[N];
ll sum[N];
void sieve(){
    for(int i=1;i<=n;i++){
        p[i]=1;
        isprime[i]=1;
    }
    isprime[0]=0;
    isprime[1]=0;
    p[1]=1;
    for(int i=2;i<=n;i++){
        if(!isprime[i])
            continue;
        p[i]=-1;
        for(int j=2;j<=n/i;j++){
            isprime[j*i]=0;
            if(j%i==0){
                p[j*i]=0;
            }
            p[j*i]*=-1;
        }
    }
}

void solve(){
    dp[1]=1;
    ll cumsum=1;
    for(int i=2;i<=n;i++){
        dp[i]=cumsum;
        for(int j=2;j<=i/j;j++){
            if(i%j==0){
                dp[i]=(dp[i] + m+ (p[j]*sum[j] )%m)%m;
                if(j!=i/j){
                    dp[i]=(dp[i] + m+(p[i/j]*sum[i/j] )%m)%m;
                }
            }
        }
        cumsum+=dp[i];
        cumsum%=m;
        for(int j=2;j<=i/j;j++){
            if(i%j==0){
                sum[j]+=dp[i];
                sum[j]%=m;
                if(j!=i/j){
                    sum[i/j]+=dp[i];
                    sum[i/j]%=m;
                }
            }
        }
        sum[i]+=dp[i];
        sum[i]%=m;
    }
}

int dp2[N];
void solve_brute()
{
    dp2[1]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            if(__gcd(i,j)==1)
                dp2[i]=(dp2[i]+dp2[j])%m;
        }
    }
}
int main(){
    //freopen("input.txt", "r",stdin);
    n=2e5;
    cin >> t >> m;
    sieve();
    solve();

    while(t--){
        cin >> ni;
        cout << dp[ni] << endl;
    }
    return 0;
}
