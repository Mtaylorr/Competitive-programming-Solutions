//https://codeforces.com/problemset/problem/145/E

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e6 + 5, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

int n,m;
string s;

struct node{
    int four,seven,dec,inc;
    node(){
        four=seven=dec=inc=0;
    }
    node(int f, int s, int d, int i){
        four=f;
        seven=s;
        dec=d;
        inc=i;
    }

    void print(){
        cout << four << " " << seven << " "<< dec << " " << inc << endl;
    }
};

typedef node dtype;
dtype OUT_OF_RANGE = {0,0,0,0};
dtype tree[4 * N];
int lazy[4*N];
int NULL_Lazy = 0;

void mrg(dtype &a,dtype & l, dtype &r){
    a.four = l.four+r.four;
    a.seven = l.seven+r.seven;
    a.inc = max(l.inc + r.seven, l.four+r.inc);
    a.dec = max(l.dec + r.four, l.seven+r.dec);
}
bool has_lazy(int id){ return lazy[id]!=NULL_Lazy; }

void rem_lazy(int id){ lazy[id]=NULL_Lazy;}

void unlazy(int id, int ns, int ne){
    if(lazy[id]%2){
        swap(tree[id].four, tree[id].seven);
        swap(tree[id].dec, tree[id].inc);
    }

}

void propagate(int id, int chld){lazy[chld]+=lazy[id];}

void upd_lazy(int id ,int ns, int ne){
    if(has_lazy(id)){
        unlazy(id, ns, ne);
        if(ns!=ne){
            int l = 2*id+1;
            int r = 2*id+2;
            propagate(id, l);
            propagate(id, r);
        }
        rem_lazy(id);
    }
}

void build(int id = 0, int ns = 0, int ne = n - 1) {
    lazy[id]=NULL_Lazy;
    if (ns == ne) {
        tree[id]={s[ns]=='4', s[ns]=='7', 1,1};
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    mrg(tree[id],tree[l],tree[r]);
}

void upd(int qs, int qe, int v, int id = 0, int ns = 0, int ne = n - 1) {
    upd_lazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return;
    }
    if(qs<=ns && qe>=ne){
        lazy[id]+=v;
        lazy[id]%=2;

        upd_lazy(id, ns, ne);
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    upd(qs, qe, v, l, ns, md);
    upd(qs, qe, v, r, md+1, ne);
    mrg(tree[id],tree[l],tree[r]);
}


dtype query(int qs, int qe, int id = 0, int ns = 0, int ne = n - 1) {
    upd_lazy(id, ns, ne);
    if(qs>ne || qe<ns){
        return OUT_OF_RANGE;
    }
    if(qs<=ns && qe>=ne){
        return  tree[id];
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    dtype la = query(qs, qe, l, ns, md);
    dtype ra = query(qs, qe, r, md + 1, ne);
    dtype ca;
    mrg(ca, la, ra);
    return ca;
}
string tmp;

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    cin >> s;
    build();
    for(int i=0;i<m;i++){
        cin >> tmp;
        if(tmp[0]=='c'){
            cout << tree[0].inc<< "\n";
        }else{
            int l,r;
            cin>> l >> r;
            l--;r--;
            upd(l,r,1);
        }
    }

    return 0;

}
