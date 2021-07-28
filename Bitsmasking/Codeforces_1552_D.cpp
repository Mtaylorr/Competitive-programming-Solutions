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
int a[N];

int main() {
    FAST;
    cin >> t;
    while (t--) {
        cin >> n;
        int three = 1;
        bool cond=false;
        // calculation 3^n
        for (int i = 0; i < n; i++) {
            three *= 3;
            cin >> a[i];
            if(a[i]==0){
                cond=true;
            }
        }
        // iterating over all 3^n submasks
        // for each 3-bit there are 3 possibilities : 0 - 1 - 2
        for (int mask = 0; mask < three; mask++) {
            if(cond) //  if there is already a solution we break the loop
                break;
            int sum = 0; // sum of elements in the mask
            int p = 0; // how many elements did we take in the mask
            ll curmask = mask; 
            for (int bit = 0; bit < n; bit++) {
                if (curmask % 3 == 1) { 
                    //  if 3-bit = 1 : then we added it to the sum
                    sum += a[bit];
                    p++;
                } else if (curmask % 3 == 2) {
                    // if 3-bit = 2 : then we added it to the sum
                    sum -= a[bit];
                    p++;
                }
                curmask /= 3;
            }
            if (sum == 0 && p>1) {
                // if the sum is null and there is at least one element that is a combination of some others then there is a solution
                cond = true;
                break;
            }
        }


        if (cond) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }


    }

    return 0;
}
