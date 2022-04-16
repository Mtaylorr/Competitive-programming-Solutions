#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6+5;
const int MOD = 998244353  ;

int n,L;
int a,b;
int x;
int freq[N];
bool isprime[N];


void get(int x){

    for(int j=2;j*j<=x;j++){
        while(x%j==0){
            if(j<=L){
                freq[j]++;
            }
            x/=j;
        }
    }
    if(x!=1 && x<=L){
        freq[x]++;
    }
}

void sieve(){
    for(int i=2;i<=L;i++){
        isprime[i]=1;
    }
    for(int j=2;j<=L;j++){
        if(!isprime[j])
            continue;
        for(int k=2*j;k<=L;k+=j){
            isprime[k]=0;
        }
    }
}

int main(){
    scanf("%d%d",&n,&L);

    sieve();
    a=1e6;
    for(int i=0;i<n;i++){
        scanf("%d",&x);
        get(x);
    }
    for(int i=0;i<=L;i++){
        if(isprime[i])
            a=min(a, freq[i]);
    }
    memset(freq, 0, sizeof(freq));
    b=1e6;
    for(int i=0;i<n;i++){
        scanf("%d",&x);
        get(x);
    }
    for(int i=0;i<=L;i++){
        if(isprime[i])
            b=min(b, freq[i]);
    }
    if(b>a){
        puts("Yessine");
    }else{
        puts("Rami");
    }
    return 0;
}
