//https://codeforces.com/problemset/problem/718/C
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5 + 5;
const int MOD = 1e9 + 7;

vector<vector<int> > tmp;
int add(int x, int y) {
    return (x % MOD + 0ll + y % MOD) % MOD;
}

int mul(int x, int y) {
    return ((x % MOD) * 1ll * (y % MOD)) % MOD;
}

void mul(vector<vector<int> > &rs,vector<vector<int> > &a, vector<vector<int> > &b) {
    tmp.resize(2);
    for (int i = 0; i < 2; i++) {
        tmp[i].assign(2, 0);
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                tmp[i][j] = (tmp[i][j] +  (a[i][k]*1ll*b[k][j])%MOD)%MOD;
            }
        }
    }
    rs.resize(2);
    for (int i = 0; i < 2; i++) {
        rs[i].assign(2, 0);
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            rs[i][j]=tmp[i][j];
        }
    }
}

int n, m, a[N];
vector<vector<int> > lazy[4 * N];
bool hasLazy[4*N];
vector<int> tree[4 * N];
vector<vector<int> > po[60];
vector<vector<int> > A;
vector<vector<int> > curV;


void init(vector<vector<int> > &a){
    a.resize(2);
    for (int i = 0; i < 2; i++) {
        a[i].assign(2, 0);
    }
    a[0][0]=a[1][1]=1;
    a[0][1]=a[1][0]=0;

}


vector<vector<int> > getA(vector<vector<int> > &rs, ll p) {
    init(rs);
    int b = 0;
    while (p) {
        if (p % 2) {
            mul(rs,rs, po[b]);
        }
        p /= 2;
        b++;
    }
    return rs;
}


void build(int id = 0, int ns = 0, int ne = n - 1) {
    init(lazy[id]);
    if (ns == ne) {
        vector<vector<int> > rs;
        getA(rs,a[ns]);
        tree[id]=rs[0];

        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    tree[id].resize(2);
    for (int i = 0; i < 2; i++)
        tree[id][i] = (tree[l][i]+ tree[r][i])%MOD;
}

void unlazy(int id, int ns, int ne){
    if(!hasLazy[id])
        return ;
    vector<int> tmp(2);
    for(int i=0;i<2;i++)
        tmp[i]=((lazy[id][i][0]*1ll*tree[id][0])%MOD+ (lazy[id][i][1]*1ll*tree[id][1])%MOD)%MOD;
    tree[id]=tmp;
    if(ns!=ne){
        int l = 2*id+1;
        int r = l+1;
        mul(lazy[l], lazy[l], lazy[id]);
        mul(lazy[r], lazy[r], lazy[id]);
        hasLazy[l]=hasLazy[r]=1;
    }
    init(lazy[id]);
    hasLazy[id]=0;

}

void upd(int qs, int qe,  int id=0, int ns=0, int ne=n-1){
    unlazy(id, ns, ne);
    if(qs>ne || qe<ns)
        return ;
    if(qs<=ns && qe>=ne){

        mul(lazy[id], lazy[id], curV);

        hasLazy[id]=1;
        unlazy(id , ns, ne);
        return ;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    upd(qs, qe, l, ns, md);
    upd(qs, qe, r, md+1, ne);
    tree[id].resize(2);
    for (int i = 0; i < 2; i++)
        tree[id][i] =(tree[l][i]+ tree[r][i])%MOD;
}

int query(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    unlazy(id , ns, ne);
    if(qs>ne || qe<ns)
        return 0;
    if(qs<=ns && qe>=ne){
        return tree[id][1];
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    return (query(qs, qe, l, ns, md)+ query(qs, qe, r, md+1,ne))%MOD;
}
int t,l,r,x;
int main() {
    //ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    A.resize(2);
    for (int i = 0; i < 2; i++) {
        A[i].assign(2, 0);
    }
    A[0][0] = 1;
    A[1][0] = 1;
    A[0][1] = 1;
    po[0] = A;
    for (int i = 1; i <= 50; i++) {
        mul(po[i],po[i - 1], po[i - 1]);
    }
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    build();

    while(m--){
        scanf("%d",&t);
        if(t==1){
            scanf("%d%d%d",&l,&r,&x);
            getA(curV,x);
            upd(--l,--r);
        }else{
            scanf("%d%d",&l,&r);
            printf("%d\n",query(--l,--r));
        }
    }

    return 0;

}
