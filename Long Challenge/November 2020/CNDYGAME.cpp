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
ll odd_it(ll num){
	num-=(num%2==0);
	return num;
}
ll even_it(ll num){
	num-=num%2;
	return num;
}
void fun(){
	int n;
	cin>>n;
	vector<ll> a(n+1,0),even(n+1,0),odd(n+1,0);
	fi(1,n+1){
		cin>>a[i];
		even[i]=even_it(a[i]);
		odd[i]=odd_it(a[i]);
	}
	vector<ll> ans(n+1,0);
	ll sum=0,last=0;
	if(a[1]!=1&&n!=1){
		int i;
		for(i=1;i<n;i++){
			if(i==n-1){
				if(a[i+1]==1){
					ans[i]=(sum+a[i])%mod;
					sum+=even[i];
					sum%=mod;
					i++;
					sum+=1;
					sum%=mod;
					ans[i]=sum;
				}
				else{
					ans[i]=(sum+a[i])%mod;
					sum+=even[i];
					sum%=mod;
					i++;
					ans[i]=(sum+a[i])%mod;
					sum+=odd[i];
					sum%=mod;
				}
			}
			else{
				if(a[i+1]==1){
					ll last=sum;
					ans[i]=(sum+a[i])%mod;
					sum+=odd[i];
					sum%=mod;
					i++;
					ans[i]=max(sum,last+even[i-1]+1);
					ans[i]%=mod;
				}
				else{
					ans[i]=(sum+a[i])%mod;
					sum+=even[i];
					sum%=mod;
				}
			}
		}
		if(i==n){
			ans[i]=(sum+a[i])%mod;
			sum+=odd[i];
			sum%=mod;
		}
	}
	int q;
	cin>>q;
	while(q--){
		ll r,candy=0;
		cin>>r;
		if(r==1){
			candy=a[1]%mod;
		}
		else if(n==1){
			if(a[1]%2)	candy=(r*a[1])%mod;
			else{
				r--;
				candy=(r*(a[1]-1))%mod;
				candy+=a[1];
				candy%=mod;
			}
		}
		else if(a[1]==1){
			candy+=r/n;
			if(r%n>1)	candy++;
			candy%=mod;
		}
		else{
			if(r%n==0){
				r--;
				candy=(sum*(r/n))%mod;
				candy=(candy+ans[n])%mod;
			}
			else{
				candy=(sum*(r/n))%mod;
				r%=n;
				candy+=ans[r];
				candy%=mod;
			}
		}
		
		cout<<candy<<"\n";
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
