//https://codeforces.com/problemset/problem/1144/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 4e5 + 5, E = 1 << 17;
const int MOD = 998244353;


string s,t,ans;
int n;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    cin >> s;
    cin >> t;
    ans="";
    int c=0;
    int x = s[n-1]-'a';
    int y = t[n-1]-'a';
    c+=(x+y)/2;
    for(int i=n-1;i>=1;i--){
        x = s[i - 1] - 'a';
        y = t[i - 1] - 'a';
        c+=(x+y)*13;
        ans+=char('a'+c%26);
        c/=26;
    }
    while(c){
        ans+=char('a'+c%26);
        c/=26;
    }
    while(ans.size()<n){
        ans+=t[n-ans.size()-1];
    }
    reverse(ans.begin(),ans.end());
    cout << ans;
    return 0;
}
