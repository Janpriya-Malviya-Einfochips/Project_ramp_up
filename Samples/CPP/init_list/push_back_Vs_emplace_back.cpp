//- push_back may construct a temporary object which then will need to get moved into the vector v whereas emplace_back just forwards the argument and construct it directly in place with no copies or moves needed.
//- emplace_back can potentially be faster then push_back if you pass it something that needs to get constructed first.
//
//eg:
//    vector<string> words;
//   words.push_back("push_back")
//
//	- Since push_back requires a object of type string the string literal “push_back” gets passed to the string class constructor first ,in this case it has to make a temporary object which is then passed in to push_back.
//	  Where as with emplate_back there is no need for a temporary object , the string literal is just passed in so in this case it is a bit more efficient .
#include <iostream>
#include <vector>
class Test
{
public:
  Test (int x_arg) : x (x_arg) { std::cout << "Test (x_arg)\n"; }
  Test () { x = 0; std::cout << "Test ()\n"; }
  Test (const Test &rhs) noexcept { x = rhs.x; std::cout << "Test (Test &)\n"; }
  Test (Test &&rhs) noexcept { x = rhs.x; std::cout << "Test (Test &&)\n"; }

private:
  int x;
};

int main ()
{
  {
    std::vector<Test> a;
    std::cout << "call emplace_back:\n";
    a.emplace_back (0);
  }
  {
    std::vector<Test> a;
    std::cout << "call push_back:\n";
    a.push_back (1);
  }
  return 0;
}
