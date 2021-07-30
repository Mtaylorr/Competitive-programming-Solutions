// https://codeforces.com/contest/1554/problem/D

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
int n;
string s;
int main() {
    FAST;
    cin >> t;
    while (t--) {
        cin >> n;
        if(n<=26){
            for(int i=0;i<n;i++){
                cout << char('a'+i) ;
            }
            cout << endl;
            continue;
        }
        s="";
        int nb=n/2;
        for(int i=0;i<nb;i++){
            s+='a';
        }
        s+='b';
        for(int i=0;i<nb-1;i++){
            s+='a';
        }
        n-=(2*nb);
        if(n){
            s+='c';
        }
        cout << s << endl;
    }

    return 0;
}
