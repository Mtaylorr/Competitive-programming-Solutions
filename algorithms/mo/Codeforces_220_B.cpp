//https://codeforces.com/contest/220/problem/B
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
typedef long long ll;

const int N = int(2e6)+5;

int n, a[N], q;
int  qs[N], qe[N], qi[N], s, e;
int qa[N];
int cnt;
unordered_map<int,int> freq;


void add(int val){
    cnt-=(freq[val]==val);
    freq[val]++;
    cnt+=(freq[val]==val);
}

void rem(int val){
    cnt-=(freq[val]==val);
    freq[val]--;
    cnt+=(freq[val]==val);
}

void update(const int & cur){
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
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);

    }
    for(int i=0;i<q;i++){
        scanf("%d%d" , &qs[i],&qe[i]);
        qs[i]--;
        qe[i]--;
        qi[i]=i;
    }
    mo();
    for(int i=0;i<q;i++){
        printf("%d\n",qa[i]);
    }
    return 0;
}
