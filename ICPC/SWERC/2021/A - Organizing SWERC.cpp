#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E= 2e5+5;
const int MOD = 998244353 ;

int t;
int n;
int b,d;
int x[12];

int main() {
    ios::sync_with_stdio(0);
    //freopen("input.txt", "r", stdin);
    cin >> t;
    while(t--){
        cin >> n;
        memset(x, -1, sizeof(x));
        while(n--){
            cin >> b >> d;
            x[d]=max(x[d], b);
        }
        bool cond=true;
        int s=0;
        for(int i=1;i<=10;i++){
            if(x[i]==-1){
                cond=false;
            }
            s+=x[i];
        }
        if(cond){
            cout << s << endl;
        }else{
            cout << "MOREPROBLEMS"<< endl;
        }
    }


    return 0;

}
