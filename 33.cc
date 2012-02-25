#include <iostream>
#include <utility>
#include <set>
#include <numeric>

using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
using std::set;

typedef pair<unsigned int, unsigned int> fraction;

unsigned int gcd(unsigned int a, unsigned int b) {
  if(a > b)
    return gcd(b, a);
  else if(b % a)
    return gcd(b % a, a);
  else
    return a;
}

fraction reduce(const fraction &frac) {
  auto factor = gcd(frac.first, frac.second);
  return make_pair(frac.first/factor, frac.second/factor);
}

bool less_than_one(const fraction &frac) {
  return frac.second > frac.first;
}

fraction frac_mult(const fraction &f1, const fraction &f2) {
  return make_pair(f1.first * f2.first, f1.second * f2.second);
}

const unsigned int digits[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

int main() {
  set<fraction> happy_joy;

  for(auto tens : digits) 
    for(auto ones : digits)
      for(auto filler : digits) { //BRUTE FORCE YEEEAAAAHHHH
	fraction f1 = make_pair(tens * 10 + ones, filler * 10 + tens),
	  f2 = make_pair(tens * 10 + ones, ones * 10 + filler),
	  cancel_f1 = make_pair(ones, filler),
	  cancel_f2 = make_pair(tens, filler);
	
	if(less_than_one(f1) && reduce(f1) == reduce(cancel_f1))
	  happy_joy.insert(f1);
	if(less_than_one(f2) && reduce(f2) == reduce(cancel_f2))
	  happy_joy.insert(f2);
      }

  auto answer = reduce(std::accumulate(happy_joy.begin(), happy_joy.end(), make_pair(1U,1U), frac_mult));
  cout<<answer.first<<"/"<<answer.second<<endl;
  
  return 0;
}
