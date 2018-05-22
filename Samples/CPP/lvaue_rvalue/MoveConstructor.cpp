#include <iostream>
#include <memory>

class Test
{
public:
    Test() : my_count(count++)
    {
        std::cout << "Default Constructor " << my_count << std::endl;
    }

    Test(const Test & f)
        : my_count(count++)
    {
        std::cout << "Copy Constructor "  << f.my_count << " to " << my_count << std::endl;
    }

    Test(Test && f)
        : my_count(count++)
    {
        std::cout << "Move Constructor "  << f.my_count << " to " << my_count << std::endl;
    }

    ~Test()
    {
        std::cout << "Destructor "  << my_count << std::endl;
    }

    Test & operator=(const Test & f)
    {
        std::cout << "Copy Assignment " << f.my_count << " to " << my_count << std::endl;
    }

    Test & operator=(Test && f)
    {
        std::cout << "Move Assignment "  << f.my_count << " to " << my_count << std::endl;
    }

private:
    static int count;
    int my_count;
};

int Test::count = 0;

int main()
{
    Test t0{};
    Test t1{};
    Test t2 = t1;
    std::unique_ptr<Test> t3(new Test());
    Test t4(std::move(*(t3.get())));
    t3.reset();
    t4 = t1;
    t2 = std::move(t4);
}
