//https://codeforces.com/contest/52/problem/C
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;

typedef long long ll;

ll tree[4*N],lazy[4*N];
int n;
int a[N];

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        tree[id]=a[ns];
        return ;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l, ns, md);
    build(r, md+1, ne);
    tree[id]=min(tree[l],tree[r]);
}

void unlazy(int id , int ns , int ne){
    tree[id]+=lazy[id];
    if(ns!=ne){
        int l = 2*id+1;
        int r = l+1;
        lazy[l]+=lazy[id];
        lazy[r]+=lazy[id];
    }
    lazy[id]=0;
}

void upd(int qs, int qe, ll v, int id=0, int ns=0, int ne=n-1){
    unlazy(id, ns, ne);
    if(ns>qe || ne<qs)
        return ;
    if(qs<=ns && qe>=ne){
        lazy[id]+=v;
        unlazy(id, ns, ne);
        return;
    }
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(qs, qe, v,l, ns, md);
    upd(qs, qe, v,r, md+1, ne);
    tree[id]=min(tree[l],tree[r]);
}

ll get(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    unlazy(id, ns, ne);
    if(ns>qe ||ne<qs)
        return 1e18;
    if(qs<=ns && qe>=ne)
        return tree[id];
    int l=2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return min(get(qs, qe, l, ns, md),get(qs, qe, r, md+1, ne));

}

int q,l,r;
ll v;
string s;



int cnt(){
    int res=0;
    for(char c:s)
        res+=(c==' ');
    return res;
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    build();
    scanf("%d",&q);
    cin.ignore();
    while(q--){
        getline(cin, s);
        string temp;
        stringstream ss;

        if(cnt()==2){
            ss<< s;
            ss>> temp;
            l = stoi(temp);

            ss>> temp;
            r = stoi(temp);

            ss>> temp;
            v = stoi(temp);
            if(l<=r){
                upd(l, r,v);
            }else{
                upd(l,n-1,v);
                upd(0,r, v);
            }
        }else{
            ss<< s;
            ss>> temp;
            l = stoi(temp);

            ss>> temp;
            r = stoi(temp);
            ll res=1e18;
            if(l<=r){
                res=get(l, r);
            }else{
                res=min(get(l,n-1),get(0,r));
            }
            printf("%lld\n",res);

        }
    }
    return 0;
}
