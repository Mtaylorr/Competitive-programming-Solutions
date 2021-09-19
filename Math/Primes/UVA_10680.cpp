//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1621
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e6 + 5;

int dp[N];
int prime[N];
ll lcm(ll x, ll y){
    return x*(y/__gcd(x,y));
}

ll add(ll x, ll y){
    x = x*y;
    while(x%10==0)
        x/=10;
    return x%100;
}
int n;
int mx=1e6+1;
int main(){
    freopen("input.txt", "r", stdin);
    for(int i=1;i<=mx;i++){
        dp[i]=1;
        prime[i]=1;
    }
    prime[0]=0;
    for(ll i=2;i<=mx;i++){
        if(!prime[i])
            continue;
        for(ll j=i*i;j<=mx;j+=i){
            prime[j]=0;
        }
        for(ll j=i;j<=mx;j*=i){
            dp[j]=add(dp[j],i);
        }
    }
    for(int i=2;i<=mx;i++){
        dp[i]=add(dp[i-1],dp[i]);

    }
    while(1){
        scanf("%d",&n);
        if(n==0)
            break;
        printf("%d\n", dp[n]%10);
    }
    return 0;
}
