#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
#define pb push_back
#define nl cout<<"\n"
#define db(x) cout<<x<<" "
#define fi(a,b) for(int i=a;i<b;i++)
#define fj(a,b) for(int j=a;j<b;j++)
#define fk(a,b) for(int k=a;k<b;k++)
#define F first
#define S second
ll fastexp(ll a,ll n,ll nod=LLONG_MAX){
	ll ans=1;
	while(n){
		if(n&1)
			ans=(ans*a)%nod;
		a=(a*a)%nod;
		n>>=1;
	}
	return ans;
}

#define vvl vector<vector<ll>>
#define vl vector<ll>
#define pl pair<ll,ll>
#define ppl pair<ll,pair<ll,ll>>
#define mxsize (int)1e6+5

void fun(){
	int n;
	cin>>n;
	vl a(n+1,0),b(n+1,0),c(n+1,0);
	fi(1,n+1)	cin>>a[i];
	fi(1,n+1)	cin>>b[i];
	fi(1,n+1)	cin>>c[i];
	vvl dp(n+2,vl(2,0));
	fi(1,n+1){
		if(a[i]>=a[i-1]&&a[i]>=b[i-1])	dp[i][0]=min(dp[i-1][0],dp[i-1][1]);
		else if(a[i]>=b[i-1])	dp[i][0]=dp[i-1][1];
		else if(a[i]>=a[i-1])	dp[i][0]=dp[i-1][0];
		else			dp[i][0]=INT_MAX;
		if(b[i]>=a[i-1]&&b[i]>=b[i-1])	dp[i][1]=c[i]+min(dp[i-1][0],dp[i-1][1]);
		else if(b[i]>=b[i-1])	dp[i][1]=c[i]+dp[i-1][1];
		else if(b[i]>=a[i-1])	dp[i][1]=c[i]+dp[i-1][0];
		else	dp[i][1]=INT_MAX;
	}

	ll ans=min(dp[n][0],dp[n][1]);
	if(ans>=INT_MAX){
		cout<<"-1\n";
	}
	else{
		cout<<ans<<"\n";
	}

}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cout.precision(20);
	cout<<fixed;
	#ifndef ONLINE_JUDGE
		freopen("/ATOM/input.txt", "r", stdin);
		freopen("/ATOM/output.txt", "w", stdout);
	#endif
	int t=1;
	cin>>t;
	while(t--){
		fun();
	}
}
