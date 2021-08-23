//https://www.spoj.com/problems/KGSS/
#include <iostream>
 
using namespace std;
 
const int N = 1e5 + 2;
 
struct node{
    int sum;
    int mx;
    node(){
        sum=0;
        mx=0;
    }
    node(int s, int m){
        sum=s;
        mx=m;
    }
};
 
int a[N];
int n,q,l,r;
node tree[4*N];
char t;
 
node mrg(node &x, node& y){
    return node(max(x.mx+y.mx ,max(x.sum, y.sum)),max(x.mx, y.mx) );
}
 
void build(int id=0,int ns = 0, int ne = n-1){
    if(ns==ne){
        tree[id] = node(a[ns], a[ns]);
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    tree[id] = mrg(tree[l],tree[r]);
}
 
 
node query(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    if(ns>qe || qs>ne){
        return node(-1e7,-1e7); ///infnity
    }
    if(qs<=ns && qe>=ne){
        return tree[id];
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    node ndl = query(qs, qe, l, ns, md);
    node ndr = query(qs, qe,r, md+1,ne);
    return mrg(ndl,ndr );
}
 
void upd(int pos , int val , int id=0, int ns=0,int ne=n-1){
    if(ns>pos || pos>ne){
        return;
    }
    if(ns==ne){
        tree[id]=node(val, val);
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(pos, val,l, ns, md);
    upd(pos, val, r, md+1, ne);
    tree[id] = mrg(tree[l],tree[r]);
}
 
 
 
int main()
{
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    build();
    cin >> q;
    while(q--){
        cin >> t >> l >> r;
        switch (t){
        case 'U': // upd l=x, r=y;
            upd(--l,r);
            break;
        case 'Q' :
            node nd = query(--l,--r);
            cout << nd.sum << endl;
            break;
        }
    }
    return 0;
}
