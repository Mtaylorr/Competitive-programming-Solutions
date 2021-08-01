//https://codeforces.com/contest/786/problem/C
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

int a[N];
int n;
int pos[N];
struct node;


extern node* emp;
struct node {
    int freq;
    node *l , *r;
    node(){
        freq=0;
        l=r=this;
    }
    node(int f, node *lft=emp, node * rt = emp){
        freq=f;
        l=lft;
        r=rt;
    }
};

node * emp = new node;
node* ins(node * root, int val, int addvalue, int ns=1, int ne=n+1){
    if(val<ns  || val>ne)
        return root;
    if(ns==ne)
        return new node(root->freq+addvalue);
    int md = ns+(ne-ns)/2;
    node * nl = ins(root->l, val,addvalue,  ns, md);
    node * nr = ins(root->r, val, addvalue,md+1, ne);
    return new node(nl->freq+nr->freq, nl, nr);
}
node* roots[N];

int query(node *rtst , int k, int nst=1, int nen=n+1){
    if(nst==nen)
        return nst;
    int lsz = rtst->l->freq;
    int md = nst + (nen-nst)/2;
    if(lsz>=k)
        return query(rtst->l, k, nst, md);

    return query(rtst->r, k-lsz, md+1, nen );
}

int solve(int k){
    int res=0;
    int b = 1;
    int r;
    while(b<=n){
        res++;
        r = query(roots[b],k+1);
        b=r;
    }
    return res;
}


int main() {
    scanf("%d",&n);
    roots[0]=emp;
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
    }
    roots[n+1]=emp;
    for(int i=n;i>=1;i--){
        int lastpos = pos[a[i]];
        int x = a[i];
        pos[x]=i;
        roots[i]=ins(roots[i+1],i, 1);
        if(lastpos!=0){
            roots[i]=ins(roots[i],lastpos, -1);
        }
    }
    for(int i=1;i<=n;i++){
        printf("%d ", solve(i));
    }

    return 0;
}
