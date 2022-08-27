//https://codeforces.com/contest/1721/problem/D
#include <bits/stdc++.h>
 
#define pb push_back
#define fi first
#define se second
 
typedef long long ll;
 
using namespace std;
 
const int N = 1e5 + 5, E = 1 << 17;
const int MOD =  998244353;
 
int n,t,a[N],b[N], ndcnt=0;
 
int nxt[30*N][2];
int cnt[30*N];
int cnt2[30*N];
int po[30];
 
int addnode(){
    memset(nxt[ndcnt], -1, sizeof(nxt[ndcnt]));
    cnt[ndcnt]=0;
    cnt2[ndcnt]=0;
    return ndcnt++;
}
void init(){
    ndcnt=0;
    addnode();
}
 
void ins(int x){
    int cur=0;
    for(int i=29;i>=0;i--){
        int p = (x&po[i])>0;
        int & nx = nxt[cur][p];
        if(nx==-1){
            nx=addnode();
        }
 
        cnt[nx]++;
        cur=nx;
    }
}
 
bool solve(int x, int mx_bit){
    int cur=0;
    for(int i=29;i>=mx_bit;i--){
        int p = (x&po[i])>0;
        int & nx = nxt[cur][p];
        if(nx==-1){
            return 0;
        }
        if(i==mx_bit) {
            cnt2[nx]++;
            if(cnt2[nx]<=cnt[nx]){
                return 1;
            }
            return 0;
        }
        cur=nx;
    }
}
 
int get(int v, int msk , int mx_bit){
    int rs=0;
    for(int j=0;j<=29;j++){
        int x = (v&po[j])>0;
        int y = (msk&po[j])>0;
        if(j>=mx_bit){
            rs+=(x*y)*po[j];
        }else{
            rs+=x*po[j];
        }
    }
    return rs;
}
 
bool sol(int msk,int mx_bit){
    for(int i=0;i<n;i++){
        if(!solve(get(a[i], msk, mx_bit+1)^msk, mx_bit)){
            return 0;
        }
    }
 
    return 1;
}
 
int main() {
   // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    po[0]=1;
    for(int i=1;i<=29;i++){
        po[i]=2*po[i-1];
    }
    while(t--){
        init();
        cin >> n;
        for(int i=0;i<n;i++){
            cin >> a[i];
        }
        for(int i=0;i<n;i++){
            cin >> b[i];
            ins(b[i]);
        }
        int msk=0;
        for(int bit=29;bit>=0;bit--){
            int new_msk = msk+(1<<bit);
            if(sol(new_msk,bit)){
                msk=new_msk;
            }
            init();
            for(int i=0;i<n;i++){
                ins(get(b[i], msk , bit));
            }
        }
        cout << msk << endl;
    }
 
    return 0;
}
