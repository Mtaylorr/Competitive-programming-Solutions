//https://codeforces.com/problemset/problem/1260/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 1 << 17;
const int MOD =  1e9 + 7;

int n,m,k,t;
int a[N];
int l[N],r[N],d[N];
vector<int> p[N];

bool ok(int u){
    if(u==0){
        return 1;
    }
    int mn = a[u-1];
    int mxposr=0;
    //cout << u << " " << mn << endl;
    ll ans=0;
    for(int i=1;i<=n+1;i++){
        int posr = -1;
        for(auto u:p[i]){
            if(d[u]>mn){
                posr=max(posr, r[u]);
            }
        }
        mxposr=max(mxposr, i-1);
        if(posr>mxposr){
            ans+=2*(posr-mxposr);
            mxposr=posr;
        }
        ans++;
    }
    return ans<=t;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> m >> n >> k >> t;
    for(int i=0;i<m;i++){
        cin >> a[i];
    }
    sort(a,a+m);
    reverse(a,a+m);
    for(int i=0;i<k;i++){
        cin >> l[i] >> r[i] >> d[i];
        p[l[i]].pb(i);
    }
    int l = 0;
    int r = m;
    while(l<r){
        int md = (l+r+1)/2;
        if(ok(md)){
            l=md;
        }else{
            r=md-1;
        }
    }
    cout << l ;
    return 0;
}
