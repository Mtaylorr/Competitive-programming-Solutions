//https://codeforces.com/problemset/problem/888/G
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

int n;
int a[N];
unordered_map<int,vector<int> > zero, one;

int trie[30*N][2];
int ndcnt=0;
int po[35];
int curbit=29;

int addnode(){
    memset(trie[ndcnt], -1, sizeof(trie[ndcnt]));
    return ndcnt++;
}

void init(){
    ndcnt=0;
    addnode();
}

void add(int x){
    int cur=0;
    for(int i=curbit;i>=0;i--){
        int id = (po[i]&x)>0;
        int &nx = trie[cur][id];
        if(nx==-1){
            nx=addnode();
        }
        cur = nx;
    }
}

int query(int x, int cur=0, int bit=curbit){
    if(bit<0){
        return 0;
    }
    int id = (x&po[bit])>0;
    if(trie[cur][id]!=-1){
        return query(x,trie[cur][id],bit-1);
    }
    return po[bit] + query(x, trie[cur][1-id],bit-1);
}



int main() {
    //ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    po[0]=1;
    for(int i=1;i<=30;i++){
        po[i]=2*po[i-1];
    }
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    int msk = 0;
    ll ans=0;
    for(int bit=29;bit>=0;bit--){
        int cur = (po[bit]);

        zero.clear();
        one.clear();
        for(int i=0;i<n;i++){
            if((cur&a[i])>0){
                one[a[i]&msk].pb(a[i]);
            }else{
                zero[a[i]&msk].pb(a[i]);
            }
        }
        for(auto &u:one){
            init();
            if(u.se.size()==0 || zero[u.fi].size()==0){
                continue;
            }
            int rs=po[30];
            for(auto v:u.se){
                add(v);
            }
            for(auto v:zero[u.fi]){
                rs=min(rs, query(v));
            }
            ans+=rs;
        }
        msk+=cur;
        curbit--;
    }
    cout << ans;
    return 0;

}
