//https://codeforces.com/contest/351/problem/D

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
typedef long long ll;

const int N = int(2e5)+5;

int n, a[N], q;
int  qs[N], qe[N], qi[N], s, e;
ll qa[N];
ll cnt;
ll freq[N];
deque<int> dq[N];
int nbdiff[N];
int bads=0;
unordered_map<int,int> diff[N];

void add(int val, int pos){
    if(dq[val].size()==0){
        dq[val].push_back(pos);
        cnt++;
    }else{
        bool chng=false;
        if(pos<dq[val].front()){
            int x =dq[val].front();
            dq[val].push_front(pos);
            int y = nbdiff[val];
            nbdiff[val]+=!diff[val][x-pos]++;
            chng=(y!=nbdiff[val]);
        }else{
            int x = dq[val].back();
            int y = nbdiff[val];
            dq[val].push_back(pos);
            nbdiff[val]+=!diff[val][pos-x]++;
            chng=(y!=nbdiff[val]);
        }
        bads+=(nbdiff[val]==2 && chng);
    }
}

void rem(int val, int pos){
    if(dq[val].size()==1){
        dq[val].pop_back();
        cnt--;
    }else{
        bool chng=false;
        if(pos==dq[val].front()){
            dq[val].pop_front();
            int x =dq[val].front();
            int y = nbdiff[val];
            nbdiff[val]-= !--diff[val][x-pos];
            chng=(y!=nbdiff[val]);
        }else{
            dq[val].pop_back();
            int x = dq[val].back();
            int y = nbdiff[val];
            nbdiff[val]-= !--diff[val][pos-x];
            chng=(y!=nbdiff[val]);
        }
        bads-=(nbdiff[val]==1 && chng);
    }
}

void update(const int & cur){
    while(e<qe[cur]){
        e++;
        add(a[e], e);
    }

    while(s>qs[cur]){
        s--;
        add(a[s], s);
    }

    while(e>qe[cur]){
        rem(a[e],e);
        e--;
    }

    while(s<qs[cur]){
        rem(a[s],s);
        s++;
    }

}

void mo(){
    int sq = sqrt(n);
    //cout << sq << endl;
    sort(qi, qi+q, [sq](int a, int b){return make_pair(qs[a]/sq,((qs[a]/sq) &1 ? -qe[a]:qe[a]))<make_pair(qs[b]/sq, ((qs[b]/sq) &1 ? -qe[b]:qe[b]));});
    s=0;
    e=-1;
    cnt=0;
    for(int i=0;i<q;i++){
        int cur = qi[i];
        update(cur);
        if(bads==cnt){
            qa[cur]=cnt+1;
        }else{
            qa[cur]=cnt;
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);

    }
    scanf("%d",&q);
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
