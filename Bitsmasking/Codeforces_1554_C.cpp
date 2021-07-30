// https://codeforces.com/contest/1554/problem/C
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll, ll> pl;
typedef long double ld;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)


const int N = int(1e6) + 3;
const int MOD = int(1e9) + 7;


int t;
ll n,m;
int main() {
    FAST;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        ll cur=0; //  cur mask
        ll takenbits = 0; //  mask for the taken bits
        for(int bit=30;bit>=0;bit--){
            takenbits+=(1<<bit);
            ll x = (n^cur)& takenbits;
            ll b = x + (1<<(bit))-1;
            b=min(b,m);
            if(b-x+1 == (1<<(bit))){ // if all the elements of the form of the current bit are <=m then there is no answer we add the bit 
                cur+=(1<<bit);
            }
        }
        cout << cur << endl;
    }


    return 0;
}
