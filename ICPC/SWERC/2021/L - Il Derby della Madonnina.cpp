#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E= 2e5+5;
const int MOD = 998244353 ;

set<ll> distinct;
map<ll,int> code;

int tree[N];
int cn;
int n, v;
ll t[N];
ll a[N];
vector<pair<ll,ll> > ord;

void upd(int x, int v){
    for(;x<cn;x+=(x)&(-x)){
        tree[x]=max(tree[x],v);
    }
}

int get(int x){
    int rs=-1e9;
    for(;x;x-=(x)&(-x)){
        rs=max(rs, tree[x]);
    }
    return rs;
}


int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    cin >> n >> v;
    for(int i=0;i<n;i++){
        cin >> t[i];
    }
    for(int i=0;i<n;i++){
        cin >> a[i];
    }

    for(int i=0;i<n;i++){
        ord.pb({-(a[i]-t[i]*v),a[i]+t[i]*v});
        distinct.insert(a[i]+t[i]*v);
    }
    ord.pb({0,code[0]});
    cn=1;
    distinct.insert(0);
    for(auto u:distinct){
        code[u]=cn++;
    }
    for(int i=1;i<=cn;i++){
        tree[i]=-1e9;
    }

    for(int i=0;i<=n;i++){
        ord[i].se=code[ord[i].se];
    }

    sort(ord.begin(), ord.end());
    int ans=0;
    for(int i=0;i<=n;i++){
        int rs = get(ord[i].se);
        if(ord[i].fi==0 && ord[i].se==code[0])
            rs=max(rs,0);
        else{
            rs=rs+1;
        }
        ans=max(ans,rs);
        upd(ord[i].se, rs);
    }
    cout << ans;

    return 0;

}
