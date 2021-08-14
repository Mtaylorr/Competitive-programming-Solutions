//https://www.spoj.com/problems/XXXXXXXX/
#include <bits/stdc++.h>

using namespace std;


typedef long long ll;

const int N = int(3e5)+5;

int n, a[N], q;
int  qs[N], qe[N], qi[N], s, e, qui[N], qt[N], quprv[N], qunew[N];
int ti=0;
int x,y;
int total;
ll vals[N];
ll qa[N];
int freq[N];
ll sm;

void add(int val){
    if(!freq[val]++)
        sm+=vals[val];
}

void rem(int val){
    if(!--freq[val])
        sm-=vals[val];
}

void update(const int & cur){
    while(ti<qt[cur]){
        ti++;
        if(qui[ti]>=s && qui[ti]<=e){
            rem(quprv[ti]);
            add(qunew[ti]);
        }
        a[qui[ti]]=qunew[ti];
    }
    while(ti>qt[cur]){
        if(qui[ti]>=s && qui[ti]<=e){
            rem(qunew[ti]);
            add(quprv[ti]);
        }
        a[qui[ti]]=quprv[ti];
        ti--;
    }
    while(e<qe[cur])
        add(a[++e]);

    while(s>qs[cur])
        add(a[--s]);

    while(e>qe[cur])
        rem(a[e--]);

    while(s<qs[cur])
        rem(a[s++]);


}

void mo(){
    int sq = ceil(pow(1LL * n, 2.0/3));
    sort(qi, qi+total, [sq](int a, int b){return make_pair(make_pair(qs[a]/sq,qe[a]/sq),qt[a])<make_pair(make_pair(qs[b]/sq,qe[b]/sq),qt[b]);});
    s=0;
    e=-1;
    for(int i=0;i<total;i++){
        int curq = qi[i];
        update(curq);
        qa[curq]=sm;
    }
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        vals[i]=a[i];
    }
    scanf("%d",&q);
    char c;

    for(int i=0;i<q;i++){
        scanf(" %c %d %d",&c, &x,&y);
        if(c=='U'){
            vals[n+ti]=y;
            ti++;
            x--;
            quprv[ti]=a[x];
            qunew[ti]=y;
            qui[ti]=x;
            a[x]=y;
        }else{
            x--;
            y--;
            qs[total]=x;
            qe[total]=y;
            qi[total]=total;
            qt[total]=ti;
            total++;
        }
    }
    sort(vals, vals+n+ti);
    int dis = unique(vals, vals+n+ti)-vals;
    for(int i=0;i<n;i++){
        a[i]=lower_bound(vals, vals+dis, a[i])-vals;
    }
    for(int i=1;i<=ti;i++){
        quprv[i] = lower_bound(vals, vals+dis, quprv[i])-vals;
        qunew[i] = lower_bound(vals, vals+dis, qunew[i])-vals;
    }
    mo();
    for(int i=0;i<total;i++){
        printf("%lld\n",qa[i]);
    }
    return 0;
}
