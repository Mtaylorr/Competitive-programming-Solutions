#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5;
const int MOD = 10567201 ;

int n;
double n1,n2,n12;

int main()
{
    //freopen("input.txt", "r",stdin);
    cin >> n1 >> n2 >> n12;
    int x = int(floor((n1+1)*(n2+1)/(n12+1)-1));
    cout << x;

    return 0;
}
