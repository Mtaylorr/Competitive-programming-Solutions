//https://codeforces.com/problemset/problem/1516/D
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 1e9 + 7 ;

int n,q;
int a[N],l[N],r[N];
int ub[N], lb[N];
int ans[N];
set<int> tmp;
set<int> cur;
vector<int> queries;

struct node;
extern node * emp;


struct node{
    int f;
    node*l,*r;
    node(){
        f=0;
        l=r=this;
    }
    node(int _f, node*_l=emp , node *_r=emp){
        f=_f;
        l=_l;
        r=_r;
    }
};

node * ins(node * rt , int v, int ns=1, int ne=n){
    if(rt==emp){
        rt = new node(0);
    }
    if(ns>v || ne<v)
        return rt;
    if(ns==ne){
        return new node(rt->f+1, rt->l, rt->r);
    }
    int md = ns+(ne-ns)/2;
    node *_l = ins(rt->l, v, ns, md);
    node *_r = ins(rt->r, v, md+1,ne);
    return new node(_l->f+_r->f, _l, _r);
}

int query(node *rt , int qs, int qe, int ns=1, int ne=n){
    if(rt==emp)
        return 0;
    if(qs<=ns && qe>=ne)
        return rt->f;
    if(qs>ne || qe<ns)
        return 0;
    int md = ns+(ne-ns)/2;
    return query(rt->l, qs, qe, ns, md) + query(rt->r, qs, qe, md+1,ne);
}

node* emp = new node();

node * roots[N];

bool cmp(int a, int b){
    return r[a]<r[b];
}

void calc(int x){
    tmp.clear();
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            tmp.insert(i);
            while(x%i==0){
                x/=i;
            }
        }
    }
    if(x>1){
        tmp.insert(x);
    }
}

bool notvalid(){
    for(auto u:tmp){
        if(cur.count(u))
            return 1;
    }
    return 0;
}
void add(){
    for(auto u:tmp){
        cur.insert(u);
    }
}

void rem(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            cur.erase(i);
            while(x%i==0){
                x/=i;
            }
        }
    }
    if(x>1){
        cur.erase(x);
    }
}

int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&q);

    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int j=1;
    for(int i=1;i<=n;i++){
        calc(a[i]);
        while(notvalid()){
            rem(a[j]);
            j++;
        }
        lb[i]=j;
        add();
    }
    for(int i=0;i<q;i++){
        scanf("%d%d",&l[i],&r[i]);
        queries.pb(i);
    }
    sort(queries.begin(), queries.end(),cmp);
    roots[0]=emp;
    int curr=0;
    for(auto i:queries){
        int qs = l[i];
        int qe = r[i];
        while(curr<qe){
            curr++;
            roots[curr]=ins(roots[lb[curr]-1],curr);
        }
        ans[i]=query(roots[qe], qs, qe);
    }
    for(int i=0;i<q;i++){
        cout << ans[i] << endl;
    }
    return 0;
}
