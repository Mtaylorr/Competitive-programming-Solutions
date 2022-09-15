//https://codeforces.com/problemset/problem/959/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e6 + 5, M=1000 +5,E = 2000 +5;
const int MOD = 1e9 + 7;

ll _sieve_size;
bitset<10000010> bs;
vector<int> primes;
void sieve(ll upperbound) {
    _sieve_size = upperbound + 1;bs.set();bs[0] = bs[1] = 0;
    for (ll i = 2; i <= _sieve_size; i++) if (bs[i]) {
            for (ll j = i * i; j <= _sieve_size; j += i) bs[j] = 0;primes.push_back((int)i); }
}
bool vis[N];
int n,a[N];

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    sieve(2000000);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    int pos = -1;
    vector<int> tmp;
    for(int i=0;i<n;i++){
        int x = a[i];
        bool cond=true;
        tmp.clear();
        for(int j=2;j*j<=x;j++){
            if(x%j==0){
                tmp.pb(j);
                if(vis[j]){
                    cond=false;
                }
                while(x%j==0){
                    x/=j;
                }
            }

        }
        if(x>1){
            tmp.pb(x);
            if(vis[x]){
                cond=false;
            }
        }
        if(cond){
            for(auto u:tmp){
                vis[u]=1;
            }
        }else{
            pos=i+1;
            cond=false;
            while(!cond){
                a[i]++;
                int x = a[i];
                cond=true;
                tmp.clear();
                for(int j=2;j*j<=x;j++){
                    if(x%j==0){
                        tmp.pb(j);
                        if(vis[j]){
                            cond=false;
                        }
                        while(x%j==0){
                            x/=j;
                        }
                    }

                }
                if(x>1){
                    tmp.pb(x);
                    if(vis[x]){
                        cond=false;
                    }
                }
            }
            for(auto u:tmp){
                vis[u]=1;
            }
            break;
        }
    }
    int indprimes = 0;
    if(pos!=-1){
        for(int i=pos;i<n;i++){
            while(vis[primes[indprimes]]){
                indprimes++;
            }
            a[i]=primes[indprimes];
            indprimes++;
        }
    }

    for(int i=0;i<n;i++){
        cout << a[i] << " ";
    }
    return 0;


}
