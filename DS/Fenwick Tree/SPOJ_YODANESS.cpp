//https://www.spoj.com/problems/YODANESS/
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;

#define fi first
#define se second

typedef long long ll;

int n,t;
string s;
map<string,int> code;
int a[N];
int tree[N];

void upd(int x, int v){
    for(;x<=n;x+=(x)&(-x)){
        tree[x]+=v;
    }
}

int get(int x){
    int res=0;
    for(;x;x-=(x)&(-x)){
        res+=tree[x];
    }
    return res;
}



int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        code.clear();
        for(int i=0;i<n;i++){
            cin >> s;
            code[s]=i+1;
        }
        for(int i=0;i<n;i++){
            cin >> s;
            a[i]=code[s];
        }
        ll res=0;
        for(int i=n-1;i>=0;i--){
            res+=get(a[i]-1);
            upd(a[i],1);
        }
        printf("%lld\n",res);
        for(int i=0;i<n;i++){
            upd(a[i],-1);
        }
    }
    return 0;
}
