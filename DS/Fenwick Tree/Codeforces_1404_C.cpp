//https://codeforces.com/problemset/problem/1404/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 3e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;

int n,q;
int a[N];
int l[N],r[N];
vector<int> qu[N];
int ans[N];
int tree[N];

void upd(int x, int v){
    for(;x<=n;x+=(x)&(-x)){
        tree[x]+=v;
    }
}

int get(int x){
    int rs=0;
    for(;x;x-=(x)&(-x)){
        rs+=tree[x];
    }
    return rs;
}

int query(int l, int r){
    return get(r)-get(l-1);
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]=a[i]-(i);
    }
    for(int i=0;i<q;i++){
        cin >> l[i] >> r[i];
        l[i]++;
        r[i]=n-r[i];
        qu[r[i]].pb(i);
    }
    for(int i=1;i<=n;i++){
        if(a[i]==0){
            upd(i, 1);
        }else if(a[i]<0){
            int lf= 0;
            int rg=i-1;
            while(lf<rg){
                int md  =(lf+rg+1)/2;
                int x = query(md, i-1);
                if(x+a[i]>=0){
                    lf=md;
                }else{
                    rg=md-1;
                }
            }
            if(lf>0){
                upd(lf, 1);
            }
        }
        for(auto v:qu[i]){
            ans[v]=query(l[v], i);
        }
    }
    for(int i=0;i<q;i++){
        cout << ans[i] << "\n";
    }
    return 0;

}
