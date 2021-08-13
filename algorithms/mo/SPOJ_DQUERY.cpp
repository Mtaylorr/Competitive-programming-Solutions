//https://www.spoj.com/problems/DQUERY/
#include <bits/stdc++.h>

using namespace std;

const int N = int(1e6)+5;

int n, a[N], q;
int  qs[N], qe[N], qi[N], s, e, qa[N];
int cnt;
int freq[N];

void add(int val){
    if(freq[val]==0)
        cnt++;
    freq[val]++;
}

void rem(int val){
    freq[val]--;
    if(freq[val]==0)
        cnt--;
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

int main()
{
    freopen("input.txt", "r", stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&q);
    for(int i=0;i<q;i++){
        qi[i]=i;
        scanf("%d%d",&qs[i], &qe[i]);
        qs[i]--;
        qe[i]--;
    }
    mo();
    for(int i=0;i<q;i++){
        printf("%d\n",qa[i]);
    }


    return 0;
}

