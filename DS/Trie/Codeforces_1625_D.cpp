//https://codeforces.com/contest/1625/problem/D
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 +5 ;
const int MOD = 998244353 ;

struct node{
    int nxt[2];
    node(){
        nxt[0]=nxt[1]=-1;
    }
};

int n,k,a[N];
vector<int> ans;
int po[32];
int  ndcnt=0;
node trie[N*33 + 10];
int v[N*33 + 10];
vector<int> res[N*33+10];

int addnode(){
    ndcnt++;
    return ndcnt;
}

int getind(int cur , int bit , int u){
    if(cur==-1)
        return 0;
    int b = (k&po[bit])>0;
    if(b==0 || bit==0){
        int a =(u&po[bit])>0;
        if(a &&  trie[cur].nxt[0]!=-1){
            return v[trie[cur].nxt[0]];
        }
        if(!a &&  trie[cur].nxt[1]!=-1){
            return v[trie[cur].nxt[1]];
        }
        if(bit==0 && b==0 &&  trie[cur].nxt[0]!=-1){
            return v[trie[cur].nxt[0]];
        }else if(bit==0 && b==0&& trie[cur].nxt[1]!=-1){
                return v[trie[cur].nxt[1]];
        }
        if(bit==0)
            return 0;
        if(a==0)
            return getind(trie[cur].nxt[0], bit-1,u);
        else
            return getind(trie[cur].nxt[1], bit-1,u);
    }else{
        int a =(u&po[bit])>0;
        if(a){
            return getind(trie[cur].nxt[0], bit-1,u);
        }
        return getind(trie[cur].nxt[1], bit-1,u);
    }
}

void add(int u, int p){
    int cur=0;
    bool cond=false;
    for(int i=29;i>=0;i--){
        int id = ((u&po[i])>0);
        if((!cond) && (k&po[i])){
            cond=true;
            if(res[cur].size()<2){
                int j = getind(cur , i, u);
                res[cur].clear();
                res[cur].pb(p+1);
                if(j)
                    res[cur].pb(j);
            }
        }
        int &nxt = trie[cur].nxt[id];
        if(nxt==-1){
            nxt = addnode();
        }
        cur = nxt;
        v[cur]=p+1;
    }
}


int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&k);
    if(k==0){
        printf("%d\n",n);
        for(int i=1;i<=n;i++){
            printf("%d ",i);
        }
        return 0;
    }
    addnode();
    po[0]=1;
    for(int i=1;i<30;i++){
        po[i]=2*po[i-1];
    }
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        add(a[i],i);
    }
    for(int i=0;i<ndcnt;i++){
        for(auto u:res[i]){
            ans.pb(u);
        }
    }
    if(ans.size()>=2){
        cout << ans.size() << endl;
        for(auto u:ans){
            cout << u << " ";
        }
        return 0;
    }
    else
        puts("-1");

    return 0;
}
