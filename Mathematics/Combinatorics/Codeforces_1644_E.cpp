//https://codeforces.com/problemset/problem/1644/E

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 3e5 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 1e9 + 7  ;
const double eps = 1e-7;

int t,n;
string s;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n;
        cin >> s;
        int rs=0;
        int ds=0;
        for(auto c:s){
            rs+=c=='R';
            ds+=c=='D';
        }
        if(rs==0 || ds==0){
            cout << n << endl;
            continue;
        }
        int i=1;
        int j=1;
        ll ans = n*1ll*n;
        int lst = n-1;
        ans-=lst;
        for(int k=0;k<s.size();k++){
            i+=s[k]=='D';
            j+=s[k]=='R';
            rs-=s[k]=='R';
            ds-=s[k]=='D';
            if(k==s.size()-1 || s[k+1]!=s[k]){
                if(s[k]=='D'){
                    lst=ds;
                    ans-=lst;
                }else{
                    lst=rs;
                    ans-=rs;
                }
            }else{
                ans-=lst;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
