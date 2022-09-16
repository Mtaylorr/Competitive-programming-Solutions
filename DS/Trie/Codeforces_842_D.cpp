//https://codeforces.com/problemset/problem/842/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 3e5 + 5, M=1000 +5,E = 2000 +5;
const int MOD = 1e9 + 7;

int cnt[20];
int tree[20*N][2], ndcnt;
int freq[20*N];
int n,m,a,x;

int addnode(){
    memset(tree[ndcnt], -1, sizeof(tree[ndcnt]));
    freq[ndcnt]=0;
    return ndcnt++;
}

void init(){
    ndcnt=0;
    addnode();
}
int po[20];
int L = 19;
set<int> s;
void ins(int a){
    int cur=0;
    for(int i=L;i>=0;i--){
        int d = (a&po[i])>0;
        int &nx = tree[cur][d];
        if(nx==-1){
            nx=addnode();
        }
        freq[nx]++;
        cur=nx;
    }
}

int getfreq(int p){
    if(p==-1)
        return 0;
    return freq[p];
}


int getans(){
    int ans= 0;
    int cur = 0;
    for(int i=L;i>=0;i--){
        if(cur==-1)
            break;
        int c = cnt[i]%2;
        int x = 0;
        int y = 1;
        if(c){
            swap(x,y);
        }
        int zerocnt = getfreq(tree[cur][x]);
        if(zerocnt == po[i]){
            cur = tree[cur][y];
            ans+=(po[i]);
        }else{
            cur=tree[cur][x];
        }
    }
    return ans;
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    po[0]=1;
    for(int i=1;i<=L;i++){
        po[i]=2*po[i-1];
    }
    cin >> n >> m;
    init();
    for(int i=0;i<n;i++){
        cin >> a;
        if(s.count(a)==0){
            ins(a);
            s.insert(a);
        }
    }
    while(m--){
        cin >> x;
        for(int i=0;i<=L;i++){
            if((po[i]&x)){
                cnt[i]++;
            }
        }
        cout << getans() << endl;
    }
    return 0;


}
