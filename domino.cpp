//Michal Plata
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define st first
#define nd second
#define pb push_back
#define rep(i,a,b) for(ll i=a;i<=b;i++)
#define all(a) a.begin(),a.end()
const int L = 91;
const int INF = 1e9+7;
ll dp[L+7];
map<ll,int> d;
unordered_map<ll,int> mapka;

void solve(){
	ll n; cin >> n;
	if(n == 1){
		cout << "1\n";
		return;
	}
	vector<ll> uzyt;
	rep(i,2,L) if(n%dp[i] == 0) uzyt.pb(dp[i]);
	d[1] = 1;
	for(auto u : uzyt){
		for(auto k : d){
			if(k.st > n/u + 1) break;
			if(d[u*k.st] == 0) d[u*k.st] = k.nd+mapka[u]+1;
			else d[u*k.st] = min(d[u*k.st],k.nd+mapka[u]+1);
		}
	}
		
	if(d[n] == 0) cout << "NIE\n";
	else cout << d[n]-2 << "\n";
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	dp[0] = 1; dp[1] = 1;
	rep(i,2,L) dp[i] = dp[i-1]+dp[i-2];
	rep(i,2,L) mapka[dp[i]] = i;
	solve();
}