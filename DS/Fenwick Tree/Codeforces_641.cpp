https://codeforces.com/contest/641/problem/E
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
typedef long long ll;

const int N = int(3e5)+5;

int n;
int a[N], t[N], x[N];
int sz[N];
set<int> ss;
set<int> sl[N];
unordered_map<int,int> codea;
unordered_map<int,int> codet[N];
vector<int> tree[N];


void upd(int x, int t, int v){
    for(;t<=sz[x];t+=(t)&(-t)){
        tree[x][t]+=v;
    }
}

int get(int x, int t){
    int res=0;
    for(;t;t-=(t)&(-t)){
        res+=tree[x][t];
    }
    return res;
}

void add(int x, int t){
    upd(x, t, 1);
}

void rem(int x, int t){
    upd(x, t,-1);
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d%d%d",&a[i],&t[i],&x[i]);
        ss.insert(x[i]);
    }
    int mxa = 0;
    for(auto u:ss){
        codea[u]=mxa++;
    }
    for(int i=0;i<n;i++){
        x[i]=codea[x[i]];
        sl[x[i]].insert(t[i]);
    }
    for(int i=0;i<mxa;i++){
        for(auto u: sl[i]){
            codet[i][u]=++sz[i];
        }
        tree[i].resize(sz[i]+2);
    }
    for(int i=0;i<n;i++){
        t[i] = codet[x[i]][t[i]];
    }
    codea.clear();
    ss.clear();
    for(int i=0;i<n;i++){
        codet[i].clear();
        sl[i].clear();
    }

    for(int i=0;i<n;i++){
        if(a[i]==1){
            add(x[i],t[i]);
        }else if(a[i]==2){
            rem(x[i],t[i]);
        }else{
            printf("%d\n",get(x[i],t[i]));
        }
    }



    return 0;
}
