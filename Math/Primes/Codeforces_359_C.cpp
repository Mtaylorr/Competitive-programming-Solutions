//https://codeforces.com/problemset/problem/359/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e6 + 5, M=1000 +5,E = 2000 +5;
const int MOD = 1e9 + 7;

ll mul(ll u , ll v, ll mod=MOD){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
    return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
    return ((u%mod)-(v%mod)+mod)%mod;
}

ll powe(ll u, ll v, ll mod=MOD){
    ll ans=1;
    ll acc=u;
    while(v){
        if(v%2){
            ans=mul(ans,acc,mod);
        }
        acc = mul(acc,acc,mod);
        v/=2;
    }
    return ans;
}
int n,x;
ll  a[N];
ll sm=0;
map<ll,int> nb;

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> x;

    for(int i=0;i<n;i++){
        cin >> a[i];
        sm+=a[i];
    }
    ll mn = sm;
    for(int i=0;i<n;i++){
        mn=min(mn , sm-a[i]);
        nb[sm-a[i]]++;
    }
    while(1){
        if(nb.count(mn)==0){
            break;
        }
        if(nb[mn]%x==0){
            nb[mn+1]+=nb[mn]/x;
            mn++;
        }else{
            break;
        }
    }
    mn=min(mn, sm);
    cout << powe(x, mn) << endl;


    return 0;


}
