// https://codeforces.com/problemset/problem/813/E
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
int n,k;
int q,l,r;
vector<int> pos[N];
vector<int> seg[1<<18];

void build(int ind=0, int ns=1 , int ne=n){
    if(ns==ne){
        seg[ind].push_back(a[ns]);
        return ;
    }
    int l  = 2*ind+1;
    int r = l+1;
    int md = (ns) + (ne-ns)/2;
    build(l,ns,md);
    build(r,md+1,ne);
    merge(seg[l].begin(),seg[l].end(),
          seg[r].begin(),seg[r].end(),
          inserter(seg[ind], seg[ind].begin()));
}
int query(int qst, int qen , int qval, int ind=0, int ns=1, int ne=n ){
    if(ns>qen || ne<qst)
        return 0;
    if(qst<=ns && qen>=ne){
        return lower_bound(seg[ind].begin(),seg[ind].end(),qval+1)-seg[ind].begin();
    }
    int l  = 2*ind+1;
    int r = l+1;
    int md = (ns) + (ne-ns)/2;
    return query(qst, qen, qval, l, ns, md) + query(qst, qen, qval, r, md+1,ne);
}


int main() {
    FAST;
    cin >> n >> k ;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        pos[a[i]].pb(i);
        if(pos[a[i]].size()>k){
            a[i]=pos[a[i]][pos[a[i]].size()-k-1];
        }else{
            a[i]=0;
        }
    }
    build();
    cin >>q;
    int last=0;
    for(int i=0;i<q;i++){
        cin >> l >> r;
        l=(l+last)%n;
        r=(r+last)%n;
        if(l>r)
            swap(l,r);
        l++;r++;
        last = query(l,r,l-1);
        cout <<  last<< endl;
    }
    return 0;
}
