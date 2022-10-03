//https://codeforces.com/contest/755/problem/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e6 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 998244353;
const double eps = 1e-7;

int tree[N];
int n,k;

void upd(int x){
    x++;
    for(;x<=n;x+=(x)&(-x)){
        tree[x]++;
    }
}
int get(int x){
    int rs=0;
    for(;x;x-=(x)&(-x)){
        rs+=tree[x];
    }
    return rs;
}

int get_range(int l, int r){
    if(l>r)
        return 0;
    l++;r++;
    return get(r)-get(l-1);
}
ll ans=1;
bool vis[N];

int get_range_ans(int l, int r){
    if(l<0){
        return get_range((l+n)%n, n-1) + get_range_ans(0,r);
    }
    if(r>=n){
        return get_range_ans(l,n-1)+get_range(0, r%n);
    }
    return get_range(l,r);
}

int get_bef(int c){
    int ln=k;
    if(2*k>n){
        ln =n-k;
    }
    int l = c-ln+1;
    int r = c+ln-1;
    int rs = get_range_ans(l,r);
    return rs;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    int c=0;
    for(int i=0;i<n;i++){
        if(vis[c]){
            cout << ans << " ";
        }else{
            vis[c]=1;
            int rs=get_bef(c);
            rs++;
            ans+=rs;
            cout << ans << " ";
            upd(c);
            c+=k;
            c%=n;
        }
    }
    return 0;

}
