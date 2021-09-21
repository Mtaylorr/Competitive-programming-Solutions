//https://codeforces.com/contest/1574/problem/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 1e6 + 5;

ll n,x,m;
vector<ll> a[15];
vector<ll> ban[N];
bool ok;
ll curj;
ll c[N];
ll bessol=-1;
ll maxsum[N];
ll cursum=0;

vector<ll> cur;
vector<ll> res;

bool cmp(vector<ll> &a , vector<ll> &b){
    for(int i=0;i<n;i++){
        if(a[i]<b[i])
            return 0;
        if(a[i]>b[i])
            return 1;
    }
    return 0;
}


bool isbanned(){
    if(curj>=m)
        return 0;
    while(curj <m  && cmp(ban[curj], cur)==1)
        curj++;
    if(curj>=m)
        return 0;
    for(int i=0;i<n;i++){
        if(cur[i]!=ban[curj][i])
            return 0;
    }
    return 1;
}



void solve(ll pos){
    if(pos>=n){
        if(isbanned()){
            curj++;
            return ;
        }
        if(cursum>bessol){
            bessol=cursum;
            res=cur;
        }
        return ;
    }
    for(int i=c[pos]-1;i>=0;i--){

        if(cursum+a[pos][i]+maxsum[pos+1]<=bessol)
            break;
        cur.pb(i);
        cursum+=a[pos][i];
        solve(pos+1);
        cur.pop_back();
        cursum-=a[pos][i];
    }
}

int main(){
    scanf("%lld",&n);
    for(int i=0;i<n;i++){
        scanf("%lld",&c[i]);
        for(int j=0;j<c[i];j++){
            scanf("%lld",&x);
            a[i].pb(x);
        }
    }
    for(int i=n-1;i>=0;i--)
        maxsum[i]=maxsum[i+1] + a[i][c[i]-1];
    scanf("%lld",&m);
    curj=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%lld",&x);
            x--;
            ban[i].pb(x);
        }
    }
    sort(ban,ban+m,cmp);
    solve(0);
    for(auto u:res){
        cout << u+1 << " ";
    }
    return 0;
}
