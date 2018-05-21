#include <iostream>
#include <functional>
#include <assert.h>

using namespace std;
using namespace std::placeholders;

class Test_placeholder {
	public :
		Test_placeholder(int value) : m_value(value) {}

		int mul_with_ten(int i) {
			return i*10;
		}

		int get_value() {
			return 5;
		}

		int get_double_value(const Test_placeholder & p1) {
			return p1.m_value + m_value;
  		}

	private :
		int m_value;
};

int default_sum(int i) {
	return i+10;
}

int get_value() {
  	return 10;
}

int main () {

	std::function<int (int)> a = std::bind(default_sum, _1);
	std::function<int ()> b = std::bind(get_value);

	assert((a(10) + b()) == 30);
	std::cout << "Actual func value get : " << a(20) + b() << endl;

	Test_placeholder p(2);

	std::function<int (int)> c = std::bind(&Test_placeholder::mul_with_ten, p, _1);
	std::function<int ()> d = std::bind(&Test_placeholder::get_value, p);

	assert((c(1) + d()) == 15);
	std::cout << "Actual Class func value get : " << c(1) + d() << endl;

	Test_placeholder p1(5);
	std::function<int (int)> e = std::bind(&Test_placeholder::mul_with_ten, p1, _1);
	std::function<int ()> f = std::bind(&Test_placeholder::get_double_value, std::ref(p1), std::cref(p1));

	assert((e(1) + f()) == 20);
	std::cout << "Actual Class func value double get : " << e(1) + f() << endl;
}
