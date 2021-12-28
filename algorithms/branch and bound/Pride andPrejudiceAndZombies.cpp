//https://vjudge.net/problem/UVALive-5123
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353 ;

int in[10];
ll n;

bool swim(long long p=1, long long a=0, long long b = 0, bool zeroa=false, bool zerob=false){
    if(a*b==n)
        return true;
    if(a*b%p != n%p)
        return 0;
    for(int i=zeroa;i<10;i++){
        if(in[i]==0)
            continue;
        in[i]--;
        for(int j=zerob;j<10;j++){
            if(in[j]==0)
                continue;
            in[j]--;
            if(swim(p*10, a+i*p, b+j*p,i==0 , j==0))
                return true;
            in[j]++;
        }
        in[i]++;
    }
    return 0;
}

int main(){
    freopen("input.txt", "r",stdin);
    while(1){
        memset(in, 0, sizeof(in));
        scanf("%lld",&n);
        if(n==0)
            break;
        ll tmp = n;
        while(tmp){
            in[tmp%10]++;
            tmp/=10;
        }
        printf("%lld: ",n);
        if(swim()){
            puts("yes");
        }else
            puts("no");
    }
    return 0;
}
