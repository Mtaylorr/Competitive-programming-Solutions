#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e6 + 5, E = 1 << 17;
const int MOD =  1e9 +7  ;


int x,y;
int t;

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){
        cin >> x >> y;
        cout << max(0, y-x) << endl;
    }

    return 0;

}
