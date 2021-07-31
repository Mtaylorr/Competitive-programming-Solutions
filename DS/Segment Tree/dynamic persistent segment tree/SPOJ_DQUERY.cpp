//https://www.spoj.com/problems/DQUERY/

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
 
struct node;
int pos[N];
int a[N];
int b[N];
int n;
int q,l,r;
 
 
extern node* empty;
struct node {
    int freq;
    node *l , *r;
    node(){
        freq=0;
        l=r=this;
    }
    node(int f, node *lft=empty, node * rt = empty){
        freq=f;
        l=lft;
        r=rt;
    }
};
 
node * empty = new node;
 
node* ins(node * root, int val, int ns=0, int ne=n){
    if(val<ns  || val>ne)
        return root;
    if(ns==ne)
        return new node(root->freq+1);
    int md = ns+(ne-ns)/2;
    node * nl = ins(root->l, val, ns, md);
    node * nr = ins(root->r, val, md+1, ne);
    return new node(nl->freq+nr->freq, nl, nr);
}
node * roots[N];
 
int query(node *rtst, node *rten , int k, int nst=0, int nen=n){
    if(rtst==empty && rten==empty)
        return 0;
    if(nst>k)
        return 0;
    if(nen<=k)
        return rten->freq-rtst->freq;
    if(nen==nst)
        return 0;
    int md = nst+(nen-nst)/2;
    return query(rtst->l, rten->l, k,nst, md )+ query(rtst->r, rten->r, k,md+1, nen );
 
}
 
 
int main() {
    FAST;
    cin >> n;
    roots[0]=empty;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        b[i]=pos[a[i]];
        pos[a[i]]=i;
        roots[i] = ins(roots[i-1], b[i]);
    }
    cin >> q;
    while(q--){
        cin >> l >> r;
        cout << query(roots[l-1], roots[r],l-1) << endl;
    }
    return 0;
} 
