#include <functional>
#include <iostream>
#include <assert.h>
class Foo
{
public:
  Foo(int value) : m_value(value) {}
  
  std::function<int ()> make_function(int bonus)
  {
    return std::bind(&Foo::answer, this, bonus);
  }


  int answer(int bonus)
  {
    return m_value + bonus + 1;
  }
private:
  int m_value;
};

int question(int i)
{
  return i;
}

int main()
{
  Foo foo(32);
  std::function<int (int)> f = [](int i)->int{ return (i + 5); } ;
  std::function<int ()> g = [&foo]()->int{ return foo.answer(10); };

  //////////////////////////////////////////////////////////////////////////////
  //
  // Assignment: transform the static and member functions used to initialize
  // `f` and `g` to use lambdas instead, such that the program does not assert.
  //
  // Changes : Static member function=> i+5
  //		   Change in Member function => m_value + bonus + 1;	
  //
  //////////////////////////////////////////////////////////////////////////////
	
  try
  {		
	assert( (f(10) + g()) == 52);
  }
  catch(...)
  {
	  std::cout << "Changes done to failed assert\n";
  }
  return 0;
}
