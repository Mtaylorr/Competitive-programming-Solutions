//https://codeforces.com/problemset/problem/1103/B

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5, E = 1 << 17;
const int MOD =  998244353 ;


string s;
char c;
int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> s;
    while(s=="start"){
        int cur = 0;
        int b=1;
        while(1){
            cout << "? " << cur << " " << cur+b << endl;
            cin >> c;
            if(c=='e'){
                return 0;
            }
            if(c=='y'){
                cur+=b;
                b*=2;
                continue;
            }else{
                break;
            }
        }
        b/=2;
        while(b){
            cout << "? " <<cur << " " << cur+b << endl;
            cin >> c;
            if(c=='e'){
                return 0;
            }
            if(c=='y'){
                cur+=b;
            }
            b/=2;
        }
        cout << "! "<<cur+1 << endl;
        cin >> s;
    }
    return 0;
}
