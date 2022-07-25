//https://codeforces.com/problemset/problem/1490/G
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;

int n,m;
ll a[N];
ll x;
int t;
ll sum;
vector<ll> v, idx;


int get(ll u){
    if(v[v.size()-1]<u){
        return -1;
    }
    int p = lower_bound(v.begin(), v.end(),u)-v.begin();
    if(p==v.size()){
        return -1;
    }else{
        return idx[p];
    }
}


bool ok(ll u, ll x){
    int  p =get(x-u*sum);
    if(p!=-1){
        return 1;
    }else{
        return 0;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("game.in", "r", stdin);
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    //cout.tie(0);
    scanf("%d",&t);
    while(t--){
        v.clear();
        idx.clear();
        scanf("%d%d",&n,&m);
        sum=0;
        ll mx=0;
        v.pb(0);
        idx.pb(0);
        for(int i=0;i<n;i++){
            scanf("%lld",a+i);
            sum+=a[i];
            if(sum>mx){
                mx=sum;
                v.pb(mx);
                idx.pb(i+1);
            }
        }
        while(m--){
            scanf("%d",&x);
            ll l = 0;
            ll r = 0;
            if(sum>0)
                r = ((ll) x+sum-1)/sum;
            while(l<r){
                ll md = (l+r)/2;
                if(ok(md,x)){
                    r=md;
                }else{
                    l=md+1;
                }
            }
            int p =get(x-l*sum);
            if(p!=-1)
                printf("%lld ",(n*l)+(p-1));
            else{
                printf("-1 ");
            }
        }
        cout << endl;
    }

    return 0;

}
