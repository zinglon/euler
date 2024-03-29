// compiles cleanly with apple clang 3.1,  clang++ -O2 -Wall -Wextra -std=c++11
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::multimap;

/* I use char all over just for the sake of premature space optimization */

vector<vector<unsigned char>> choose(unsigned int n, unsigned int c) {
  vector<vector<unsigned char>> ret;
  //well this is the worst way to do this other than anything else I came up with
  for(unsigned int i = (1<<c) - 1; i < 1<<n; i++) {
    if((unsigned int)__builtin_popcount(i) == c) {
      unsigned char idx = 0;
      unsigned int ii = i;
      vector<unsigned char> idxs;
      while(ii) {
	if(ii & 1) 
	  idxs.push_back(idx);
	ii >>= 1;
	idx++;
      }
      ret.push_back(idxs);
    }
  }
  return ret;
}

unsigned int powerof10(unsigned int power) {
  static unsigned int values[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
  return values[power];
}

//digits should be in ascending order
template<typename T>
unsigned int chop(unsigned int x, T const& digits) {
  unsigned int removed = 0;
  for(auto d : digits) {
    auto power = powerof10(d - removed);
    x = (x % power) + (x / (power * 10)) * power;
    removed++;
  } 
  return x;
}

vector<pair<unsigned int, vector<unsigned char>>> make_keys(unsigned int num) {
  auto digits = vector<vector<unsigned char>>(10,vector<unsigned char>());
  unsigned char index = 0;

  //not strictly necessary, just felt like having the early-bailout hatch
  bool good = false;

  //record the indexes of the digits
  unsigned int tempnum = num;
  while(tempnum) {
    digits[tempnum%10].push_back(index);
    if(digits[tempnum%10].size() > 0) good = true;
    tempnum /= 10;
    index++;
  }

  decltype(make_keys(0)) ret;
  if(!good) return ret;

  //for each digit that occurs twice or more,
  // make a wildcarded version by removing 2+ occurrences and remembering the indexes
  for(unsigned int digit = 0; digit < 10; digit++) {
    auto const& idxs = digits[digit];
    for(unsigned int remove = 2; remove <= (unsigned int)idxs.size(); remove++) {
      auto dropidxs = choose((unsigned int)idxs.size(), remove);
      for(auto& drops : dropidxs) {
	for(auto& drop : drops) //quickly twiddle the actual indexes in
	  drop = idxs[drop];

	ret.push_back(std::make_pair(chop(num,drops), drops));
      }
    }
  }
  
  return ret;
} 

template<typename T>
T remove_ref(T& x) { return x; }

int main() {
  //yeah, I feel like some decltype abuse
  typedef decltype(remove_ref(make_keys(0)[0])) keytype;
  multimap<keytype, int> values;

  //SIEVE OF ERATOSTHENES TIME YEEEEAAAAHHHHH
  //let's try 4 million
  const auto MAX = 4000000U;
  const auto SQRT_MAX = (unsigned int)std::sqrt(MAX);
  const auto goal = 8U;
  //[3,5..]
  auto prim = vector<unsigned char>(MAX/2, 1);
  for(unsigned int p = 0; p < (unsigned int)prim.size(); p++) {
    if(!prim[p]) continue;

    auto actual = p*2+3;
    
    for(auto const& possible : make_keys(actual)) {
      values.insert(std::make_pair(possible, actual));
      if(values.count(possible) == goal) {
	auto holycrap = values.equal_range(possible);
	for(auto it = holycrap.first; it != holycrap.second; it++)
	  cout << it->second << " ";
	cout << endl;
	return 0;
      }
    }

    //potential off-by-one error and subsequent nasal demons here
    if(actual <= SQRT_MAX)
    for(auto np = (actual * actual)/2 - 1; np < (unsigned int)prim.size(); np += actual)
      prim[np] = 0;
  }
  cout << "Nothing!" << endl;
  return 0;
}
