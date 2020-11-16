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
#define pii pair<int,pair<int,int>>
#define psi pair<string,pair<int,int>>
#define mxsize (int)505
int n,k;
int chck[mxsize][mxsize];
vector<vector<bool>> vis(mxsize,vector<bool>(mxsize,0));
vector<bool> done;
vector<int> corx,cory,l,r;
int dx[4]={0,-1,1,0};   //right up down left
int dy[4]={1,0,0,-1};
string dir="RUDL";
vector<psi> ans;
bool check(int org,int des,string& s){
	if(done[org]||done[des]||org==des)	return 0;
	int i=0;
	int x=corx[org],y=cory[org];
	while(i<s.size()){
		fj(0,4){
			if(s[i]==dir[j]){
				x+=dx[j];	y+=dy[j];
				break;
			}
		}
		if(vis[x][y])	return 0;
		if(chck[x][y]&&chck[x][y]!=des)	return 0;
		i++;
	}
	i=0;
	x=corx[org],y=cory[org];
	while(i<s.size()){
		fj(0,4){
			if(s[i]==dir[j]){
				x+=dx[j];	y+=dy[j];
				vis[x][y]=1;
				break;
			}
		}
		i++;
	}
	done[org]=done[des]=1;
	return 1;
}
bool comp(pii& a,pii& b){
	if(a.F!=b.F)	return a.F<b.F;
	return a.S>b.S;
}
void fun(){
	cin>>n>>k;
	done=vector<bool>(k+1,0);
	cory=l=r=corx=vector<int>(k+1,0);
	vector<pii> temp;
	fi(1,k+1){
		int x,y;
		cin>>x>>y>>l[i]>>r[i];
		chck[x][y]=i;
		corx[i]=x;	cory[i]=y;
		temp.push_back({r[i]+l[i],{r[i],i}});
	}
	sort(temp.begin(),temp.end(),comp);
	for(int fakei=0;fakei<k;fakei++){
		int i=temp[fakei].S.S;
		// db(i);nl;
// 		db(temp[fakei].F);db(temp[fakei].S.F);nl;
		int srcx=corx[i],srcy=cory[i];
		int c=0;
		for(int fakej=fakei+1;fakej<k;fakej++){
			int j=temp[fakej].S.S;
			int desx=corx[j],desy=cory[j];
			int L=max(l[i],l[j]);
			int R=min(r[i],r[j]);
			int dis=abs(srcx-desx)+abs(srcy-desy)+1;
			c++;
			if(c==13000)
			    break;
			// db(i);db(j);nl;
			if(dis<L||dis>R)	continue;
			string s="";
			string str="";
			if(desy>=srcy)	s+=string(desy-srcy,'R');
			else 			s+=string(srcy-desy,'L');
			if(desx>=srcx)	str+=string(desx-srcx,'D');
			else 			str+=string(srcx-desx,'U');

			ans.push_back({s+str,{i,j}});
			ans.push_back({str+s,{i,j}});
		}
	}
	int sz=ans.size();
	vector<bool> vis(sz,1);
	fi(0,ans.size()){
		if(!check(ans[i].S.F,ans[i].S.S,ans[i].F)){
			sz--;
			vis[i]=0;
		}
	}
	cout<<sz<<"\n";
	fi(0,ans.size()){	
		if(vis[i])	cout<<ans[i].S.F<<" "<<ans[i].S.S<<" "<<ans[i].F<<"\n";
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
	// cin>>t;
	fi(1,t+1){
		fun();
	}
}
