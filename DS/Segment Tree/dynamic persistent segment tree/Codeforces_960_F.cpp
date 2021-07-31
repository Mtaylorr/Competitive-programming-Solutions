//https://codeforces.com/problemset/problem/960/F
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
int a,b,w;
struct node;
extern node* emp;
struct node{
    ll mx;
    node *l , *r;
    node(){
        mx = 0;
        l=this;
        r=this;
    }
    node(ll ma  ,  node *l = emp , node *r=emp){
        mx=ma;
        this->l=l;
        this->r=r;
    }
};
node* emp = new node;

node * ins(node *root,ll w, ll val , ll nst=-2,ll nen=1e9){

    if(w>nen || w<nst){
        return root;
    }
    if(nst==nen){
        return new node(val);
    }
    int md = nst+(nen-nst)/2;
    node * ln = ins(root->l,w,val, nst,md );
    node * rn = ins(root->r, w,val, md+1, nen);
    return new node(max(ln->mx, rn->mx),ln, rn);
}
node* roots[N];

ll query(node * rt, ll k, ll nst = -2, ll nen=1e9){
    if(nst>k)
        return 0;
    if(nen<=k){
        return rt->mx;
    }
    int md = nst+(nen-nst)/2;
    ll v1 = query(rt->l, k,nst, md );
    ll v2 = query(rt->r, k,md+1, nen);
    return max(v1,v2);
}


int main() {
    FAST;
    cin >> n >> m;
    int ans=0;
    for(int i=1;i<=n;i++){
        roots[i]=emp;
    }
    for(int i=0;i<m;i++){
        cin >> a >> b >> w;
        int v1 = query(roots[a],w-1);
        ans=max(ans,v1+1);
        roots[b] = ins(roots[b],w,1+v1);
    }
    cout << ans << endl;


    return 0;
}
