//https://codeforces.com/contest/1555/problem/E
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll, ll> pl;
typedef long double ld;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)


const int N = int(1e6) + 3;
const int MOD = int(1e9) + 7;

int n,m;
ll l[N], r[N], w[N];
vector<int> v;
ll tree[4*N];
ll lazy[4*N];
ll t[4*N];


void updlazy(int id ,int ns, int ne){
    if(t[id]==0)
        return ;
    t[id]=0;
    tree[id]=lazy[id];
    if(ns!=ne){
        int l = 2*id+1;
        int r = l+1;
        lazy[l]=lazy[id];
        lazy[r]=lazy[id];
        t[l]=1;
        t[r]=1;
    }
}


void upd(int qs , int qe, int val , int id=0, int ns=1, int ne=m){
    updlazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return ;
    }
    if(qs<=ns && qe>=ne){
        lazy[id]=val;
        t[id]=1;
        updlazy(id, ns, ne);
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = (ns+ne)/2;
    upd(qs, qe, val, l, ns, md);
    upd(qs, qe, val, r, md+1, ne);
    tree[id]=max(tree[l], tree[r]);
}



bool cmp(int a, int b){
    return w[a]>w[b];
}

/*
We start from the top doing down , each time we update the values on the segment by the minimum value of a segment that covers some points 
once all points are covered we can update the answer by the maximum value over all points and the current value 
*/

int main() {
    FAST;
    cin >> n >> m;
    for(int i=0;i<n;i++){
        v.pb(i);
        cin >> l[i] >> r[i] >> w[i];
        r[i]--;
    }
    m--;
    for(int i=0;i<4*N;i++){
        tree[i]=1e7;
    }
    sort(all(v), cmp);
    ll ans = 1e18;
    for(auto i:v){
        upd(l[i],r[i],w[i]);
        updlazy(0,1,m);
        if(tree[0]>1e6){
           // some points are not covered
            continue;
        }

        ans=min(ans,tree[0]-w[i]);
    }
    cout << ans << endl;
    return 0;
}
