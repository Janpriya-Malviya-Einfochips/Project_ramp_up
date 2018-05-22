#include <assert.h>
#include <vector>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
//
// Assignment: compile existing program and run using valgrind, and save the
// output.  Next, modify the program so that it uses managed pointers instead of
// raw pointers.  Run the modified program using valgrind, and compare outputs.
// Run the program using a debugger, and step through copying and deleting the
// managed pointers.
//
// Answer: Problem already resolved using unique_ptr
////////////////////////////////////////////////////////////////////////////////

class Foo
{
public:
  Foo (std::unique_ptr < int > v):val (std::move (v))
  {
  }
  int answer ()
  {
    return *val;
  }
  int dummy()
  {
      return 10;
  }
private:
  std::unique_ptr < int > val;
};

int
main ()
{
  std::vector < Foo > fs;
  {
    for (int j = 0; j < 100; j++)
    {
      std::unique_ptr < int > i (new int (42));
      fs.emplace_back(std::move(i));
    }
  }

  for (auto f = fs.begin (); f != fs.end (); ++f)
  {
      assert (f->answer () == 42);
  }
}
