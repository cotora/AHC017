#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
//#include <atcoder/all>
#endif

using namespace std;
//using namespace atcoder;
#define INF 1e9
#define repi(n) for(int i=0;i<n;i++)
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()
#define uset unordered_set
#define umap unordered_map
typedef long long ll;
typedef vector<int> vi;
typedef vector< vector<int> > vvi;
typedef vector<ll> vl;
typedef vector< vector<ll> > vvl;
typedef vector<bool> vb;
typedef vector< vector<bool> > vvb;
typedef vector<double> vd;
typedef vector< vector<double> > vvd;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

struct Edge{
	int to;
	ll w;
	Edge(int to,ll w):to(to),w(w){}
};


using Graph=vector<vector<Edge>>;

template <typename T>
bool chmin(T &x,T y){
	if(x>y){
		x=y;
		return true;
	}
	return false;
}

template <typename T>
bool chmax(T &x,T y){
	if(x<y){
		x=y;
		return true;
	}
	return false;
}

template <typename T>
string toBinary(T x){
	string res="";
	while(x!=0){
		if(x&1){
			res="1"+res;
		}
		else{
			res="0"+res;
		}
		x=x>>1;
	}
	return res;
}

int toDecimal(string s){
	int res=0;
	int d=1;
	for(int i=s.size()-1;i>=0;i--){
		if(s[i]=='1'){
			res+=d;
		}
		d*=2;
	}
	return res;
}

template <typename T>
void printVector(vector<T> &x){
	for(auto i : x)cout<<i<<" ";
	cout<<endl;
}

template <typename T>
void printVector2d(vector< vector<T> > &x){
	for(auto &i : x){
		for(auto j : i){
			cout<<j<<" ";
		}
		cout<<endl;
	}
}

void printYesOrNo(bool x){
	cout<<(x ? "Yes" : "No")<<endl;
}

Graph G;
vector<map<int,ll>> GM;
vb seen;
int n,d,k,m;
vi ans;
vi rnum;
map<pair<int,int>,int> mp;
vector<pair<pair<int,int>,ll>> es;
vvl base;
const int snum=5;
vl starts;

void dfs(int x,int p,int day){
	day%=d+1;
	if(day==0)day++;
	while(rnum[day]==k){
		day++;
		day%=d+1;
		if(day==0)day++;
	}
	int tmpx=x;
	int tmpp=p;
	if(tmpx>tmpp){
		swap(tmpx,tmpp);
	}
	if(mp.find({tmpx,tmpp})!=mp.end()){
	if(seen[mp[{tmpx,tmpp}]])return;
	ans[mp[{tmpx,tmpp}]]=day;
	rnum[day]++;
	seen[mp[{tmpx,tmpp}]]=true;
	}
	for(auto v : G[x]){
		dfs(v.to,x,day+1);
	}
}

//O(|E|log|V|)
//sは始点
vector<ll> dijkstra(int s){
	vl dist(n,INF);
	dist[s]=0;

	priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> que;
	que.push(make_pair(dist[s],s));

	while(!que.empty()){
		int v=que.top().second;
		ll dd=que.top().first;
		que.pop();

		if(dd>dist[v])continue;

		for(auto e : GM[v]){
			if(chmin(dist[e.first],dist[v]+e.second)){
				que.push(make_pair(dist[e.first],e.first));
			}
		}
	}
	return dist;
}

ll score(){
	ll res=0;
	vvi dedge(d+1);
	vvl dist(snum);
	for(int i=0;i<m;i++){
		dedge[ans[i]].push_back(i);
	}
	for(int i=1;i<=d;i++){
		for(auto e : dedge[i]){
			GM[es[e].first.first].erase(es[e].first.second);
			GM[es[e].first.second].erase(es[e].first.first);
		}
		for(int j=0;j<snum;j++){
			dist[j]=dijkstra(starts[j]);
		}
		for(auto e : dedge[i]){
			GM[es[e].first.first][es[e].first.second]=es[e].second;
			GM[es[e].first.second][es[e].first.first]=es[e].second;
		}
		ll tmp=0;
		for(int k=0;k<snum;k++){
			for(int j=0;j<n;j++){
				if(starts[k]==j)continue;
				tmp+=dist[k][j]-base[k][j];
			}
		}
		tmp/=(n-1)*snum;
		res+=tmp;
	}
	res/=d;
	res*=1000;
	return res;
}

int main(void){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout<<fixed<<setprecision(15);
	cin>>n>>m>>d>>k;
	G.resize(n);
	GM.resize(n);
	seen.resize(m,false);
	ans.resize(m);
	rnum.resize(d+1,0);
	es.resize(m);
	base.resize(snum);
	starts.resize(snum);

	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<> rand100(0,n-1);
	for(int i=0;i<snum;i++){
		starts[i]=rand100(mt);
	}
	repi(m){
		int u,v;
		ll w;
		cin>>u>>v>>w;
		u--;v--;
		if(u>v){
			swap(u,v);
		}
		G[u].push_back(Edge(v,w));
		G[v].push_back(Edge(u,w));
		GM[u][v]=w;
		GM[v][u]=w;
		mp[make_pair(u,v)]=i;
		es[i]=make_pair(make_pair(u,v),w);
	}
	for(int i=0;i<snum;i++){
	base[i]=dijkstra(starts[i]);
	}
	vi finalAns;
	ll s=1LL<<55;
	for(int i=0;i<n;i+=10){
		dfs(i,i,1);
		if(score()<s){
			s=score();
			finalAns=ans;
		}
	}
	//for(int i=1;i<=d;i++)cerr<<rnum[i]<<" ";
	//cerr<<endl;
	printVector(finalAns);
	return 0;
}