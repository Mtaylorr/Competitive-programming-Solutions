//https://codeforces.com/problemset/problem/914/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e5 + 5 , E = 2e6 + 5;
const int MOD = 1e9 + 7 ;

int n;
int a[N];
int tree[4*N];
int q,l,r,x,t;

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        tree[id]=a[ns];
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md  =ns+(ne-ns)/2;
    build(l,ns,md);
    build(r, md+1,ne);
    tree[id]=__gcd(tree[l],tree[r]);
}

void upd(int p, int v, int id=0, int ns=0, int ne=n-1){
    if(ns>p || ne<p)
        return ;
    if(ns==ne){
        tree[id]=v;
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md  =ns+(ne-ns)/2;
    upd(p,v,l, ns,md);
    upd(p,v,r,md+1,ne);
    tree[id]=__gcd(tree[l],tree[r]);
}

int getleft(int p,int v, int id=0, int ns=0,int ne=n-1){
    if(ne<p){
        return ne;
    }
    if(tree[id]%v==0){
        return ne;
    }
    if(ns==ne){
        return ns-1;
    }
    int l = 2*id+1;
    int r = l+1;
    int md  =ns+(ne-ns)/2;
    int ans = getleft(p,v,l,ns,md);
    if(ans==md){
        return getleft(p,v,r, md+1,ne);
    }
    return ans;
}

int getright(int p,int v, int id=0, int ns=0,int ne=n-1){
    if(ns>p){
        return ns;
    }
    if(tree[id]%v==0){
        return ns;
    }
    if(ns==ne){
        return ne+1;
    }
    int l = 2*id+1;
    int r = l+1;
    int md  =ns+(ne-ns)/2;
    int ans = getright(p,v,r, md+1,ne);
    if(ans==md+1){
        return getright(p,v,l, ns,md);
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    build();
    cin >> q;
    while(q--){
        cin >> t;
        if(t==1){
            cin >> l >> r >> x;
            l--;r--;
            int lf = getleft(l,x);
            int rg = getright(r,x);
            if(lf>=rg-2){
                cout << "YES\n";
            }else{
                cout << "NO\n";
            }
        }else{
            cin >> l >> x;
            upd(--l,x);
        }
    }
    return 0;

}
