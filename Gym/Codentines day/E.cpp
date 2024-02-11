#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
#define INV_2 499122177
#define INF 1000000000
#define PI 3.14159265358979323846
#define eps 1e-9
#define MOD1 998244353
#define MOD2 1000000007

using namespace std;

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int n;
	cin >> n;
	string s;
	set<string>ss;
	for(int i = 0; i < n; i++)
	{
		cin >> s;
		if(s == "touch")
		{
			getline(cin, s);
			ss.insert(s);
		}
		else if(s == "rm")
		{
			getline(cin, s);
			if(ss.count(s))
				ss.erase(s);
		}
		else if(s == "ask")
		{
			cout << ss.size() << '\n';
		}
	}
}	
//07-02-46
