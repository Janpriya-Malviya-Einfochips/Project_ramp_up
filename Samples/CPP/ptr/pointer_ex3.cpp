#include <assert.h>
#include <vector>
#include <functional>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
//
// Assignment: compile existing program and run using valgrind.  Fix the
// segmentation fault by replacing all use of pointers with managed pointers.
// Run in valgrind to verify.
//
// Answer: Problem already resolved using unique_ptr
////////////////////////////////////////////////////////////////////////////////

class Foo
{
public:
    Foo(std::unique_ptr<int> v) : val(std::move(v)) {}
    std::function<int ()> get_answer_func()
    {
        return std::bind(&Foo::answer, this);
    }
    int answer()
    {
        return *val;
    }
private:
    std::unique_ptr<int> val;
};

int main()
{
    std::unique_ptr<int> i(new int(42));
    std::unique_ptr<Foo> foo(new Foo(std::move(i)));
    std::function<int ()> f = foo->get_answer_func();
    assert(f() == 42);
}
