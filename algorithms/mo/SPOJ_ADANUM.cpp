//https://www.spoj.com/problems/ADANUM/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
typedef long long ll;

const int N = int(2e5)+5;

int n, a[N], q;
int  qs[N], qe[N], qi[N], s, e;
ll qa[N];
ll cnt;
int freq[N];
int cntfreq[N];

void add(int val){
    ll x = cntfreq[freq[val]+1];
    cnt-=freq[val]*(x+1);
    freq[val]++;
    cntfreq[freq[val]]++;
    cnt+=freq[val]*(x+1);
}

void rem(int val){
    ll x = cntfreq[freq[val]];
    cnt-=freq[val]*(x);
    cntfreq[freq[val]]--;
    freq[val]--;
    cnt+=freq[val]*(x);
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
set<int> distincts;
map<int,int> code;

int main(){
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        distincts.insert(a[i]);
    }
    int cn=0;
    for(auto u:distincts){
        code[u]=cn++;
    }
    for(int i=0;i<n;i++){
        a[i]=code[a[i]];
    }
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
