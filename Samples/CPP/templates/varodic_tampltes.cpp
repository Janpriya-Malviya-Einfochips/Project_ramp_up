#include<iostream>
#include<functional>
#include<string>
	
using namespace std;
	
template<typename T>
T adder(T v) 
{
  std::cout << "Added with signle arg called \n";
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return v;
}

template<typename T, typename... Args>
T adder(T first, Args... args) 
{
  std::cout << "Added with multi arg called \n";
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return first + adder(args...);
}

template<typename T>
bool pair_comparer(T a) {
   std::cout <<  __PRETTY_FUNCTION__ << "A= " << a << "\n";
  return false;
}


template<class T>
bool pair_comparer(T a, T b) {
  // In real-world code, we wouldn't compare floating point values like
  // this. It would make sense to specialize this function for floating
  // point types to use approximate comparison.
   std::cout <<  __PRETTY_FUNCTION__ << "A= " << a << "B= " << b << "\n";
  return a == b;
}

template<class T, class... Args>
bool pair_comparer(T a, T b, Args... args) 
{
	std::cout <<  __PRETTY_FUNCTION__ << "A= " << a << "B= " << b << "\n";
	return a == b && pair_comparer(args...);
}

template <typename... Ts>
double sum(Ts... ts) {
  double result = 0.0;
  for (auto el : ts)
    result += el;
  return result;
}

int main()
{
	//std::cout << "Try to add 1, 2, 3, 8, 7  Result=" <<  adder(1, 2, 3, 8, 7) << "\n";
	//std::cout << "Try to call compare  Result=" <<  pair_comparer(1.5, 1.5, 2, 2, 6, 6 , 7) << "\n";
	
	return 0;
}
