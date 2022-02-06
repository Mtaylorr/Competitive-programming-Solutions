//https://atcoder.jp/contests/abc238/tasks/abc238_g
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 +5 , P=1e6+1;
const int MOD = 1e9 + 7 ;

int n,q;
int a[N];
int qs[N], qe[N], qi[N], qa[N];
int bigPrime[N][2];
vector<int> primes;
bool notPrime[P];
int cumSum[100][N];
int freq[P];
int cnt=0, cntthree=0;
int s=1, e=0;

void sieve(){
    notPrime[0]=notPrime[1]=1;
    for(int i=1;i<P;i++){
        if(notPrime[i])
            continue;
        primes.pb(i);
        for(int j=i;j*1ll*i<P;j++){
            notPrime[i*j]=1;
        }
    }
}

void process(int u, int i){
    for(int j=0;j<100;j++){
        int  p = primes[j];
        int rs=0;
        while(u%p==0){
            rs++;
            u/=p;
        }
        if(rs){
            cumSum[j][i]+=rs;
        }
    }
    for(int j=100;primes[j]*primes[j]<=u;j++){
        int  p = primes[j];
        int rs=0;
        while(u%p==0){
            rs++;
            u/=p;
        }
        if(rs){
            bigPrime[i][0]=p;
            if(rs==2)
                bigPrime[i][1]=p;

        }
    }
    if(u>1){
        bigPrime[i][1]=bigPrime[i][0];
        bigPrime[i][0]=u;
    }
}

void add(int x){
    cnt+=freq[x]==0;
    if(freq[x])
        cntthree-=(freq[x]%3==0);
    freq[x]++;
    cntthree+=(freq[x]%3==0);
}

void rem(int x){
    cntthree-=(freq[x]%3==0);
    freq[x]--;
    if(freq[x])
        cntthree+=(freq[x]%3==0);
    cnt-=(freq[x]==0);
}
void addi(int i){
    for(int j=0;j<2;j++){
        if(bigPrime[i][j]!=-1){
            add(bigPrime[i][j]);
        }
    }
}
void remi(int i){
    for(int j=0;j<2;j++){
        if(bigPrime[i][j]!=-1){
            rem(bigPrime[i][j]);
        }
    }
}

void upd(int cur){
    while(e<qe[cur]){
        addi(++e);
    }
    while(s>qs[cur]){
        addi(--s);
    }
    while(e>qe[cur]){
        remi(e--);
    }
    while(s<qs[cur]){
        remi(s++);
    }
}

void mo(){
    int B = sqrt(n);
    sort(qi, qi+q, [B](int a, int b){return make_pair(qs[a]/B,(((qs[a]/B)&1)?-qe[a]:qe[a]))<make_pair(qs[b]/B,(((qs[b]/B)&1)?-qe[b]:qe[b]));});
    for(int i=0;i<q;i++){
        int cur = qi[i];
        if(!qa[cur])
            continue;
        upd(cur);
        if(cnt!=cntthree)
            qa[cur]=0;
    }
}





int main(){
    freopen("input.txt", "r",stdin);
    sieve();
    memset(bigPrime,-1, sizeof(bigPrime));
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        process(a[i],i);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<100;j++){
            cumSum[j][i]+=cumSum[j][i-1];
        }
    }
    for(int i=0;i<q;i++){
        scanf("%d%d",&qs[i],&qe[i]);
        qi[i]=i;
        qa[i]=1;
        for(int j=0;j<100;j++){
            if((cumSum[j][qe[i]]-cumSum[j][qs[i]-1])%3){
                qa[i]=0;
            }
            if(!qa[i])
                break;
        }
    }
    mo();
    for(int i=0;i<q;i++){
        if(qa[i]){
            puts("Yes");
        }else
            puts("No");
    }

    return 0;
}
