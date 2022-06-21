//https://codeforces.com/problemset/problem/1366/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;

int n;
int a;
int smallestPrime[P];

void sieve(){
    for(int i=2;i<=P;i++){
        if(smallestPrime[i]!=-1)
            continue;
        smallestPrime[i]=i;
        for(int j=2*i;j<=P;j+=i){
            if(smallestPrime[j]==-1){
                smallestPrime[j]=i;
            }
        }
    }
}
int d1[N],d2[N];

int main() {
    freopen("input.txt", "r", stdin);
    memset(smallestPrime,-1,sizeof(smallestPrime));
    sieve();
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a;
        int x = smallestPrime[a];
        int rs=1;
        while(a%x==0){
            rs*=x;
            a/=x;
        }
        if(a!=1){
            d1[i]=rs;
            d2[i]=a;
        }else{
            d1[i]=d2[i]=-1;
        }
    }
    for(int i=0;i<n;i++){
        cout << d1[i] << " ";
    }
    cout << "\n";
    for(int i=0;i<n;i++){
        cout << d2[i] << " ";
    }



    return 0;

}
