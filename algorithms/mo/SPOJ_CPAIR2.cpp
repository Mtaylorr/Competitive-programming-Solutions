//https://www.spoj.com/problems/CPAIR2/
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
typedef long long ll;

const int N = int(1e5)+5;

int n, a[N], q,k;
int  qs[N], qe[N], qi[N], s, e;
ll qa[N];
ll cnt;
int tree[N];
int freq[N];

void upd(int x, int v){
    for(;x<=1e5;x+=(x&(-x)))
        tree[x]+=v;
}

int get(int x){
    int res=0;
    for(;x;x-=(x)&(-x)){
        res+=tree[x];
    }
    return res;
}

int getrange(int l, int r){
    if(l>r)
        return 0;
    return get(r)-get(l-1);
}

void add(int val){
    cnt+=getrange(1, val-k);
    cnt+=getrange(val+k, (int)1e5);
    upd(val,1);
}


void rem(int val){
    cnt-=getrange(1, val-k);
    cnt-=getrange(val+k, (int)1e5);
    upd(val,-1);

}

void update(int cur){
    while(e<qe[cur]){
        add(a[++e]);
    }
    while(s>qs[cur]){
        add(a[--s]);
    }
    while(e>qe[cur]){
        rem(a[e--]);
    }
    while(s<qs[cur]){
        rem(a[s++]);
    }
}

void mo(){
    int sq = sqrt(n);
    sort(qi, qi+q, [sq](int a, int b){return make_pair(qs[a]/sq,qe[a])<make_pair(qs[b]/sq, qe[b]);});
    s=0;
    e=-1;
    cnt=0;
    for(int i=0;i<q;i++){
        int cur = qi[i];
        update(cur);
        qa[cur]=cnt;
    }
}

int main(){
    scanf("%d%d%d",&n,&q,&k);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    for(int i=0;i<q;i++){
        scanf("%d%d" , &qs[i],&qe[i]);
        qs[i]--;
        qe[i]--;
        qi[i]=i;
    }
    mo();
    for(int i=0;i<q;i++){
        printf("%lld\n",qa[i]);
    }
    return 0;
}
