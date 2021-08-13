//https://www.spoj.com/problems/COT/
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

vector<vector<int> > adj;
vector<int> node2ind, ind2node, depth;
int spt[int(2e5)+5][20];
int lg[int(2e5)+5];


int value[N];
int n,m;

struct node;
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

vector<node*> roots, parents;

node* ins(node * root, int val, int ns=INT_MIN, int ne=INT_MAX){
    if(val<ns  || val>ne)
        return root;
    if(ns==ne)
        return new node(root->freq+1);
    int md = ns+(ne-0ll-ns)/2;
    node * nl = ins(root->l, val, ns, md);
    node * nr = ins(root->r, val, md+1, ne);
    return new node(nl->freq+nr->freq, nl, nr);
}


int query(node *rtu, node *rtv, node *rtLCA ,node *rtPLCA, int k, int nst=INT_MIN, int nen=INT_MAX){
    if(nst==nen)
        return nst;
    int lsz = rtu->l->freq + rtv->l->freq - rtLCA->l->freq - rtPLCA->l->freq;
    int md = nst+(nen-0ll-nst)/2;
    if(k<=lsz){
        return query(rtu->l, rtv->l,rtLCA->l , rtPLCA->l,k , nst, md);
    }else
        return query(rtu->r, rtv->r,rtLCA->r, rtPLCA->r, k-lsz, md+1,nen);
}

void init(){
    adj.resize(n+1);
    depth.resize(n+1);
    node2ind.resize(n+1);
    ind2node.clear();
    roots.resize(n+1);
    parents.resize(n+1);
}

void dfs(int u, int dpth=0, node* parent=empty, int p=0){
    node2ind[u]=ind2node.size();
    ind2node.pb(u);
    parents[u]=parent;
    roots[u]=ins(parent, value[u]);
    depth[u]=dpth;
    for(int v:adj[u]){
        if(v==p)
            continue;
        dfs(v, dpth+1, roots[u], u);
        ind2node.pb(u);
    }
}

void buildspt(){
    lg[0]=-1;
    for(int i=0;i<ind2node.size();i++){
        spt[i][0]=i;
        lg[i+1]= lg[i]+ !(i&i+1);
    }
    for(int j=1;(1<<j)<=ind2node.size();j++){
        for(int i=0;i+(1<<j)<=ind2node.size();i++){
            int a = spt[i][j-1];
            int b = spt[i+(1<<(j-1))][j-1];
            spt[i][j] = (depth[ind2node[a]]<depth[ind2node[b]] ? a:b);
        }
    }
}

int SPTMQ(int a , int b){
    int sz = b-a+1;
    int l = lg[sz];
    a = spt[a][l];
    b = spt[b-(1<<l)+1][l];
    return (depth[ind2node[a]]<depth[ind2node[b]] ? a:b);
}

int SPTLCA(int u , int v){
    int a = node2ind[u];
    int b = node2ind[v];
    if(a>b)
        swap(a,b);
    return ind2node[SPTMQ(a,b)];
}



int main() {
    FAST;
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> value[i+1];
    }
    int u,v, k;
    init();
    for(int i=1;i<n;i++){

        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1);
    buildspt();
    while(m--){
        cin >> u >> v >> k;
        int d = SPTLCA(u,v);
        cout << query(roots[u],roots[v], roots[d], parents[d], k) << endl;
    }
    return 0;
}
