#include <iostream>
#include <memory>

using namespace std;
class test;

void register_srvr(shared_ptr<test> ptr)
{
	cout << "register_srvr called " << ptr.get() << "\n";
}


class test : public std::enable_shared_from_this<test>
{
	
public:

		test()
		{
			cout << "Test class created= " << this << "\n";
		}
	
	
		~test()
		{
			cout << "Test class deleted = " << this << "\n";
		}
		
		
		void register_service()
		{
			cout << "Register service called = " << this << "\n";
			register_srvr(shared_from_this());
		}

};

void fn(shared_ptr<test> ptr)
{
	cout << "from fn : ";
	ptr->register_service();
}

int main()
{
 	//intended use
	shared_ptr<test> good = shared_ptr<test>(new test());
	good->register_service();
	
	fn(good);
	
	//---------------------------------------
	//Enabled Shared from this bad behaviour 
	// It is meditory to create shared poiter fisrt
	//Solultuon - 
	//	Make call constructor private
	//	Add static function create which return shared_ptr of that class
	//---------------------------------------
	
	//bad use
	//service bad;
	//bad.register(); //undefined behaviour on 'shared_from_this'
 
	//also bad
	//auto pbad = new service();
	//pbad->register();
}

class bad_bheviour_solution : public std::enable_shared_from_this<bad_bheviour_solution>
{
	

		bad_bheviour_solution()
		{
			cout << "Test class created= " << this << "\n";
		}
	
	
		~bad_bheviour_solution()
		{
			cout << "Test class deleted = " << this << "\n";
		}
		
public:
		static shared_ptr<bad_bheviour_solution> create()
		{
			return shared_ptr<bad_bheviour_solution> ( new bad_bheviour_solution());
		}

};

