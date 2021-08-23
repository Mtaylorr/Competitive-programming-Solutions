//https://www.spoj.com/problems/BRCKTS/
#include <iostream>

using namespace std;

const int N = 1e5 + 2;

struct node{
    int l,r;
    node(){
        l=r=0;
    }
    node(int lf, int rg){
        l=lf;
        r=rg;
    }
};

string a;
int n,q,l,r;
node tree[4*N];
char t;

node mrg(node &x, node& y){
    return node(x.l + max(0, y.l-x.r), y.r + max(0, x.r-y.l));
}

void build(int id=0,int ns = 0, int ne = n-1){
    if(ns==ne){
        tree[id] = node(a[ns]==')', a[ns]=='(');
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
        return node(0,0); ///infnity
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

void upd(int pos, int id=0, int ns=0,int ne=n-1){
    if(ns>pos || pos>ne){
        return;
    }
    if(ns==ne){
        tree[id]=node(tree[id].r,tree[id].l);
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(pos, l, ns, md);
    upd(pos, r, md+1, ne);
    tree[id] = mrg(tree[l],tree[r]);
}


int x;
int main()
{
    for(int i=0;i<10;i++){
        cin >> n;
        cin >> a;
        build();
        cin >> q;
        cout << "Test " << i+1 << ":\n";
        while(q--){
            cin >> x;
            if(x){
                upd(--x);
            }else{
                if(tree[0].l==0 && tree[0].r==0){
                    cout << "YES\n";
                }else{
                    cout << "NO\n";
                }
            }
        }
    }

    return 0;
}
