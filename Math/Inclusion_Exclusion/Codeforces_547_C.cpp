//https://codeforces.com/contest/547/problem/C

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 5e5 + 100, M = 1000 + 5, E = 2e6 + 5;
const int MOD = 998244353 ;

int mob[N];
bool vis[N];
bool out[N];
int n,a[N],q;
ll ans=0;
int freq[N];

void upd(int x, int sign=1){
    if(sign==1){
        for(int j=1;j*j<=x;j++){
            if(x%j==0){
                ans+=mob[j]*sign*freq[j];
                if(j*j!=x){
                    ans+=mob[x/j]*sign*freq[x/j];
                }
            }
        }
        for(int j=1;j*j<=x;j++){
            if(x%j==0){
                freq[j]+=sign;
                if(j*j!=x){
                    freq[x/j]+=sign;
                }
            }
        }
    }else{
        for(int j=1;j*j<=x;j++){
            if(x%j==0){
                freq[j]+=sign;
                if(j*j!=x){
                    freq[x/j]+=sign;
                }
            }
        }
        for(int j=1;j*j<=x;j++){
            if(x%j==0){
                ans+=mob[j]*sign*freq[j];
                if(j*j!=x){
                    ans+=mob[x/j]*sign*freq[x/j];
                }
            }
        }
    }

}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    mob[1]=0;
    for(int i=2;i<N;i++){
        mob[i]=-1;
    }
    for(int i=2;i<N;i++){
        if(vis[i])
            continue;
        ll si = i*1ll*i;
        for(int j=i;j<N;j+=i){
            vis[j]=1;
            if(j%si==0){
                mob[j]=0;
            }else{
                mob[j]*=-1;
            }
        }
    }
    cin >> n >> q;
    for(int i=0;i<n;i++){
        cin >> a[i];
        out[i]=1;
    }
    ll nb=0;
    while(q--){
        int p;
        cin >> p;
        p--;
        if(out[p]){
            upd(a[p]);
            nb++;
        }else{
            upd(a[p],-1);
            nb--;
        }
        out[p]=!out[p];
        ll tot = (nb*(nb-1))/2;
        cout << tot-ans << endl;
    }
    return 0;

}
