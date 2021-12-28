//https://vjudge.net/problem/FZU-1499
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353 ;

int available[55], required[1005], n,m;
int freq[129];
int sma=0;
int mx=0;

bool swim(int avind, int freqind, int waste, int rem){
    if(!rem)
        return true;
    if(waste<0 || avind==n)
        return false;
    for(int i=freqind;i<=mx;i++){
        if(!freq[i]==0)
            continue;
        if(available[avind]<i)
            break;
        available[avind]-=i;
        freq[i]--;
        if(swim(avind, i,waste, rem-1)){
            freq[i]++;
            available[avind]+=i;
            return true;
        }
        freq[i]++;
        available[avind]+=i;

    }
    return swim(avind+1, 0, waste-available[avind],rem);

}

bool ok(int x){
    memset(freq, 0, sizeof(freq));
    int smreq = 0 ;
    for(int i=0;i<x;i++){
        freq[required[i]]++;
        smreq+=required[i];
        mx=required[i]
;    }
    return swim(0,0,sma-smreq,x);
}


int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&available[i]);
        sma+=available[i];
    }
    sort(available, available+n);
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%d",&required[i]);
    }
    sort(required, required+m);
    int st=0, en=m;
    while(st<en){
        int md = st+(en-st+1)/2;
        if(ok(md)){
            st=md;
        }else{
            en=md-1;
        }
    }
    printf("%d\n", st);
    return 0;
}
