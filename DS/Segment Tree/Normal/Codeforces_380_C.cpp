//https://codeforces.com/problemset/problem/380/C

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 2;

struct node{
    int l,r;
    int sm=0;
    node(){
        l=r=0;
    }
    node(int s,int lf, int rg){
        sm=s;
        l=lf;
        r=rg;
    }
};

string a;
int n,q,l,r;
node tree[4*N];
char t;

node mrg(node &x, node& y){
    int news = x.sm+y.sm;
    news += min(x.r,y.l);
    return node(news,x.l + max(0, y.l-x.r), y.r + max(0, x.r-y.l));
}

void build(int id=0,int ns = 0, int ne = n-1){
    if(ns==ne){
        tree[id] = node(0,a[ns]==')', a[ns]=='(');
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
        return node(0,0,0);
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



int x;
int main()
{
    ios::sync_with_stdio(0);
    cin >> a;
    n=a.size();
    build();
    cin >> q;
    while(q--){
        cin >> l >> r;
        cout << 2*query(--l,--r).sm << endl;
    }


    return 0;
}
