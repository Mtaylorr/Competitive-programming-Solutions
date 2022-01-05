//https://www.spoj.com/problems/APIO10A/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 +5 ;
const int MOD = 998244353 ;


int n;
ll a,b,c;
ll x[N];

deque<pair<ll,ll> > dq;
ll sub(const pair<ll,ll> & line , ll x){
    return line.fi*x + line.se;
}

double intersect(const pair<ll,ll> & a,const pair<ll,ll> & b){
    return (a.se-b.se+0.0)/(b.fi-a.fi+0.0);
}


void ins(pair<ll,ll>  line ){

    dq.push_back(line);
    while(dq.size()>=3){
        pair<ll,ll> c = dq.back();
        dq.pop_back();
        pair<ll,ll> b = dq.back();
        dq.pop_back();
        pair<ll,ll> a = dq.back();
        dq.pop_back();
        if(intersect(a,b)<intersect(b,c)){
            dq.push_back(a);
            dq.push_back(b);
            dq.push_back(c);
            break;
        }
        dq.push_back(a);
        dq.push_back(c);
    }
}

ll query(ll x ){
    while(dq.size()>=2){
        pair<ll,ll> first = dq.front();
        dq.pop_front();
        pair<ll,ll> second = dq.front();
        dq.pop_front();
       if(sub(first,x)<sub(second,x)){
            dq.push_front(second);
        }else{
            dq.push_front(second);
            dq.push_front(first);
            break;
        }
    }
    return sub(dq.front(),x);
}


int t;
int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d",&t);
    while(t--){
        while(!dq.empty()){
            dq.pop_back();
        }
        scanf("%d",&n);
        scanf("%lld%lld%lld",&a,&b,&c);
        for(int i=1;i<=n;i++){
            scanf("%lld",&x[i]);
            x[i]=x[i]+x[i-1];
        }
        ll r;
        ins({0,0});
        for(int i=1;i<=n;i++){
            r= query(x[i])+a*x[i]*x[i]+b*x[i]+c;
            ll m = -2ll*a*x[i];
            ll e = r-b*x[i] +a*x[i]*x[i];
            ins({m,e});
        }
        printf("%lld\n",r);
    }
    return 0;
}

