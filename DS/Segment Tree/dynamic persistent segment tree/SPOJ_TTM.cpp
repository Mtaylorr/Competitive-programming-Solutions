//https://www.spoj.com/problems/TTM/
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
 
 
ll sum[N];
int n,m;
ll a[N];
char c;
int l, r, d, t;
struct node;
extern node* empty;
struct node{
    ll sum;
    ll lazy;
    node *l , *r;
    node(){
        sum = 0;
        lazy = 0;
        l=this;
        r=this;
    }
    node(ll f  , ll v, node *l = empty , node *r=empty){
        sum=f;
        lazy=v;
        this->l=l;
        this->r=r;
    }
};
node* empty = new node;
 
node * insert(node *root,ll l, ll r,ll val , ll nst=1,ll nen=n){
 
    if(l>nen || r<nst){
        return root;
    }
    if(l<= nst && r>=nen){
        return new node(root->sum+val*(nen-nst+1), root->lazy+val, root->l, root->r);
    }
    int md = nst+(nen-nst)/2;
    node * ln = insert(root->l, l,r,val, nst,md );
    node * rn = insert(root->r, l,r,val , md+1, nen);
    return new node(ln->sum+rn->sum+root->lazy*(nen-nst+1),root->lazy, ln, rn);
}
node* roots[N];
 
ll query(node * rt, ll l , ll r,ll cur=0, ll nst = 1, ll nen=n){
    if(l>nen || r<nst)
        return 0;
    if(l<=nst && r>=nen){
        return (cur)*(nen-nst+1)+rt->sum;
    }
    int md = nst+(nen-nst)/2;
    ll v1 = query(rt->l, l, r, cur+rt->lazy,nst, md );
    ll v2 = query(rt->r, l, r, cur+rt->lazy, md+1, nen);
    return v1+v2;
}
 
 
int main() {
    FAST;
    roots[0]=empty;
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+a[i];
    }
    int cur=0;
    for(int i=0;i<m;i++){
        cin >> c;
        if(c=='C'){
            cin >> l >>  r >> d;
            roots[cur+1] = insert(roots[cur], l,r,d);
            cur++;
        }else if(c=='Q'){
            cin >> l >> r;
            t=cur;
            cout << sum[r]-sum[l-1] + query(roots[t],l,r,0) << endl;
        }else if(c=='H'){
            cin >> l >> r >> t;
            cout << sum[r]-sum[l-1] + query(roots[t],l,r,0) << endl;
        }else{
            cin >> t;
            cur=t;
        }
    }
    return 0;
} 
