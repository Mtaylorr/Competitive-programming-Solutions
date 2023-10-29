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

vector<int>v[100005];
map<string, int>m;
string a[100005];
bool seen[100005];

void dfs(int idx, int anc)
{
	seen[idx] = 1;
	for(int i = 0; i < v[idx].size(); i++)
	{
		if((!seen[v[idx][i]]) && v[idx][i]!=anc)
			dfs(v[idx][i], idx);
	}
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int n;
	cin >> n;
	vector<pair<int, int> >v1, v2;
	int cu=0;
	for(int i = 1; i <= n; i++)
	{
		string s1, x,  s2;
		cin >> s1 >> x >> s2;
		//cout << s1 << ' ' << x << ' ' << s2 << '\n';
		if(!m.count(s1))
		{
			m[s1]=cu;
			a[cu]=s1;
			cu++;
		}
		if(!m.count(s2))
		{
			m[s2]=cu;
			a[cu]=s2;
			cu++;
		}
		if(x=="??")
		{
			v2.push_back(make_pair(m[s1], m[s2]));
			v[m[s1]].push_back(m[s2]);
			v[m[s2]].push_back(m[s1]);
		}
		else
		{
			v1.push_back(make_pair(m[s1], m[s2]));
			
		}
	}
	for(int i = 0; i < v1.size(); i++)
		dfs(v1[i].second, v1[i].first);
	vector<string>ans;
	for(int i = 0; i < cu; i++)
		if(!seen[i])
			ans.push_back(a[i]);
	sort(ans.begin(), ans.end());
	for(int i = 0; i < ans.size(); i++)
		cout << ans[i] << '\n';
}
//07-02-46
