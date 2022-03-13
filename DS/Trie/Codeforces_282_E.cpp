//https://codeforces.com/problemset/problem/282/E

#include <bits/stdc++.h>
#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 1e9 +7 ;

int n;
ll a[N];
ll cum[N];
int ndcnt=0;
ll po[N];
struct node{
    int nxt[2];
    int nb;
};

node trie[40*N];

int addnode(){
    memset(trie[ndcnt].nxt,-1, 2*sizeof(int));
    trie[ndcnt].nb=0;
    return ndcnt++;
}

void init(){
    ndcnt=0;
    addnode();
}
void upd(ll x, int v){
    int cur = 0;
    for(int j=39;j>=0;j--){
        int p = (po[j]&x)>0;
        int& nx = trie[cur].nxt[p];
        if(nx==-1){
            nx = addnode();
        }
        trie[nx].nb+=v;
        cur=nx;
    }
}

ll query(ll x){
    int cur = 0;
    ll ans=0;
    for(int j=39;j>=0;j--){
        int p = (po[j]&x)>0;
        int& nx = trie[cur].nxt[1-p];
        if(nx!=-1 && trie[nx].nb!=0){
            ans+=po[j];
            cur=nx;
        }else{
            cur=trie[cur].nxt[p];
        }
    }
    return ans;
}



int main()
{
    freopen("input.txt", "r",stdin);
    po[0]=1;
    init();
    for(int i=1;i<=40;i++){
        po[i]=2*po[i-1];
    }
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    ll ans=0;
    upd(0,1);
    for(int i=1;i<=n;i++){
        cum[i]=cum[i-1]^a[i];
        upd(cum[i],1);
        ans=max(ans, cum[i]);
    }
    ll cur=0;
    for(int i=n;i>=1;i--){
        cur=cur^a[i];
        upd(cum[i],-1);
        ans=max(ans, query(cur));
    }
    cout << ans << endl;

    return 0;

}
