#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 2e6+5;

int tree[N];
int qi[N], qs[N], qe[N], qx[N], qy[N], qans[N];
int a[N];
int l,r;
int n,q;
int occ[N];

void upd(int x,int val){
    for(;x<N;x+=(x)&(-x)){
        tree[x]^=val;
    }
}
int get(int x){
    if(x<0)
        return 0;
    int res=0;
    for(;x;x-=(x)&(-x))
        res=res^tree[x];
    return res;
}

void add(int x){
    upd(x, occ[x]);
    occ[x]++;
    upd(x,occ[x]);
}
void rem(int x){
    upd(x, occ[x]);
    occ[x]--;
    upd(x,occ[x]);
}

void update(int cur){
    while(r<qe[cur])
        add(a[++r]);

    while(l>qs[cur])
        add(a[--l]);

    while(r>qe[cur])
        rem(a[r--]);

    while(l<qs[cur])
        rem(a[l++]);
}

void mo(){
    int B = sqrt(n);
    sort(qi, qi+q, [B](int a, int b){return make_pair(qs[a]/B,qe[a])<make_pair(qs[b]/B, qe[b]);});
    l=0;
    r=-1;
    for(int i=0;i<q;i++){
        int cur =qi[i];
        update(cur);
        int yy = get(qy[cur]);
        int xx = get(qx[cur]-1);
        qans[cur]=yy^xx;
    }
}

int main(){
    //freopen("input.txt", "r", stdin);
    freopen("hypo.in", "r", stdin);
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }

    for(int i=0;i<q;i++){
        scanf("%d%d%d%d",&qs[i],&qe[i], &qx[i], &qy[i]);
        qs[i]--;
        qe[i]--;
        qi[i]=i;
    }
    mo();
    for(int i=0;i<q;i++){
        cout << qans[i] << "\n";
    }
    return 0;
}
