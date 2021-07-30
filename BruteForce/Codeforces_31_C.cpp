// https://codeforces.com/contest/31/problem/C
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


int n;
int dp[N];
int l[N], r[N];
int ok[2][N];
vector<int> v;


bool cmp(int a,int b){
  // function to compare the elements in the vector v
    return l[a]<l[b];
}
set<int> ss;

void show() {
    // function to print the answer
    cout << ss.size() << endl;
    for (auto u:ss) {
        cout << u + 1 << " ";
    }
}

int main() {
    FAST;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        v.pb(i);
    }
   // sort all elements from smallest to largest l
    sort(all(v), cmp);
    for(int i=0;i<n;i++){
        bool cond=true;
        int curr=-1;
        for(int j=0;j<n;j++){
            if(j==i)
                continue;
            if(curr==-1){
                // first element in the sequence
                curr=r[v[j]];
            }else{
                if(l[v[j]]<curr){
                    // there is intersection
                    cond=false;
                }
            }
            curr=r[v[j]];
        }
        if(cond){
            ss.insert(v[i]);
        }
    }
    show();



    return 0;
}
