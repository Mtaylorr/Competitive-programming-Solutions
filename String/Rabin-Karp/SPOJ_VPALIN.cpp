//https://www.spoj.com/problems/VPALIN/
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define fi first
#define se second
 
const int N = int(2e6) + 3;
 
const int MOD[] = {(int)1e9+7,1000000093};
const int BASE = 128;
 
ll mul(ll u , ll v, ll mod){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod){
    return ((u%mod)+(v%mod)+mod)%mod;
}
 
ll sub(ll u, ll v , ll mod){
    return ((u%mod)-(v%mod)+mod)%mod;
}
 
ll powe(ll u, ll v, ll mod){
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
ll  inv(ll u,ll mod){
    return powe(u,mod-2,mod);
}
ll p[2][N];
ll ip[2][N];
map<pair<ll,ll>,ll> maa;
string s;
int n,m;
int main(){
    p[0][0]=p[1][0]=1;
    for(int i=1;i<=2000000;i++){
        p[0][i]=mul(p[0][i-1],BASE,MOD[0]);
        ip[0][i]=inv(sub(p[0][i],1,MOD[0]),MOD[0]);
        p[1][i]=mul(p[1][i-1],BASE,MOD[1]);
        ip[1][i]=inv(sub(p[1][i],1,MOD[1]),MOD[1]);
    }
    cin >> n;
    ll ans=0;
    while(n--){
        cin >> m;
        cin >> s;
        pair<ll,ll> h;
        for(int i=0;i<m;i++){
            h.fi=add(h.fi,mul(p[0][i],s[i],MOD[0]),MOD[0]);
            h.se=add(h.se,mul(p[1][i],s[i],MOD[1]),MOD[1]);
        }
        h.fi = mul(h.fi,ip[0][m],MOD[0]);
        h.se = mul(h.se,ip[1][m],MOD[1]);
        ans+=2*maa[h];
        maa[h]++;
        ans++;
    }
    cout << ans;
    return 0;
} 
