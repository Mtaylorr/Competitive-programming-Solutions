#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 10567201 ;

int n;
map<string ,int> f;
string s;

int main()
{
   // freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        cin >> s;
        f[s]++;
    }
    for(auto u:f){
        if(2*u.se>n){
            cout << u.fi ;
            return 0;
        }
    }
    puts("NONE");

    return 0;
}
