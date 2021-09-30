//https://www.spoj.com/problems/KQUERY/

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e5 + 10;

int a[N];
int n,q,l,r,k;
vector<int> tree[1<<17];

void build(int id=0,int ns=0, int ne=n-1){
    if(ns==ne){
        tree[id]={a[ns]};
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    merge(tree[l].begin(), tree[l].end(),
        tree[r].begin(), tree[r].end(),
        inserter(tree[id], tree[id].begin()));
}

int query(int qs, int qe, int qv, int id=0, int ns=0, int ne=n-1){
    if(ns>qe || ne<qs)
        return 0;
    if(qs<=ns&& qe>=ne){
        int p = upper_bound(tree[id].begin(), tree[id].end(), qv) - tree[id].begin();
        return tree[id].size()-p;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return query(qs, qe, qv,l, ns, md) + query(qs, qe, qv, r, md+1, ne);
}


int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    build();
    scanf("%d",&q);
    while(q--){
        scanf("%d%d%d",&l,&r,&k);
        printf("%d\n", query(--l,--r,k));
    }
    return 0;
}

