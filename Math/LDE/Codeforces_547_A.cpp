//https://codeforces.com/contest/547/problem/A

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e6  + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 998244353;

bool vis[N];
int m;
ll x[2], y[2], h[2],a[2];
ll c[2], d[2];

ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> m;
    for(int i=0;i<2;i++){
        cin >> h[i] >> a[i];
        cin >> x[i] >> y[i];
    }
    for(int i=0;i<2;i++){
        memset(vis, 0, sizeof(vis));
        ll cur = h[i];
        while(vis[cur]==0 && cur!=a[i]){

            c[i]++;
            vis[cur]=1;
            cur=(x[i]*cur+y[i])%m;
        }

        if(cur!=a[i]){
            cout << -1;
            return 0;
        }
        d[i]=1;
        memset(vis, 0, sizeof(vis));
        cur=(x[i]*cur+y[i])%m;
        while(vis[cur]==0 && cur!=a[i]){
            d[i]++;
            vis[cur]=1;
            cur=(x[i]*cur+y[i])%m;
        }
        if(cur!=a[i]){
            d[i]=-1;
        }
    }

    if(d[0]==-1 || d[1]==-1){
        ll z = -1;
        if(d[0]==-1){
            z=c[0];
        }else{
            z=c[1];
        }
        for(int i=0;i<z;i++){
            for(int j=0;j<2;j++){
                h[j]=(h[j]*x[j]+y[j])%m;
            }
        }
        if(h[0]!=a[0] || h[1]!=a[1]){
            cout << -1;
            return 0;
        }
    }
    ll cd = c[1]-c[0];
    ll e,f,g;
    if(find_any_solution(d[0], -d[1],cd, e, f,g)){
        ll ans1 = c[0] + d[0]*e;
        ll ans2 = c[1] + d[1]*f;
        while(e>0){
            ll k  =e/((d[1]/g)) +1;
            e-=k*(d[1]/g);
            f-=k*(d[0]/g);
        }
        while(f>0){
            ll k  =f/((d[0]/g))+1;
            e-=k*(d[1]/g);
            f-=k*(d[0]/g);
        }
        while(e<0) {
            ll z = d[1]/g;
            ll k  = (abs(e)+z-1)/z;
            e+=k*z;
            f+=k*(d[0]/g);
            ans1 = c[0] + d[0]*e;
        }
        while(f<0) {
            ll z = d[0]/g;
            ll k  = (abs(f)+z-1)/z;
            e+=k*(d[1]/g);
            f+=k*(d[0]/g);
            ans1 = c[0] + d[0]*e;
        }

        cout << ans1;
    }else{
        cout << -1;
    }
    return 0;

}
