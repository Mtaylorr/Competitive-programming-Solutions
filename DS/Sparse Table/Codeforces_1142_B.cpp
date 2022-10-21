//https://codeforces.com/problemset/problem/1142/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M = 1000 + 5, E = 1e6 + 5;
const int MOD =998244353 ;
const double eps = 1e-7;

int n,m,q;
int p[N];
int a[N];
int spt[N][30];
int pos[N];
deque<int> dq[N];
int val[N];
int L;

typedef int dtype;
dtype OUT_OF_RANGE = 1e9;
dtype tree[4 * N];

void mrg(dtype &a,dtype & l, dtype &r){
    a=min(l,r);
}

void build(int id = 0, int ns = 0, int ne = m - 1) {
    if (ns == ne) {
        tree[id] = val[ns];
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    mrg(tree[id],tree[l],tree[r]);
}

dtype query(int qs, int qe, int id = 0, int ns = 0, int ne = m - 1) {
    if (ns > qe || ne < qs)
        return OUT_OF_RANGE;
    if (qs <= ns && qe >= ne) {
        return tree[id];
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

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> q;
    for(int i=0;i<n;i++){
        cin >> p[i];
        p[i]--;
        pos[p[i]]=i;
    }
    for(int i=0;i<m;i++){
        cin >> a[i];
        a[i]--;
        dq[a[i]].pb(i);
    }
    for(int i=0;i<m;i++){
        dq[a[i]].pop_front();
        dq[a[i]].push_back(i);
        int x = p[(pos[a[i]]+1)%n];
        if(dq[x].size()){
            int nx = dq[x].front();
            if(nx>i){
                spt[i][0]=nx-i;
            }else{
                spt[i][0]=m+1;
            }
        }else{
            spt[i][0]=m+1;
        }
    }
    for(int l=1;(1<<l)<=m;l++){
        L=l;
        for(int i=0;i<m;i++){
            spt[i][l]=spt[i][l-1]+spt[(i+spt[i][l-1])%m][l-1];
            if(spt[i][l]>m){
                spt[i][l]=m+1;
            }
        }

    }
    for(int i=0;i<m;i++){
        int u = n-1;
        int cur = (1<<L);
        int sz = 0;
        int st=i;
        for(int j=L;j>=0;j--){
            if(u>=cur){
                sz+=spt[st][j];
                st+=spt[st][j];
                u-=cur;
                st%=m;
                if(sz>m){
                    sz=m+1;
                }
            }
            cur/=2;
        }
        if(u){
            val[i]=i+m+1;
        }else{
            val[i]=i+sz;
        }

    }

    build();
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        if(query(l,r)<=r){
            cout << "1";
        }else{
            cout << "0";
        }
    }

    return 0;

}
