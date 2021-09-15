//https://www.spoj.com/problems/EASYMATH/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;
const int N = 1e6+5;

int t;
ll n,m,a,d;

ll lcm(ll x, ll y){
    return (x*(y/__gcd(x,y)));
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d%d",&n,&m,&a,&d);
        vector<ll> v;
        for(int i=0;i<=4;i++){
            v.pb(a+d*i);
        }
        ll ans=0;
        for(int mask=1;mask<(1<<5);mask++){
            int cnt=0;
            ll cur = -1 ;
            for(int bit=0;bit<5;bit++){
                if((1<<bit)&mask){
                    cnt++;
                    if(cur==-1)
                        cur=v[bit];
                    else
                        cur=lcm(cur, v[bit]);
                    if(cur>m){
                        cnt=-1;
                        break;
                    }
                }
            }
            if(cnt>=0 && cnt%2){
                ans+=m/cur -(n-1)/cur;
            }else if(cnt>=0){
                ans-=m/cur -(n-1)/cur;
            }
        }
        ans=(m-n+1)-ans;
        printf("%lld\n",ans);
    }
    return 0;
}
