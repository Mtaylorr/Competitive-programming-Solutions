//https://codeforces.com/contest/837/problem/G

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


int x[2][N], y[2][N], a[N],b[N];
int n,m,l,r,xx;


struct node;


extern node* emp;
struct node {
    ll sum;
    node *l , *r;
    node(){
        sum=0;
        l=r=this;
    }
    node(ll s, node *lft=emp, node * rt = emp){
        sum=s;
        l=lft;
        r=rt;
    }
};

node * emp = new node;
node* ins(node * root, int pos, ll val, int ns=1, int ne=n){
    if(pos<ns  || pos>ne)
        return root;
    if(ns==ne)
        return new node(root->sum+val);
    int md = ns+(ne-ns)/2;
    node * nl = ins(root->l, pos, val, ns, md);
    node * nr = ins(root->r, pos, val, md+1, ne);
    return new node(nl->sum+nr->sum, nl, nr);
}
node * fixes[N], *as[N], *bs[N];
vector<pair<int,int> > addy[N],adda[N],addb[N];

ll query(node *rt, int l, int r, int nst=1, int nen=n){
    if(nst>r || nen<l)
        return 0;
    if(l<=nst && r>=nen)
        return rt->sum;
    if(rt==emp){
        return 0;
    }
    int md = nst+(nen-nst)/2;
    ll v1 = query(rt->l, l, r, nst, md);
    ll v2 = query(rt->r, l, r, md+1, nen);
    return v1+v2;
}


int main() {
    FAST;
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> x[0][i]  >> x[1][i] >>  y[0][i]>>a[i] >> b[i] >> y[1][i];
        x[0][i]++;
        x[1][i]++;
        addy[1].pb({i, y[0][i]});
        addy[x[0][i]+1].pb({i,-y[0][i]});
        addy[x[1][i]+1].pb({i,y[1][i]});
        adda[x[0][i]+1].pb({i,a[i]});
        adda[x[1][i]+1].pb({i,-a[i]});
        addy[x[0][i]+1].pb({i,b[i]});
        addy[x[1][i]+1].pb({i,-b[i]});
    }
    fixes[0]=emp;
    as[0]=emp;
    for(int i=1;i<=2e5+2;i++){
        fixes[i]=new node(fixes[i-1]->sum, fixes[i-1]->l, fixes[i-1]->r);
        for(auto u:addy[i]){
            fixes[i]=ins(fixes[i],u.fi, u.se);
        }
        as[i]=new node(as[i-1]->sum, as[i-1]->l, as[i-1]->r);
        for(auto u:adda[i]){
            as[i]=ins(as[i],u.fi, u.se);
        }
    }
    cin >> m;
    ll last=0;
    while(m--){
        cin >> l >> r >> xx;
        xx = (last+xx)%(1000000000);
        xx++;
        xx=min(xx, int(2e5)+2);

        ll fix = query(fixes[xx],l, r );
        ll aa = query(as[xx],l,r);
        ll ans = fix + aa*(xx-1);
        cout << ans << endl;
        last=ans;
    }

    return 0;
}
