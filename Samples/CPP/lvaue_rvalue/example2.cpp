#include <vector>
#include <inttypes.h>

class Test
{
public:
  Test() : bytes(1024, 42)
  {
  }

private:
  std::vector<uint8_t> bytes;
};
//////////////////////////////////////////////////////////////////////////////
//
// Assignment: compile existing program and run using valgrind, and save the
// output.  Next, modify the program so that it uses move semantics instead of
// copy semantics.  Run the modified program using valgrind, and compare outputs.
//
//////////////////////////////////////////////////////////////////////////////

int main()
{
  Test f;
  for(unsigned int i = 0; i < 1024 * 1024; ++i)
  {
    Test g = std::move(f);
  }
}
