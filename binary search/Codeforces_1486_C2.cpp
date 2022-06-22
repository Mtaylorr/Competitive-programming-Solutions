//https://codeforces.com/problemset/problem/1486/C2
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;

int n;
int p;
int x;

int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    int l=1;
    int r=n;
    cout <<"? "<< l << " " << r << endl;
    cin >> p;
    if(n==2){
        cout << "! " << 3-p << endl;
        return 0;
    }
    if(l==p){
        l++;
    }else if(r==p){
        r--;
    }else{
        cout <<"? "<< l << " " << p << endl;
        cin >> x;
        if(x==p){
            r=p-1;
        }else{
            l=p+1;
        }
    }
    while(l<r){
        int md = (l+r)/2;
        if(r<p)
            md = (l+r+1)/2;
        if(md<p)
            cout <<"? "<< md << " " << p << endl;
        else
            cout <<"? "<< p << " " << md << endl;
        cin >> x;
        if(x!=p){
            if(md<p){
                r=md-1;
            }else{
                l=md+1;
            }
        }else{
            if(md<p){
                l=md;
            }else{
                r=md;
            }
        }
    }
    cout <<"! "<< l << endl;

    return 0;

}
