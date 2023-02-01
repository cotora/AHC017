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
#define INF 2e9
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


int main(void){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout<<fixed<<setprecision(15);
	int n,m,d,k;
	cin>>n>>m>>d>>k;
	vector<int> rnum(d+1,0);
	vector<pair<ll,int>> e(m);
	G.resize(n);
	repi(m){
		int u,v;
		ll w;
		cin>>u>>v>>w;
		u--;v--;
		G[u].push_back(Edge(v,w));
		G[v].push_back(Edge(u,w));
		e[i]=make_pair(w,i);
	}
	sort(all(e));
	int count=0;
	int today=1;
	vi ans(m);
	for(int i=0;i<m;i++){
		if(count==k){
			today++;
			count=0;
		}
		ans[e[i].second]=today;
		count++;
	}
	printVector(ans);
	/*
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<> rand100(1,d);
	for(int i=0;i<m;i++){
		int t=rand100(mt);
		while(rnum[t]==k){
			t=rand100(mt);
		}
		rnum[t]++;
		cout<<t<<" ";
	}
	cout<<endl;
	*/
	/*
	for(int i=1;i<=d;i++)cerr<<rnum[i]<<" ";
	cerr<<endl;
	*/
	return 0;
}