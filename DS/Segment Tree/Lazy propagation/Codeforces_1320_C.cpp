//https://codeforces.com/problemset/problem/1320/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 1e9 + 7 ;

int n,m,p;
ll a[N], ca[N],b[N], cb[N];
int x[N],y[N],z[N];
map<int,vector<int> > xtoy;
ll tree[8*N], lazy[8*N];
set<int> distinct_y;
ll curvaly[2*N];
map<int,int> code_y;
vector<int> sort_x;
multiset<int> sort_xvalues;
int cn=0;
void rem(int ind){
    sort_xvalues.erase(sort_xvalues.find(ca[ind]));
}

void build(int id=0, int ns=0, int ne=cn-1){
    if(ns==ne){
        tree[id]=curvaly[ns];
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    tree[id]=max(tree[l],tree[r]);
}

void upd_lazy(int id, int ns,int ne){
    tree[id]+=lazy[id];
    if(ns!=ne){
        int l= 2*id+1;
        int r = l+1;
        lazy[l]+=lazy[id];
        lazy[r]+=lazy[id];
    }
    lazy[id]=0;
}

void upd(int qs, int qe, int v,int id=0, int ns=0, int ne=cn-1){
    upd_lazy(id, ns, ne);
    if(qs>ne || qe<ns)
        return ;
    if(qs<=ns && qe>=ne){
        lazy[id]+=v;
        upd_lazy(id, ns, ne);
        return ;
    }
    int l= 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qs, qe, v, l, ns, md);
    upd(qs, qe, v,r, md+1, ne);
    tree[id]=max(tree[l],tree[r]);
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> p;
    for(int i=0;i<n;i++){
        sort_x.pb(i);
        cin >> a[i] >> ca[i];
        sort_xvalues.insert(ca[i]);
    }
    for(int i=0;i<m;i++){
        cin >> b[i] >> cb[i];
        distinct_y.insert(b[i]);
    }
    for(int i=0;i<p;i++){
        cin >> x[i] >> y[i] >> z[i];
        xtoy[x[i]].pb(i);
        distinct_y.insert(y[i]);
    }
    for(auto u:distinct_y){
        curvaly[cn]=-1e18;
        code_y[u] = cn++;
    }
    for(int i=0;i<m;i++){
        b[i]=code_y[b[i]];
        curvaly[b[i]]=max(curvaly[b[i]], -cb[i]);
    }
    for(int i=0;i<p;i++){
        y[i]=code_y[y[i]];
    }
    for(int i=cn-2;i>=0;i--){
        curvaly[i]=max(curvaly[i],curvaly[i+1]);
    }
    build();
    sort(sort_x.begin(), sort_x.end(), [](int x, int y){return ca[x]<ca[y];});
    int ind_x = 0;
    ll ans =curvaly[0] + -(*sort_xvalues.begin());
    for(auto &u:xtoy){
        while(ind_x<n && a[sort_x[ind_x]]<=u.fi){
            rem(sort_x[ind_x]);
            ind_x++;
        }
        if(sort_xvalues.size()==0){
            break;
        }
        ll x_v = *sort_xvalues.begin();
        for(auto v:u.se){
            if(y[v]+1<=cn-1) {

                upd(y[v] + 1, cn - 1, z[v]);
            }
        }
        ll y_sum = tree[0];
        ans=max(ans, y_sum - x_v);
    }

    cout << ans << endl;


    return 0;


}
