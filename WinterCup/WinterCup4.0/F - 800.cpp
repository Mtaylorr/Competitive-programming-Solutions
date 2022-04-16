#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6+5;
const int MOD = 998244353  ;

int n,m;
char b;
char s[1005][1005];

int main(){
    //freopen("input.txt", "r",stdin);
    scanf("%d%d",&n,&m);
    cin >> b;
    for(int i=0;i<n;i++){
        scanf("%s",s[i]);
    }
    if(m==1){
        for(int i=0;i<n;i++){
            if(s[i][0]!=b)
            {
                cout << "NO";
                return 0;
            }

        }
    }
    for(int i=0;i<m;i++){
        if(s[n-1][i]!=b){
            cout << "NO";
            return 0;
        }
    }
    puts("YES");

    return 0;
}
