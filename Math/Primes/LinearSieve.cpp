#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 100e6 +5 ;
const int MOD = 998244353 ;


int primes[N],prmcnt;
int smallestPrimeFactor[N];
int res[50], rscnt;

void getWheel(const vector<int> & smallPrimes){
    int  p = 1;
    for(int i=0;i<smallPrimes.size();i++)
        p*=smallPrimes[i];
    vector<bool> muls(p,0);
    for(int x:smallPrimes){
        for(int y=0;y<p;y+=x){
            muls[y]=true;
        }
    }
    int prev = 1;
    for(int i=2;i<muls.size();i++){
        if(!muls[i])
            res[rscnt++]=(i-prev),prev=i;
    }
    res[rscnt++]=p+1-prev;
}

void sieve(){
    primes[prmcnt++]=2;
    primes[prmcnt++]=3;
    primes[prmcnt++]=5;
    primes[prmcnt++]=7;
    getWheel({2,3,5,7});
    for(int i=1+res[0],k=0;i<N;i+=res[k=++k%rscnt]){
        if(smallestPrimeFactor[i]==0){
            smallestPrimeFactor[i]=i;
            primes[prmcnt++]=i;
        }
        int cs = N/i;
        for(int j=4;primes[j]<=cs;j++){
            smallestPrimeFactor[i*primes[j]]=primes[j];
            if(primes[j]>=smallestPrimeFactor[i]){
                break;
            }
        }
    }
}

int main(){
    freopen("input.txt", "r",stdin);
    sieve();

    return 0;
}
